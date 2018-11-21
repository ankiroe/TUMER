#include <NewPing.h>
#include <Adafruit_NeoPixel.h>
// Which pin on the Arduino is connected to the NeoPixels?
#define PING_PIN 28 // Pin Ultrasonidos
NewPing sonar(PING_PIN, PING_PIN );

#define PIN            33
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      16
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


//Motores
const int pinPWMA = 4;
const int pinAIN2 = 35;
const int pinAIN1 = 34;
const int pinBIN1 = 36;
const int pinBIN2 = 37;
const int pinPWMB = 5;
const int pinSTBY = 12;


const int waitTime = 2000;   //espera entre fases
const int velocidad = 70;      //velocidad de giro

const int pinMotorA[3] = { pinPWMA, pinAIN2, pinAIN1 };
const int pinMotorB[3] = { pinPWMB, pinBIN1, pinBIN2 };

int distancia = 0;
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
  Serial.begin(9600);
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.show();
  pinMode(pinAIN2, OUTPUT);
  pinMode(pinAIN1, OUTPUT);
  pinMode(pinPWMA, OUTPUT);
  pinMode(pinBIN1, OUTPUT);
  pinMode(pinBIN2, OUTPUT);
  pinMode(pinPWMB, OUTPUT);
}

void loop()
{ 
  leedistancia();
  
  //Mantener distancia de 20cm
  if (distancia < 20) {
    move(backward, velocidad);
    //Encender luces de marcha atrás y apagar resto
    pixels.setPixelColor(5, pixels.Color(0, 0, 0)); // Moderately bright green color.
    pixels.setPixelColor(4, pixels.Color(0, 0, 0)); // Moderately bright green color.
    pixels.setPixelColor(10, pixels.Color(0, 0, 0)); // Moderately bright green color.
    pixels.setPixelColor(11, pixels.Color(0, 0, 0)); // Moderately bright green color.
    pixels.setPixelColor(0, pixels.Color(50, 0, 0)); // Moderately bright green color.
    pixels.setPixelColor(15, pixels.Color(50, 0, 0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.
    //delay(500);
  } else {
    move(forward, velocidad);
    //Encender luces de marcha y apagar resto
    pixels.setPixelColor(5, pixels.Color(50, 50, 50)); // Moderately bright green color.
    pixels.setPixelColor(4, pixels.Color(50, 50, 50)); // Moderately bright green color.
    pixels.setPixelColor(10, pixels.Color(50, 50, 50)); // Moderately bright green color.
    pixels.setPixelColor(11, pixels.Color(50, 50, 50)); // Moderately bright green color.
    pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // Moderately bright green color.
    pixels.setPixelColor(15, pixels.Color(0, 0, 0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    //delay(500);
  }
  Serial.println(distancia);
}

void leedistancia(void)
{
  delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  distancia = uS / US_ROUNDTRIP_CM;
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
