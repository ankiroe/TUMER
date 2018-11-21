//Declaración de pines
const int pinPWMA = 4;
const int pinAIN2 = 35;
const int pinAIN1 = 34;
const int pinBIN1 = 36;
const int pinBIN2 = 37;
const int pinPWMB = 5;
const int pinSTBY = 12;

//Declaración de variables
const int waitTime = 2000;   //espera entre fases
const int velocidad = 100;      //velocidad de giro
 
const int pinMotorA[3] = { pinPWMA, pinAIN2, pinAIN1 };
const int pinMotorB[3] = { pinPWMB, pinBIN1, pinBIN2 };
 
enum moveDirection {
   forward,
   backward
};
 
enum turnDirection {
   clockwise,
   counterClockwise
};
 
void setup()
{
   pinMode(pinAIN2, OUTPUT);
   pinMode(pinAIN1, OUTPUT);
   pinMode(pinPWMA, OUTPUT);
   pinMode(pinBIN1, OUTPUT);
   pinMode(pinBIN2, OUTPUT);
   pinMode(pinPWMB, OUTPUT);
}
 
void loop()
{
   move(forward, velocidad);
   delay(waitTime);
 
   move(backward, velocidad);
   delay(waitTime);
 
   turn(clockwise, velocidad);
   delay(waitTime);
 
   turn(counterClockwise, velocidad);
   delay(waitTime);
 
   fullStop();
   delay(waitTime);
}
 
//Funciones que controlan el vehiculo
void move(int direction, int speed)
{
   if (direction == forward)
   {
      moveMotorForward(pinMotorA, speed);
      moveMotorForward(pinMotorB, speed);
   }
   else
   {
      moveMotorBackward(pinMotorA, speed);
      moveMotorBackward(pinMotorB, speed);
   }
}
 
void turn(int direction, int speed)
{
   if (direction == forward)
   {
      moveMotorForward(pinMotorA, speed);
      moveMotorBackward(pinMotorB, speed);
   }
   else
   {
      moveMotorBackward(pinMotorA, speed);
      moveMotorForward(pinMotorB, speed);
   }
}
 
void fullStop()
{
   stopMotor(pinMotorA);
   stopMotor(pinMotorB);
}
 
//Funciones que controlan los motores
void moveMotorForward(const int pinMotor[3], int speed)
{
   digitalWrite(pinMotor[1], HIGH);
   digitalWrite(pinMotor[2], LOW);
 
   analogWrite(pinMotor[0], speed);
}
 
void moveMotorBackward(const int pinMotor[3], int speed)
{
   digitalWrite(pinMotor[1], LOW);
   digitalWrite(pinMotor[2], HIGH);
 
   analogWrite(pinMotor[0], speed);
}
 
void stopMotor(const int pinMotor[3])
{
   digitalWrite(pinMotor[1], LOW);
   digitalWrite(pinMotor[2], LOW);
 
   analogWrite(pinMotor[0], 0);
}
