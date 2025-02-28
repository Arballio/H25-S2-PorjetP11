// ================================================================================================
// ==================================== Includes ==================================================
// ================================================================================================
#include <Arduino.h>
#include "screen_16x2_driver.h"
#include "Bouton.h"
#include "bargraph.h"
#include "Joystick.h"
#include "Accelero.h"

#define MAX_IDS_DELAYS 5

// ================================================================================================
// =============================== Private functions ==============================================
// ================================================================================================
bool NonStoppingDelay(unsigned int delayTime,int id);
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
  initAccelero();

  delay(1000);
  menuManager(NO_INPUT);
  lecture_joystick();
  //while(1);
}

bool accelOrBar = 0;

void loop() {
  //testButton();

  int AcceleroX = 0;
  int AcceleroY = 0;
  int AcceleroZ = 0;
  //movementdetec(&AcceleroX, &AcceleroY, &AcceleroZ);

  if(!accelOrBar){
    if(NonStoppingDelay(100,0)){
      shake_bar();
      //Serial.print("X = ");Serial.print(AcceleroX);Serial.print(" Y = ");Serial.print(AcceleroY);Serial.print(" Z = ");Serial.println(AcceleroZ);
    }
  } else{
    bargraph(1024,0,analogRead(A10));
  }

  direction read = lecture_joystick();

  if(read != neutral && NonStoppingDelay(1000,2))
  {
    printJoystick(read);
  }

  static int clicked[4] = {0,0,0,0};
  readButton(clicked);

  if(NonStoppingDelay(100,3)){
    if (clicked[0] == 1 || read == up)
    {
      menuManager(MENU_UP);
      clicked[0] = 0;
    }
    else if (clicked[1] == 1 || read == down)
    {
      menuManager(MENU_DOWN);
      clicked[1] = 0;
    }
    else if (clicked[2] == 1 || read == left)
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
      if(NonStoppingDelay(1000,1))
        menuManager(NO_INPUT);
    }
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
  case accelero:
    accelOrBar = 0;
    break;
  case potbargraph:
    accelOrBar = 1;
    break;
  
  default:
    break;
  }
}

bool NonStoppingDelay(unsigned int delayTime,int id)
{
  static unsigned long lastTime[MAX_IDS_DELAYS] = {0};
  if (millis() - lastTime[id] > delayTime)
  {
    lastTime[id] = millis();
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