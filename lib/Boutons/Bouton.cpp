#include "Bouton.h"

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long debounceDelay = 100;    // the debounce time; increase if the output flickers

Buttons_s button1 = {48,LOW,LOW,0};
Buttons_s button2 = {46,LOW,LOW,0};
Buttons_s button3 = {44,LOW,LOW,0};
Buttons_s button4 = {42,LOW,LOW,0};
Buttons_s button[4] = {button1,button2,button3,button4};


void initButton(){
    for(int i = 0; i<4;i++){
        pinMode(button[i].Pin, INPUT);
    }
}

void readButton(int clicked[4]) {
  // read the state of the switch into a local variable:
    for(int i = 0; i<4;i++){
        button[i].State = digitalRead(button[i].Pin);

        // check to see if you just pressed the button
        // (i.e. the input went from LOW to HIGH),  and you've waited long enough
        // since the last press to ignore any noise:
        if (button[i].State && (button[i].State != button[i].lastState)) {
            // reset the debouncing timer
            button[i].lastDebounceTime = millis();
            button[i].lastState = button[i].State;
            clicked[i] = HIGH;
            //Serial.print("Button ");Serial.print(i);Serial.print(" = ");Serial.println(button[i].State);
        }
        else if (!button[i].State && button[i].lastState) {
            if ((millis() - button[i].lastDebounceTime) > debounceDelay) {
                    button[i].lastState = LOW;
                    //Serial.print("Button ");Serial.print(i);Serial.print(" = ");Serial.println("Released");
            }
        }
    }
}

void testButton(){
    int clicked[4] = {0,0,0,0};
    while(1){
        password();
        readButton(clicked);
        printButtonState(clicked);
    }
}

bool password(int max_tries = 9999){
    int count = 0;
    int password[4] = {0,2,3,2};
    int clicked[4] = {0,0,0,0};
    static int tries = 0;
    while(tries < max_tries){
        readButton(clicked);
        if(clicked[0] || clicked[1] || clicked[2] || clicked[3]){
            if(count == 0)
                {if(clicked[password[0]])
                    {count = 1;} else count = 0;}
            else if(count == 1)
                {if(clicked[password[1]])
                    {count = 2;} else count = 0;}
            else if(count == 2)
                {if(clicked[password[2]])
                    {count = 3;} else count = 0;}
            else if(count == 3)
                {if(clicked[password[3]])
                {Serial.println("Password OK");tries = 0; return 1;}else count = 0;}
            tries++;
            }    
        printButtonState(clicked);
    }
    tries = 0;
    Serial.println("Password Failed");
    return 0;
}

void printButtonState(int clicked[4]){
    for(int i = 0; i<4;i++){
        if(clicked[i] == 1)
            {
                Serial.print("Button ");Serial.print(i);Serial.print(" = ");Serial.println(clicked[i]);
                clicked[i] = 0;
            }
    }
    
}