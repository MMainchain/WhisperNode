#include <Arduino.h>
#include <Bouton.h>
#include "LowPower.h"
#include <RH_RF95.h>
#include <Wire.h>
#include <T2WhisperNode.h>
#include <LoRa.h>

#define BAUD 9600

// Element pins
const int blueButton = 4;
// const int yellowButton = 5;

int countD = 0;
// int countG = 0;

Bouton boutonD(blueButton);
// Bouton boutonG(yellowButton);

// T2Flash myflash;
// RH_RF95 myradio;

T2Message t2message;
uint8_t radioBuf[(T2_MESSAGE_HEADERS_LEN + T2_MESSAGE_MAX_DATA_LEN)];

int serialId = 10;
int id = 0;

void setup() {

    // put your setup code here, to run once:
    Serial.begin(BAUD); // Définition du port de sortie 

    /** TP2 **/

    // Pour mémoire flash
    // myflash.init(T2_WPN_FLASH_SPI_CS);
    // myflash.powerDown();

    // Pour puce LoRa
    // myradio.init();
    // myradio.sleep();

    /** TP3 **/
    Wire.begin();

    LoRa.setPins(10,7,2); 
    if(!LoRa.begin(868E6)) { 
        Serial.println("Starting LoRa failed!"); 
        while(1);
    } else {
        Serial.println("LoRa started");
    }
}

void createChannel() {
    Serial.println("create channel");
    while(1) {
    int packetSize = LoRa.parsePacket();
    // Serial.println(packetSize);
        if (packetSize) {
            int i = 0;
            char *message;
            while (LoRa.available()) {
                message[i++] = (char) LoRa.read();
            }
            Serial.println(message);
        }
    }
}

void initialisation(int idx, int src, int dst, int sdx, int cmd, const char *data, int len) {
    Serial.println("Init");
    uint8_t radioBufLen = 0;

    t2message.idx = idx;
    t2message.src = src;
    t2message.dst = dst;

    t2message.sdx = sdx;
    t2message.cmd = cmd;
    t2message.len = len;
    memcpy(t2message.data, data, len);
    t2message.getSerializedMessage(radioBuf, &radioBufLen);
    LoRa.beginPacket(); 
    LoRa.write(radioBuf, radioBufLen);
    LoRa.endPacket();

    char message[250];
    int idNode = 0;
    int idNetwork = 0;
    int idWhisperNode = 0;
    
    while(idWhisperNode != serialId) {
        int i = 0;
        int packetSize = LoRa.parsePacket();
        if (packetSize) {
            while (LoRa.available() && i < 250) {
                message[i++] = (char) LoRa.read();
            }
            message[i++] = 0;
        }

        if (packetSize) {
            t2message.setSerializedMessage((uint8_t*) message, i);

            idNode = atoi(strtok((char*)t2message.data, ";"));
            idNetwork = atoi(strtok(NULL, ";"));
            idWhisperNode = atoi(strtok(NULL, ";"));

            id = idNode;
        }
    }

    Serial.println(id);
}

int read() {
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        int i = 0;
        char *message;
        while (LoRa.available()) {
            message[i++] = (char) LoRa.read();
        }
        Serial.println(message);
    }
}

int emitData(int idx, int src, int dst, int sdx, int cmd, const char *data, int len) {
    Serial.println("emit data");

    uint8_t radioBufLen = 0;

    t2message.idx = idx;
    t2message.src = src;
    t2message.dst = dst;

    t2message.sdx = sdx;
    t2message.cmd = cmd;
    t2message.len = len;
    memcpy(t2message.data, data, len);
    t2message.getSerializedMessage(radioBuf, &radioBufLen);

    LoRa.beginPacket(); 
    LoRa.write(radioBuf, radioBufLen);
    LoRa.endPacket();

    
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
    // Serial.println(t2message.printMessage());
    // t2message.printMessage();
    // delay(5000);

    boutonD.check();
    countD = boutonD.getNumber();
    if (countD == 1) {
        initialisation(0x00, 0x00, 0x01, 0x01, 0x00, "10;", 3);
    }
    if (countD == 2) {
        createChannel();
    }
    if (countD == 3) {
        emitData(0x00, 0x00, 0x01, 0x01, 0x00, "10;", 3);
    }
    
}