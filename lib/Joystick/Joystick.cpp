#include <Joystick.h>

float lecture()
{
    xValue = analogRead(x_pin);
    yValue = analogRead(y_pin);


    //print

    Serial.print("x = ");
    Serial.print(xValue);
    Serial.print("y = ");
    Serial.print(yValue);
}