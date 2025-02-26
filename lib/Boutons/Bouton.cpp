#include <Bouton.h>

int press_read()
{
    int bouton1 = digitalRead(press1);
    int bouton2 = digitalRead(press2);
    int bouton3 = digitalRead(press3);
    int bouton4 = digitalRead(press4);



    //print
    Serial.print("button state : ");
    Serial.print(bouton1);
    Serial.print(bouton2);
    Serial.print(bouton3);
    Serial.print(bouton4);
}