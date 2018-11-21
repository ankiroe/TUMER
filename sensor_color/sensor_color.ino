#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include "ColorConverterLib.h"
 
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);
 
void setup()
{
  Serial.begin(9600);
 
 
  if (!tcs.begin())
  {
    Serial.println("Error al iniciar TCS34725");
    while (1) delay(1000);
  }
}
 
void loop()
{
  uint16_t clear, red, green, blue;
 
  tcs.setInterrupt(false);
  delay(60); // Cuesta 50ms capturar el color
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);
 
  // Hacer rgb medición relativa
  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
 
  // Escalar rgb a bytes
  r *= 256; g *= 256; b *= 256;
 
  // Convertir a hue, saturation, value
  double hue, saturation, value;
  ColorConverter::RgbToHsv(static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b), hue, saturation, value);
 
  // Mostrar nombre de color
  printColorName(hue * 360);
 
  delay(1000);
}
 
void printColorName(double hue)
{
  if (hue < 15)
  {
    Serial.println("Rojo");
  }
  else if (hue < 45)
  {
    Serial.println("Naranja");
  }
  else if (hue < 90)
  {
    Serial.println("Amarillo");
  }
  else if (hue < 150)
  {
    Serial.println("Verde");
  }
  else if (hue < 210)
  {
    Serial.println("Cyan");
  }
  else if (hue < 270)
  {
    Serial.println("Azul");
  }
  else if (hue < 330)
  {
    Serial.println("Magenta");
  }
  else
  {
    Serial.println("Rojo");
  }
}
