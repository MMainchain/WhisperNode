#include <Arduino.h>
#include <Bouton.h>
#include "LowPower.h"
#include <RH_RF95.h>
#include <T2WhisperNode.h>

#define BAUD 9600

// Element pins
const int blueButton = 4;
const int yellowButton = 5;

int countD = 0;
int countG = 0;

/*Bouton boutonD(blueButton);
Bouton boutonG(yellowButton);*/

T2Flash myflash;
RH_RF95 myradio;

void setup() {

    // put your setup code here, to run once:
    Serial.begin(BAUD); // Définition du port de sortie 

    /** TP2 **/
    
    // Pour mémoire flash
    myflash.init(T2_WPN_FLASH_SPI_CS);
    myflash.powerDown();

    // Pour puce LoRa
    myradio.init();
    myradio.sleep();
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

    /** TP2 **/
    // LowPower.idle(SLEEP_FOREVER, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);
    // LowPower.idle(SLEEP_FOREVER, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_ON);
    // LowPower.idle(SLEEP_FOREVER, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_ON, TWI_OFF);
    // LowPower.idle(SLEEP_FOREVER, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_ON, USART0_OFF, TWI_OFF);
    // LowPower.idle(SLEEP_FOREVER, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_ON, USART0_ON, TWI_ON);

    // LowPower.powerSave(SLEEP_FOREVER, ADC_OFF, BOD_OFF, TIMER2_OFF);
    // LowPower.powerSave(SLEEP_FOREVER, ADC_ON, BOD_OFF, TIMER2_OFF);
    // LowPower.powerSave(SLEEP_FOREVER, ADC_OFF, BOD_ON, TIMER2_OFF);
    // LowPower.powerSave(SLEEP_FOREVER, ADC_OFF, BOD_OFF, TIMER2_ON);
    // LowPower.powerSave(SLEEP_FOREVER, ADC_ON, BOD_ON, TIMER2_ON);

    // LowPower.powerStandby(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    // LowPower.powerStandby(SLEEP_FOREVER, ADC_ON, BOD_OFF);
    // LowPower.powerStandby(SLEEP_FOREVER, ADC_OFF, BOD_ON);
    // LowPower.powerStandby(SLEEP_FOREVER, ADC_ON, BOD_ON);

    // LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    // LowPower.powerDown(SLEEP_FOREVER, ADC_ON, BOD_OFF);
    // LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_ON);
    // LowPower.powerDown(SLEEP_FOREVER, ADC_ON, BOD_ON);

    // Pour le calculateur
    // myradio.init();
    // digitalWrite(9, LOW);
    // digitalWrite(6, HIGH);
    // delay(500);
    // digitalWrite(6, LOW);
    // digitalWrite(9, HIGH);
    // myradio.sleep();
    // LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    // delay(5000);

    /** TP3 **/


}