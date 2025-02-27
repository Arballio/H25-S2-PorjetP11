#include <Arduino.h>
#include <Joystick.h>
#include <Bouton.h>

void setup()
{
  Serial.begin(9600);
  lecture_joystick();
  
}

void loop()
{

  lecture_joystick();
}