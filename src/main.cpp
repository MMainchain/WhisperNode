#include <Arduino.h>
#define BAUD 9600

const int blueLED = 6;
const int yellowLED = 9;

const int blueButton = 4;
const int yellowButton = 5;

// Button state
// 0 : LOW
// 1 : HIGH
int blueButtonState = 0;
int yellowButtonState = 0;

void setup() {

    // put your setup code here, to run once:
    Serial.begin(BAUD); // Définition du port de sortie 

    // LED pin init as output
    pinMode(blueLED, OUTPUT);
    pinMode(yellowLED, OUTPUT);

    // Button init as INPUT
    pinMode(blueButton, INPUT);
    pinMode(yellowButton, INPUT);

}

void loop() {

    // put your main code here, to run repeatedly:
    
    Serial.println("Hello From Arduino");

    // Pilotage des leds
    /*digitalWrite(blueLED, LOW);
    digitalWrite(yellowLED, HIGH);
    delay(1000);
    digitalWrite(yellowLED, LOW);
    digitalWrite(blueLED, HIGH);
    delay(1000);*/
    
    // button state reading
    blueButtonState = digitalRead(blueButton);
    yellowButtonState = digitalRead(yellowButton);

    // If button is pressed, light the LED
    if(blueButtonState == HIGH) {
        digitalWrite(blueLED, HIGH);
        delay(500);
        digitalWrite(blueLED, LOW);
    } 
    if(yellowButtonState == HIGH) {
        digitalWrite(yellowLED, HIGH);
        delay(500);
        digitalWrite(yellowLED, LOW);
    } 

}