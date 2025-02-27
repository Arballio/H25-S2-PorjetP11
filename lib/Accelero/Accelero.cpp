#include "Accelero.h"

void movementdetec()
{
    pinMode(groundpin, OUTPUT);
    pinMode(powerpin, OUTPUT);
    digitalWrite(groundpin, LOW);
    digitalWrite(powerpin, HIGH);
    int Xpin = analogRead(xpin);
    int Ypin = analogRead(ypin);
    int Zpin = analogRead(zpin);  
}

void shake_bar()
{
    int max = 700;
    int current_value;
    movementdetec();
    
    current_value = Zpin;
    bargraph(max, 300, current_value);
}