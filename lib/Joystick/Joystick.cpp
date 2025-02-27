#include <Joystick.h>

/*void init_joy()
{
    pinMode(x_pin, INPUT);
    pinMode(y_pin, INPUT);
}

direction lecture_joystick()
{
    int xValue = analogRead(x_pin);
    int yValue = analogRead(y_pin);
    direction state = down;


    //print
    printf("test de joystick");
    Serial.print("x = ");
    Serial.println(xValue);
    Serial.print("y = ");
    Serial.println(yValue);
    delay(500);

    if (xValue >= 0
        
        && xValue <= 100 && yValue < 600 && yValue > 500)
    {
        state = right;
        Serial.print("right");

    }

    else if (yValue >= 0 && yValue <= 300)
    {
        state = up;
        Serial.print("up");
    }

    else if (xValue > 700 && xValue <= 1100)
    {
        state = left;
        Serial.print("left");
    }

    else if (yValue > 700 && yValue <= 1100)
    {
        state = down;
        Serial.print("down");
    }

    else
    {
        state = neutral;
        Serial.print("neutral");
    }
    
    return state;
}*/


