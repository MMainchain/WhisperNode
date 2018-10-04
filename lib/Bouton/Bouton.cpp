#include "Bouton.h"
#include <Arduino.h>

Bouton::Bouton(int myPin) {
    this->myPin = myPin;
    this->lastState = LOW;
    this->lastPressedTime = millis();
}

int Bouton::getNumber() {

    unsigned long int i = millis();
    while((i-this->lastPressedTime) < 500) {
        i = millis();
        check();
    }
    int tmp=this->count; this->count = 0; 
    return tmp;
}

void Bouton::check() {

    int val = digitalRead(myPin);
    if((this->lastState != val) && (this->lastState == 1)) {
        this->count++;
        this->lastPressedTime = millis();
    }
    this->lastState= val;

}
