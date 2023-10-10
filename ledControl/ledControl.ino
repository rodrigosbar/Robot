

/*******************************************************************************
 * Variáveis para controlar o led indicador
 *******************************************************************************/
unsigned long currentLedTime = 0;  // tempo de funcionamento do led
unsigned long previousLedTime = 0; // controle do tempo
int intervalLedtime = 2000;         // intervalo de tempo do led
const int pinoLed = D1;            // pino onde o LED está conectado
bool ledState = false;             // estado atual do led

void setup()
{
  Serial.begin(9600);
  initLed();
   while (!Serial)
    delay(1);
}

void loop()
{
 piscarLedStatus();
}

void initLed()
{
  pinMode(pinoLed, OUTPUT);
}

void piscarLedStatus()
{
  currentLedTime = millis();
  if ((currentLedTime - previousLedTime) > intervalLedtime)
  {
    previousLedTime = currentLedTime;
    mudarLed(!ledState);
  }
}

void mudarLed(bool ligar)
{
  digitalWrite(pinoLed, ligar ? HIGH : LOW);
  ledState = !ledState;
  Serial.print(F("LED State : "));
  Serial.println(ledState);
}
