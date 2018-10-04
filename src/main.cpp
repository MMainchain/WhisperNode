#include <Arduino.h>
#define BAUD 9600

void setup() {
    // put your setup code here, to run once:
    Serial.begin(BAUD); // Définition du port de sortie 
}

void loop() {
    // put your main code here, to run repeatedly:
    Serial.println("Hello From Arduino");
    delay(5000);
}