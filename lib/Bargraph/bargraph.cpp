#include "bargraph.h"
#include "Accelero.h"
//allumer le bargraph
void bargraph(int max, int min, int current_value)
{
    int step = (max - min)/10;
    int compare = 0;

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


