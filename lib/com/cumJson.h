#include <Arduino.h>
#include "ArduinoJson.h"


#define BAUD 115200        // Frequence de transmission serielle

/*------------------------------ Constantes ---------------------------------*/
#define JSON_SIZE 500       // Taille du message JSON



/*------------------------- Prototypes de fonctions -------------------------*/
void sendMsg(); 
void readMsg();
void serialEvent();
/*---------------------------- Fonctions "Main" -----------------------------*/