#include <Joystick.h>

void init_joy()
{
    pinMode(x_pin, INPUT);
    pinMode(y_pin, INPUT);
}

direction lecture_joystick()
{
    int xValue = analogRead(x_pin);
    int yValue = analogRead(y_pin);

    direction state = down;


    /*
    Serial.print("x = ");
    Serial.println(xValue);
    Serial.print("y = ");
    Serial.println(yValue);
    */
    if (xValue >= 0
        
        && xValue <= 100 && yValue < 600 && yValue > 500)
    {
        state = right;

    }

    else if (yValue >= 0 && yValue <= 300)
    {
        state = up;
    }

    else if (xValue > 700 && xValue <= 1100)
    {
        state = left;
    }

    else if (yValue > 700 && yValue <= 1100)
    {
        state = down;
    }

    else
    {
        state = neutral;
    }
    
    return state;
}

void printJoystick(direction dir)
{
    switch (dir)
    {
    case up:
        Serial.println("up");
        break;
    case down:
        Serial.println("down");
        break;
    case left:
        Serial.println("left");
        break;
    case right:
        Serial.println("right");
        break;
    case neutral:
        Serial.println("neutral");
        break;
    default:
        break;
    }
}


