// * Author: Arthur Blanchard
// * Date: 2025/03/19
// * Description: Header file for ComRaw.cpp, defines the Frame structure and function prototypes.

#ifndef COMRAW_H
#define COMRAW_H

#include <Arduino.h>

#define BAUD 115200      
#define MSG_SIZE 3
#define MSG_ID_ERROR 71

#define MSG_ID_JOYSTICK 101
#define MSG_ID_POTENTIOMETER 102
#define MSG_ID_ACCELEROMETER 103
#define MSG_ID_BUTTON 104
#define MSG_ID_SHAKED 105

#define MSG_ID_PC_LED 201
#define MSG_ID_PC_MOTOR 202
#define MSG_ID_PC_LCD 203
#define MSG_ID_PC_STATE 204
#define MSG_ID_FROM_MISC 242

// Frame structure
typedef struct Frame_t { 
    uint8_t id;
    uint8_t data;
    uint8_t checksum;
}Frame;

// Function prototypes
void sendMsg(Frame frame);
Frame readMsg();
Frame readMsg(byte id);
byte convertBoolsToByte(bool p_sw[]);
void byteToBoolArray(byte b, bool arr[8]);

#endif // COMRAW_H