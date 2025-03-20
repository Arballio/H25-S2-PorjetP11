// ================================================================================================
// ==================================== Includes ==================================================
// ================================================================================================
#include <Arduino.h>
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include <LiquidCrystal.h>
#include "Bouton.h"
#include "bargraph.h"
#include "Joystick.h"
#include "Accelero.h"
#include "ComRaw.h"

#define MAX_IDS_DELAYS 5

const int rs = 53, rw = 51, en = 49, d4 = 47, d5 = 45, d6 = 43, d7 = 41;
LiquidCrystal lcd(rs,rw, en, d4, d5, d6, d7);

#define GREEN_LED 34
#define BLUE_LED 36
#define RED_LED 38
#define YELLOW_LED 40 

// ================================================================================================
// =============================== Private functions ==============================================
// ================================================================================================
bool NonStoppingDelay(unsigned int delayTime,int id);
void motor_rumble(int duration = 500);
void blinkLed(int duration = 500);
void PrintFrame(Frame frame);
void PrintFrame(Frame frame,bool ToLCD);




// ================================================================================================
// ==================================== Main code =================================================
// ================================================================================================

void initPins()
{
  pinMode(2, OUTPUT);
  pinMode(34, OUTPUT);//LED Vert
  pinMode(36, OUTPUT);//LED Bleu
  pinMode(38, OUTPUT);//LED Rouge
  pinMode(40, OUTPUT);//LED Jaune

  pinMode(A10, INPUT);
}

void setup() {

  Serial.begin(9600);  
  lcd.begin(16, 2);
  //Serial.println("Hello World");
  initButton();
  initPins();
  init_joy();
  initAccelero();

  //delay(1000);
  lecture_joystick();
}

void loop() {
  Frame FrameOut = {0, 0, 0};
  
  //int AcceleroX = 0;
  //int AcceleroY = 0;
  //int AcceleroZ = 0;
  //movementdetec(&AcceleroX, &AcceleroY, &AcceleroZ);

  if(NonStoppingDelay(50,0)){
      if(shake_bar())
      {
        FrameOut.data = 1;
        FrameOut.id = MSG_ID_SHAKED;
      }
    }

  //Lecture des boutons
  static bool clicked[4] = {0,0,0,0};
  readButton(clicked);

  if(clicked[0] || clicked[1] || clicked[2] || clicked[3])
  {
    FrameOut.data = (clicked[0] << 3) | (clicked[1] << 2) | (clicked[2] << 1) | clicked[3];
    FrameOut.id = MSG_ID_BUTTON;
    for(int i = 0; i<4;i++)
      clicked[i] = 0;
  }

  //Lecture du joystick
  direction read = lecture_joystick();

  if(NonStoppingDelay(100,1) && FrameOut.id == 0)
  {
    if (read != neutral)
    {
        FrameOut.data = read;
        FrameOut.id = MSG_ID_JOYSTICK;
    }

  }

  //Lecture du potentiometre
  if(NonStoppingDelay(100,2) && FrameOut.id == 0)
  {
    double PotOut = analogRead(A10);
    PotOut = map(PotOut, 0, 1023, 0, 255);
    static int lastPot = 0;

    if(lastPot > PotOut+2 || PotOut-2 > lastPot  )
    {
      FrameOut.data = PotOut;
      FrameOut.id = MSG_ID_POTENTIOMETER;
      lastPot = PotOut;
    }
  }

  //Rafraichissement de l'ecran LCD
  if(NonStoppingDelay(1000,3))
  {
    //Refresh time on screen
    //lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Time:        ");
    lcd.setCursor(7, 0);
    lcd.print(millis()/1000);
  }
        

  if(FrameOut.id != 0)
  {  
    sendMsg(FrameOut);
    PrintFrame(FrameOut);
  }
  
  Frame frameIn = readMsg(); 
  
  if(frameIn.id != 0)
  {
    switch (frameIn.id){
      case MSG_ID_PC_LED:
        digitalWrite(GREEN_LED, frameIn.data & 0x01);
        digitalWrite(BLUE_LED, (frameIn.data & 0x02)>>1);
        digitalWrite(RED_LED, (frameIn.data & 0x03)>>2);
        digitalWrite(YELLOW_LED, (frameIn.data & 0x04)>>3);
        break;
  
      case MSG_ID_PC_MOTOR:

        break;

      case MSG_ID_PC_LCD:

        break;
      case MSG_ID_PC_STATE:

        break;
      case MSG_ID_FROM_MISC:
      
        break;
      default:
        break;
    }
  }
}
 

void PrintFrame(Frame frame)
{
  Serial.print("ID: ");
  Serial.print(frame.id);
  Serial.print(" Data: ");
  Serial.print(frame.data);
  Serial.print(" Checksum: ");
  Serial.println(frame.checksum);
}

void PrintFrame(Frame frame,bool ToLCD)
{
  if(ToLCD)
  {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("ID:");
    lcd.print(frame.id);
    //lcd.setCursor(0, 1);
    lcd.print("Data:");
    lcd.print(frame.data);
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