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

// Count of click
int countD = 0;

// Define button
Bouton boutonD(blueButton);

// Define message
T2Message t2message;

// Maaaaagic
uint8_t radioBuf[(T2_MESSAGE_HEADERS_LEN + T2_MESSAGE_MAX_DATA_LEN)];

// Serial id of WhisperNode
const int serialId = 10;

// Given id from remote server
int id = 0;

// Given id network
int idNetwork = -1;

// Given channel id from remote server
int channelId;

/**
 * Setup function, first function to be called
 */
void setup() {

    Serial.begin(BAUD); // Définition out port 

    Wire.begin();
    LoRa.setPins(10,7,2); 
    if(!LoRa.begin(868E6)) { 
        Serial.println("Starting LoRa failed!"); 
        while(1);
    } else {
        Serial.println("LoRa started");
    }
}

/**
 * Initialisation : called when 1 press to right button
 */
void initialisation(int idx, int src, int dst, int sdx, int cmd, const char *data, int len) {
    Serial.println("Initializing...");
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
    Serial.print("Initialized. Given id = ");
    Serial.println(id);
}

/**
 * Create channel : called when 2 press to right button
 */
void createChannel(int idx, int src, int dst, int sdx, int cmd, const char *data, int len) {
    Serial.println("Creating channel...");
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
    int channel = -1;
    int field = 0;
    
    while(channel < 0) {
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

            channel = atoi(strtok((char*)t2message.data, ";"));
            field = atoi(strtok(NULL, ";"));

            channelId = channel;
        }
    }

    Serial.print("Channel id given = ");
    Serial.println(channelId);
}

/**
 * Send message : called when 3 press to right button
 */
int emitData(int idx, int src, int dst, int sdx, int cmd, const char *data, int len) {
    Serial.println("Sending message...");
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

    Serial.println("Message sent.");
}

/**
 * Loop function, second function to be called
 * Works like a while(true)
 */
void loop() {
    // Verify button D
    boutonD.check();
    // Count number of press on it
    countD = boutonD.getNumber();
    // Init if pressed one time
    if (countD == 1) {
        initialisation(0x00, 0x00, 0x01, 0x01, 0x00, "10;", 3);
    }
    // Create channel if pressed two times
    if (countD == 2) {
        createChannel(idNetwork, id, 0x01, 0x02, 0x00, "", 0);
    }
    // Emit data if pressed three times
    if (countD == 3) {
        emitData(idNetwork, id, 0x01, 0x03, 0x01, "Message;", 8);
    }
}