#include <Joystick.h>

float lecture()
{
    xValue = analogRead(x_pin);
    yValue = analogRead(y_pin);


    //print
    printf("test de joystick");
    Serial.print("x = ");
    Serial.print(xValue);
    Serial.print("y = ");
    Serial.print(yValue);
    delay(200);
}