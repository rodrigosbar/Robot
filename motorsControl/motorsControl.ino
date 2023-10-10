
/*******************************************************************************
 * Variáveis para controlar o led indicador
 *******************************************************************************/
const int pinoLed = D1; // pino onde o LED está conectado

/*******************************************************************************
 * Variáveis para controlar os motores
 *******************************************************************************/
#define ENA 14  // Enable/speed motors Right        GPIO14(D5)
#define ENB 12  // Enable/speed motors Left         GPIO12(D6)
#define IN_1 15 // L298N in1 motors Rightx          GPIO15(D8)
#define IN_2 13 // L298N in2 motors Right           GPIO13(D7)
#define IN_3 2  // L298N in3 motors Left            GPIO2(D4)
#define IN_4 0  // L298N in4 motors Left            GPIO0(D3)

int speedCar = 400; // 400 - 1023.
int speed_Coeff = 3;

void setup()
{
  Serial.begin(9600);
  initMotors();
  initLed();
  while (!Serial)
    delay(1);
}

void loop()
{
  testarRobo();
}

void initMotors()
{
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
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
}

void goBack()
{

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}

void goRight()
{

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
}

void goLeft()
{

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}

void goAheadRight()
{

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar / speed_Coeff);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
}

void goAheadLeft()
{

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar / speed_Coeff);
}

void goBackRight()
{

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar / speed_Coeff);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}

void goBackLeft()
{

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar / speed_Coeff);
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

void initLed()
{
  pinMode(pinoLed, OUTPUT);
}

void mudarLed(bool ligar)
{
  digitalWrite(pinoLed, ligar ? HIGH : LOW);
}