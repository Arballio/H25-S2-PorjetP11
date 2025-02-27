// ================================================================================================
// ==================================== Includes ==================================================
// ================================================================================================
#include <Arduino.h>
#include "screen_16x2_driver.h"
#include "Bouton.h"

// ================================================================================================
// =============================== Private functions ==============================================
// ================================================================================================
bool NonStoppingDelay(int delayTime);


// ================================================================================================
// ==================================== Main code =================================================
// ================================================================================================

void setup() {
  Serial.begin(9600);
  Serial.println("Hello World");
  initButton();
  initLcd();
  menuManager(NO_INPUT);
}


void loop() {
  //testButton();
  static int clicked[4] = {0,0,0,0};
  readButton(clicked);

  if (clicked[0] == 1)
  {
    menuManager(MENU_UP);
    clicked[0] = 0;
  }
  else if (clicked[1] == 1)
  {
    menuManager(MENU_DOWN);
    clicked[1] = 0;
  }
  else if (clicked[2] == 1)
  {
    menuManager(MENU_LEFT);
    clicked[2] = 0;
  }
  else if (clicked[3] == 1)
  {
    menuManager(MENU_RIGHT);
    clicked[3] = 0;
  }
  else
  {
    if(NonStoppingDelay(1000))
      menuManager(NO_INPUT);
  }


}


bool NonStoppingDelay(int delayTime)
{
  static unsigned long lastTime = 0;
  if (millis() - lastTime > delayTime)
  {
    lastTime = millis();
    return true;
  }
  return false;
}