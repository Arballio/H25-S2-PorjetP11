#include "bargraph.h"
#include "Accelero.h"
//allumer le bargraph

int led[9] = {32, 30, 28, 26, 24, 22, 33, 31, 29};

void bargraph(int max, int min, int current_value)
{
    int step = (max - min)/10;
    int compare = min;

    for (int i=8 ; i>=0 ; i--)
    {
        pinMode(led[i], OUTPUT);
        if (compare < current_value)
        {
            compare += step;
            digitalWrite(led[i], HIGH);
        }
        else
        {
            digitalWrite(led[i], LOW);
        }
    }    
}


#define MAX_ACCELERO 120

//The shake_bar function will light up the bargraph when the accelerometer detects a shake
//Once a shake is detected, the bargraph will go up for 1 unit and then go down by 1 unit every 3 second
int shake_bar()
{
    static int Shaked = 0, Reset_Time = 0;
    int current_valueX = 0;
    int current_valueY = 0;
    int current_valueZ = 0;
    
    movementdetec(&current_valueX, &current_valueY, &current_valueZ);
    
    int highest = current_valueX>current_valueY?current_valueX:(current_valueY>current_valueZ?current_valueY:current_valueZ);

        if (highest > MAX_ACCELERO)
    {
        Shaked>=10?Shaked=10:Shaked+=1;
    } else if (millis() - Reset_Time > 1000)
    {
        Shaked<=0?Shaked=0:Shaked-=1;
        Reset_Time = millis();    
    }

    bargraph(10, 0, Shaked);
    return Shaked;
}


