#include "Bouton.h"
#include <Arduino.h>

/**
 * Class representing the Arduino's button
 */
Bouton::Bouton(int myPin) {
    this->myPin = myPin;
    this->lastState = LOW;
    this->lastPressedTime = millis();
}

/**
 * Returns the amount of times the button has been pressed.
 * This amount is back to 0 at each call.
 */
int Bouton::getNumber() {

    unsigned long int i = millis();
    while((i-this->lastPressedTime) < 500) {
        i = millis();
        check();
    }
    int tmp=this->count; this->count = 0; 
    return tmp;
}

/**
 * Increments a counter each time the button is pressed.
 */
void Bouton::check() {

    int val = digitalRead(myPin);
    if((this->lastState != val) && (this->lastState == 1)) {
        this->count++;
        this->lastPressedTime = millis();
    }
    this->lastState= val;

}
