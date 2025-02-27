#include <Arduino.h>
#include <Joystick.h>
#include <Bouton.h>
#include <Accelero.h>
#include <bargraph.h>

void setup()
{
  Serial.begin(9600);
  //lecture_joystick();
  //movementdetec();
  bargraph(10, 0, 5);
  delay(2000);
}

void loop()
{
  //movementdetec();
  //lecture_joystick();
}