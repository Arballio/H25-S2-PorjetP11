#include <Arduino.h>
#include <stdio.h>
#include "bargraph.h"

const int groundpin = 18;
const int powerpin = 19;
const int xpin = A13;
const int ypin = A12;
const int zpin = A11;
int Xpin = analogRead(xpin);
int Ypin = analogRead(ypin);
int Zpin = analogRead(zpin); 
void movementdetec();