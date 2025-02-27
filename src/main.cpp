#include <Arduino.h>
#include "screen_16x2_driver.h"
#include "Bouton.h"


void setup() {
  Serial.begin(9600);
  Serial.println("Hello World");
  initButton();
  //MenuManager(MENU_ENTER);
}

void loop() {
  
  //MenuManager(NO_INPUT);
  if(digitalRead(48))
    Serial.println("Button 1");
  
  testButton();

}
