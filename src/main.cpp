// ================================================================================================
// ==================================== Includes ==================================================
// ================================================================================================
#include <Arduino.h>
#include "screen_16x2_driver.h"
#include "Bouton.h"
#include "bargraph.h"
#include "Joystick.h"

// ================================================================================================
// =============================== Private functions ==============================================
// ================================================================================================
bool NonStoppingDelay(unsigned int delayTime);
void menuFunction(Function_e function);
void motor_rumble(int duration = 500);
void blinkLed(int duration = 500);



// ================================================================================================
// ==================================== Main code =================================================
// ================================================================================================

void initPins()
{
  pinMode(2, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(38, OUTPUT);
  pinMode(40, OUTPUT);

  pinMode(A10, INPUT);
}


void setup() {
  Serial.begin(9600);
  delay(100);
  Serial.println("Hello World");
  initButton();
  initLcd();
  initPins();
  init_joy();
  delay(1000);
  menuManager(NO_INPUT);
  delay(1000);
  lecture_joystick();
  //while(1);
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
    menuFunction(menuManager(MENU_ENTER));
    clicked[2] = 0;
  }
  else if (clicked[3] == 1)
  {
    //useless statement
    //menuManager(NO_INPUT);
    //clicked[3] = 0;
  }
  else
  {
    if(NonStoppingDelay(1000))
      menuManager(NO_INPUT);
  }

  bargraph(1024,0,analogRead(A10));

  direction read = lecture_joystick();

  if(read != neutral && NonStoppingDelay(1000))
  {
    printJoystick(read);
  }

}

void menuFunction(Function_e function)
{
  switch (function)
  {
  case passwordfunc:
    if(password(10))
    {
      motor_rumble();
      blinkLed();
      
    }
    break;
  
  default:
    break;
  }
}

bool NonStoppingDelay(unsigned int delayTime)
{
  static unsigned long lastTime = 0;
  if (millis() - lastTime > delayTime)
  {
    lastTime = millis();
    return true;
  }
  return false;
}

void motor_rumble(int duration)
{
  for(int i = 0; i<3;i++)
  {
    digitalWrite(2, HIGH);
    delay(duration);
    digitalWrite(2, LOW);
    delay(duration);
  Serial.println("Rumble");
  }
  digitalWrite(2, HIGH);
  delay(duration*2);
  digitalWrite(2, LOW);
 
}

void blinkLed(int duration)
{
  int LedPin[4] = {34,36,38,40};
  for(int i = 0; i<4;i++)
  {
    digitalWrite(LedPin[i], HIGH);
    delay(duration);
    digitalWrite(LedPin[i], LOW);
    delay(duration/4);
  } 
  
}