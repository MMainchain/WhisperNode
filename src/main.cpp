#include <Arduino.h>
#include <Bouton.h>
#include "LowPower.h"

#define BAUD 9600

// Element pins
const int blueButton = 4;
const int yellowButton = 5;

int countD = 0;
int countG = 0;

Bouton boutonD(blueButton);
Bouton boutonG(yellowButton);

void setup() {

    // put your setup code here, to run once:
    Serial.begin(BAUD); // Définition du port de sortie 

}

void loop() {
    /** TP1 **/
    
    // Bibliothèque Bouton    
    // boutonD.check();
    // countD = boutonD.getNumber();
    // if (countD > 0) {
    //    Serial.print("D"); 
    //    Serial.println(countD);
    //}

    //boutonG.check();
    //countG = boutonG.getNumber();
    //if (countG > 0) {
    //    Serial.print("G"); 
    //    Serial.println(countG);
    //}

    LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, 
                SPI_OFF, USART0_OFF, TWI_OFF);

}