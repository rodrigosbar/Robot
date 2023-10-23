/*******************************************************************************
 * Variáveis para Conexão com WIFI e MQTT
 *******************************************************************************/
#include <PubSubClient.h>

#include <ArduinoJson.h>

#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#include "config.h" // Arquivo de configuração do broker MQTT
#include <WiFiClientSecure.h>

const char *ssid = "jesus2ghz";
const char *password = "custa10reais";

/**** Secure WiFi Connectivity Initialisation *****/
WiFiClientSecure espClient;

/**** MQTT Client Initialisation Using WiFi Connection *****/
PubSubClient client(espClient);

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

bool isOnlineRobot = false;

/*******************************************************************************
 * Variáveis para controlar o led indicador
 *******************************************************************************/
const int pinoLed = D1; // pino onde o LED está conectado
bool ledState = false;  // estado atual do led

/*******************************************************************************
 * Variáveis para controlar os motores
 *******************************************************************************/
#define ENA 14      // Enable/speed motors Right        GPIO14(D5)
#define ENB 12      // Enable/speed motors Left         GPIO12(D6)
#define IN_1 15     // L298N in1 motors Rightx          GPIO15(D8)
#define IN_2 13     // L298N in2 motors Right           GPIO13(D7)
#define IN_3 2      // L298N in3 motors Left            GPIO2(D4)
#define IN_4 0      // L298N in4 motors Left            GPIO0(D3)
int speedCar = 400; // 400 - 1023.
int speed_Coeff = 3;

void setup()
{
  Serial.begin(9600);

  while (!Serial)
    delay(1);
  initMotors();
  initLed();
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

  if (!isOnlineRobot)
  {
    DynamicJsonDocument doc(1024);

    doc["deviceId"] = "Robot FPV";
    doc["mensagem"] = "Online-";

    char mqtt_message[128];
    serializeJson(doc, mqtt_message);

    publishMessage("robotMessages", mqtt_message, true);
    isOnlineRobot = true;
  }
}

/*******************************************************************************
 * Funções para os motores
 *******************************************************************************/
void initMotors()
{
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
  stopRobot();
}

void testarRobo()
{
  delay(1000);
  Serial.println(F("FRENTE - 5s"));
  mudarLed(true);
  goAhead();
  delay(5000);

  Serial.println(F("PARADO: 5s"));
  mudarLed(false);
  stopRobot();
  delay(5000);

  Serial.println(F("PARA TRÁS: 5s"));
  mudarLed(true);
  goBack();
  delay(5000);

  Serial.println(F("PARADO: 5s"));
  mudarLed(false);
  stopRobot();
  delay(5000);
}

void goAhead()
{

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
  Serial.println(F("FRENTE"));
}

void goBack()
{

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
  Serial.println(F("ATRAS"));
}

void goRight()
{

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
  Serial.println(F("DIREITA"));
}

void goLeft()
{

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
  Serial.println(F("ESQUERDA"));
}

void goAheadRight()
{

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar / speed_Coeff);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
  Serial.println(F("FRENTE DIREITA"));
}

void goAheadLeft()
{

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar / speed_Coeff);
  Serial.println(F("FRENTE ESQUERDA"));
}

void goBackRight()
{

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar / speed_Coeff);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
  Serial.println(F("ATRAS DIREITA"));
}

void goBackLeft()
{

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar / speed_Coeff);
  Serial.println(F("ATRAS ESQUERDA"));
}

void stopRobot()
{

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}

/*******************************************************************************
 * Funções para o LED
 *******************************************************************************/
void initLed()
{
  pinMode(pinoLed, OUTPUT);
}

void mudarLed(bool ligar)
{
  digitalWrite(pinoLed, ligar ? HIGH : LOW);
  ledState = !ledState;
  Serial.print(F("LED State novo : "));
  Serial.println(ledState);
}

/*******************************************************************************
 * Funções para WIFI e MQTT
 *******************************************************************************/

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
      client.subscribe("motor_state"); // subscribe the topics here
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

  if (strcmp(topic, "motor_state") == 0)
  {

    if (incommingMessage.equals("ahead"))
    {
      goAhead();
    }

    if (incommingMessage.equals("back"))
    {
      goBack();
    }

    if (incommingMessage.equals("left"))
    {
      goLeft();
    }

    if (incommingMessage.equals("right"))
    {
      goRight();
    }

    if (incommingMessage.equals("aheadLeft"))
    {
      goAheadLeft();
    }

    if (incommingMessage.equals("backRight"))
    {
      goBackRight();
    }

    if (incommingMessage.equals("backLeft"))
    {
      goBackLeft();
    }

    if (incommingMessage.equals("stop"))
    {
      stopRobot();
    }

    if (incommingMessage.equals("aheadRight"))
    {
      goAheadRight();
    }
  }
}

/**** Method for Publishing MQTT Messages **********/
void publishMessage(const char *topic, String payload, boolean retained)
{
  if (client.publish(topic, payload.c_str(), true))
    Serial.println("Mensagem publicada [" + String(topic) + "]: " + payload);
}
