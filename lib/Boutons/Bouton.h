#include <Arduino.h>

#pragma once

typedef enum{
    SW2,
    SW3,
    SW4,
    SW5,
}ButtonsName;


typedef struct ButtonsStruct{
    int Pin;
    int State;
    int lastState;
    unsigned long lastDebounceTime;
}Buttons_s;


void testButton();
void printButtonState(int clicked[4]);
void readButton(int clicked[4]);
void initButton();
bool password(int max_tries = 9999);