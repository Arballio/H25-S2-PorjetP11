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

void shake_bar()
{
    int max = 700;
    int current_valueX = 0;
    int current_valueY = 0;
    int current_valueZ = 0;
    movementdetec(&current_valueX, &current_valueY, &current_valueZ);
    /*Serial.print("y = ");
    Serial.println(current_valueY);*/

    bargraph(max, 300, current_valueY);
}


