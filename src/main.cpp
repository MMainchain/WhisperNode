#include <Arduino.h>
#define BAUD 9600

void setup() {
    // put your setup code here, to run once:
    Serial.begin(BAUD); // Définition du port de sortie 
}

void loop() {
    // put your main code here, to run repeatedly:
    Serial.println("Hello From Arduino");

    // Pilotage des leds
    digitalWrite(9, LOW);
    digitalWrite(DD6, HIGH);
    delay(1000);
    digitalWrite(6, LOW);
    digitalWrite(9, HIGH);
    delay(1000);

}