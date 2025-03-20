#include "Accelero.h"

#define xpin A13
#define ypin A12
#define zpin A11


void initAccelero()
{
    pinMode(xpin, INPUT);
    pinMode(ypin, INPUT);
    pinMode(zpin, INPUT);
}

void movementdetec(int *Xpin, int *Ypin, int *Zpin)
{
    *Xpin = abs(analogRead(xpin)-300);
    *Ypin = abs(analogRead(ypin)-300);
    *Zpin = abs(analogRead(zpin)-300);  
}

