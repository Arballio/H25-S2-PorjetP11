#include <Arduino.h>
#include <stdio.h>

#pragma once

typedef enum{
    SW1,
    SW2,
    SW3,
    SW4,
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
void password();