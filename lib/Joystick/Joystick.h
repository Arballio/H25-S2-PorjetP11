#include <Arduino.h>
#include <stdio.h>


#define x_pin A15
#define y_pin A14

typedef enum{
    up = 0, down, left, right, neutral

}direction;

direction lecture_joystick();
void printJoystick(direction dir);
void init_joy();
