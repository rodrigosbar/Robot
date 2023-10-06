
/*******************************************************************************
 * Variáveis para controlar os motores
 *******************************************************************************/
#define ENA 14  // Enable/speed motors Right        GPIO14(D5)
#define ENB 12  // Enable/speed motors Left         GPIO12(D6)
#define IN_1 15 // L298N in1 motors Rightx          GPIO15(D8)
#define IN_2 13 // L298N in2 motors Right           GPIO13(D7)
#define IN_3 2  // L298N in3 motors Left            GPIO2(D4)
#define IN_4 0  // L298N in4 motors Left            GPIO0(D3)

int speedCar = 800; // 400 - 1023.
int speed_Coeff = 3;

void setup()
{
  initMotors();
}

void loop()
{
  // put your main code here, to run repeatedly:
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