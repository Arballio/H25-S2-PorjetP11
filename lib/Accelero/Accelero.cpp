#include <Accelero.h>

void movementdetec()
{
    pinMode(groundpin, OUTPUT);
    pinMode(powerpin, OUTPUT);
    digitalWrite(groundpin, LOW);
    digitalWrite(powerpin, HIGH);
    int Xpin = analogRead(xpin);
    int Ypin = analogRead(ypin);
    int Zpin = analogRead(zpin);

    

    Serial.print("movement detected");
    Serial.print("\n");
    Serial.print(Xpin);
    Serial.print("\n");
    Serial.print(Ypin);
    Serial.print("\n");
    Serial.print(Zpin);
    Serial.print("\n");
    delay(100);


   
}