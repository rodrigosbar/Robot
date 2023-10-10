#include <PubSubClient.h>

#include <ArduinoJson.h>



/*******************************************************************************
 * Importação das bibliotecas externas
 *******************************************************************************/
#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif


#include "config.h" // Arquivo de configuração do broker MQTT
#include <WiFiClientSecure.h>


bool testeEnviado = false;
const int pinoLed = D1; // pino onde o LED está conectado
bool ledState = false;  // estado atual do led

/*******************************************************************************
 * Variáveis para conexão WIFI
 *******************************************************************************/
const char *ssid = "jesus2ghz";
const char *password = "custa10reais";

/**** Secure WiFi Connectivity Initialisation *****/
WiFiClientSecure espClient;

/**** MQTT Client Initialisation Using WiFi Connection *****/
PubSubClient client(espClient);

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

/************* Connect to WiFi ***********/
void setup_wifi()
{
  delay(10);
  Serial.print("\nConnecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("\nWiFi connected\nIP address: ");
  Serial.println(WiFi.localIP());
}


/************* Connect to MQTT Broker ***********/
void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    String clientId = "Robot-";
    clientId += String(random(0xffff), HEX); // Create a random client ID
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password))
    {
      Serial.println("connected to MQTT");
      client.subscribe("led_state"); // subscribe the topics here
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again MQTT in 5 seconds"); // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

/***** Call back Method for Receiving MQTT messages and Switching LED ****/

void callback(char *topic, byte *payload, unsigned int length)
{
  String incommingMessage = "";
  for (int i = 0; i < length; i++)
    incommingMessage += (char)payload[i];

  Serial.println("Mensagem MQTT [" + String(topic) + "]" + incommingMessage);

  //--- check the incomming message
  if (strcmp(topic, "led_state") == 0)
  {
    if (incommingMessage.equals("1"))
      mudarLed(true); // Turn the LED on
    else
      mudarLed(false); // Turn the LED off
  }
}

/**** Method for Publishing MQTT Messages **********/
void publishMessage(const char *topic, String payload, boolean retained)
{
  if (client.publish(topic, payload.c_str(), true))
    Serial.println("Mensagem publicada [" + String(topic) + "]: " + payload);
}

void mudarLed(bool ligar)
{
  digitalWrite(pinoLed, ligar ? HIGH : LOW);
  ledState = !ledState;
  Serial.print(F("LED State : "));
  Serial.println(ledState);
}


void setup()
{
  Serial.begin(9600);
  pinMode(pinoLed, OUTPUT);
  while (!Serial)
    delay(1);
  setup_wifi();
#ifdef ESP8266
  espClient.setInsecure();
#else
  espClient.setCACert(root_ca); // enable this line and the the "certificate" code for secure connection
#endif
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}



void loop()
{
  if (!client.connected())
    reconnect(); // check if client is connected
  client.loop();

  if (!testeEnviado)
  {
    DynamicJsonDocument doc(1024);

    doc["deviceId"] = "Robot teste";
    doc["siteId"] = "Minha casa";
    doc["mensagem"] = "Olá mundo";

    char mqtt_message[128];
    serializeJson(doc, mqtt_message);

    publishMessage("robotMessages", mqtt_message, true);
    testeEnviado = true;
  }
}
