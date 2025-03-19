#include <Arduino.h>
#include <stdio.h>


#define x_pin A15
#define y_pin A14

typedef enum{
    down = 0b0001, up = 0b0010, right = 0b0100, left = 0b1000, neutral

}direction;

direction lecture_joystick();
void printJoystick(direction dir);
void init_joy();
