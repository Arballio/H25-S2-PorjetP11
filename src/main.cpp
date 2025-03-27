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

#define MAX_IDS_DELAYS 10
#define LED_GREEN 34
#define LED_BLUE 36
#define LED_RED 38
#define LED_YELLOW 40

const int rs = 53, rw = 51, en = 49, d4 = 47, d5 = 45, d6 = 43, d7 = 41;
LiquidCrystal lcd(rs,rw, en, d4, d5, d6, d7);

// ================================================================================================
// =============================== Private functions ==============================================
// ================================================================================================
bool NonStoppingDelay(unsigned int delayTime,int id);
void motor_activate(int duration);
void motor_activate(int duration, int qty);
void motor_refresh(int duration);
void motor_refresh(int duration, int qty);
void blinkLed(int duration = 500);
void PrintFrame(Frame frame);
void PrintFrame(Frame frame,bool ToLCD);
void motor_refresh();




// ================================================================================================
// ==================================== Main code =================================================
// ================================================================================================

void initPins()
{
  pinMode(2, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);//LED Vert
  pinMode(LED_BLUE, OUTPUT);//LED Bleu
  pinMode(LED_RED, OUTPUT);//LED Rouge
  pinMode(LED_YELLOW, OUTPUT);//LED Jaune

  pinMode(A10, INPUT);
}

void setup() {

  Serial.begin(115200);
  delay(100);
  lcd.begin(16, 2);
  lcd.clear();
  //Serial.println("Hello World");
  initButton();
  initPins();
  init_joy();
  initAccelero();
  lecture_joystick();
}

struct motor_t
{
  int Dur = 0;
  int Qty = 0;
  bool Active = false;
}motor;

void loop() {
  Frame FrameOut = {0, 0, 0};
  
  //int AcceleroX = 0;
  //int AcceleroY = 0;
  //int AcceleroZ = 0;
  //movementdetec(&AcceleroX, &AcceleroY, &AcceleroZ);

  if(NonStoppingDelay(100,0)){
      int shake = shake_bar();
      /*if(shake == 10)
      {
        FrameOut.data = 1;
        FrameOut.id = MSG_ID_SHAKED;
        motor_activate(500,5);
      }else if(shake > 5)
      {
        //motor_activate(50,shake);
      }*/
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
    lcd.setCursor(6, 0);
    lcd.print(millis()/1000);
  }
        

  if(FrameOut.id != 0)
  {  
    sendMsg(FrameOut);
    //PrintFrame(FrameOut,1);
  }
  
  Frame frameIn = readMsg(); 
  
  switch(frameIn.id)
    {
    case MSG_ID_PC_LED:
      digitalWrite(LED_GREEN, (frameIn.data & 0x08)>>3);
      digitalWrite(LED_BLUE, (frameIn.data & 0x04) >> 2);
      digitalWrite(LED_RED, (frameIn.data & 0x02) >> 1 );
      digitalWrite(LED_YELLOW, (frameIn.data & 0x01));
      break;
    case MSG_ID_PC_MOTOR:
      motor_activate(frameIn.data);
      break;
    case MSG_ID_PC_LCD:
      
      break;
    case MSG_ID_PC_STATE:
      
      break;
    default:
      break;
    }

  motor_refresh();
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


void motor_activate(int duration)
{
  motor.Dur = duration;
  !motor.Active?motor.Active = true:motor.Active = false;
}

void motor_activate(int duration, int qty)
{
  motor.Dur = duration;
  motor.Qty = qty;
  !motor.Active?motor.Active = true:motor.Active = false;
}

void motor_refresh()
{
  static unsigned long lastTime = 0;
  static bool isOn = false;

  if(motor.Active)
  {
    if(millis() - lastTime > motor.Dur)
    {
      lastTime = millis();
      isOn = !isOn;
      digitalWrite(2, isOn);
      motor.Qty--;
      if(motor.Qty == 0)
      {
        isOn = false;
        digitalWrite(2, isOn);
        motor.Active = false;
      }
    }
  }
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