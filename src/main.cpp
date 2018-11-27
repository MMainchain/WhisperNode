// Definition de la taille max du payload
#define T2_MESSAGE_MAX_DATA_LEN 15
#include <Arduino.h>
#include <RH_RF95.h>
#include <T2WhisperNode.h>
#include <LoRa.h>

/// A MODIFIER
/// myNetID = mettre ici le réseau de la passerelle
/// mySerialNumber = mettre le serial number du WhisperNode

////////////////////////////////////////////
/// Configuration WhisperNode
int myNetID = 1; // Definition du réseau
int myID = 0; // ID du WhisperNode
int mySerialNumber = 10; // Numero de série.
int myChannel =0;
////////////////////////////////////////////
////////////////////////////////////////////

// Radio
uint8_t radioBuf[(T2_MESSAGE_HEADERS_LEN + T2_MESSAGE_MAX_DATA_LEN)];
T2Message myMsg;

// Tableau stockant les valeurs du payload
char *array[10];
int arrayint[10];

// fonction permettant d'analyser le payload d'une trame
// stocke les valeurs dans le tableau arrayint
// premier parametre dans arrayint[0], deuxième dans arrayint[1] etc...
int parseString (char *s) {
    int i = 0;
    char *p = strtok (s, ";");
    while ((p != NULL) & (i<9)) {
        array[i++] = p;
        p = strtok (NULL, ";");
    }
    while (i<10) array[i++] = NULL;
    for (i = 0; i < 10; ++i) {
      if (array[i]!=NULL) {
        arrayint[i]=atoi(array[i]);
        }
    }
    return 0;
}

int sendLORA(int idx,int src, int dst, int sdx, int cmd, const char *data,int len) {
	uint8_t radioBufLen = 0;
	myMsg.idx = idx;
	myMsg.src = src;
	myMsg.dst = dst;
	myMsg.sdx = sdx;
	myMsg.cmd = cmd;
	myMsg.len = len;
	memcpy(myMsg.data,data,len);

	myMsg.getSerializedMessage(radioBuf, &radioBufLen);
  myMsg.printMessage();

  LoRa.beginPacket();
  LoRa.write(radioBuf,radioBufLen);
  LoRa.endPacket();
  return 1;
}

char buf[10]; // Buffeur utilisé pour l'envois de la trame
int len;      // longueur de la trame

int sendGiveMeANodeID(){
  itoa(mySerialNumber,buf,10);
  len = strlen(buf);
  buf[len ] = ';';
  len = len +1;
	//	int sendLORA(int idx,int src, int dst, int sdx, int cmd, const char *data,int len)
	return sendLORA( 0x01, myID,  0x01,  0x01,  0x00, buf, len);
}

int sendGiveMeAChannelAndField(){
	buf[0]=0;
	//	int sendLORA(int idx,int src, int dst, int sdx, int cmd, const char *data,int len)
	return sendLORA( myNetID, myID,  0x01,  0x02,  0x00, buf, 1);
}

int sendMyValue(int value){
	itoa(value,buf,10);
  len = strlen(buf);
  buf[len] = ';';
  len = len +1;
	//	int sendLORA(int idx,int src, int dst, int sdx, int cmd, const char *data,int len)
	return sendLORA( myNetID, myID,  0x01,  0x03,  0x01, buf, len);
}

void setup() {
    Serial.begin(9600);
    Serial.println("Radio Init");
    LoRa.setPins(10,7,2);
      if (!LoRa.begin(868E6)) {
        	Serial.println("Starting LoRa failed!");
        	while (1);
    	}
}

char message[255]; //buffeur de reception d'un message
uint8_t lmes; //longeur du message recu

int receivLoRa(){
  int lmes=0;
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");
    // read packet
    while ((LoRa.available()) && (lmes<250)) {
      message[lmes++] = (char) LoRa.read();
    }
    message[lmes++] =0;
    myMsg.setSerializedMessage((uint8_t *) message, lmes);
    myMsg.printMessage();
    return 1;
  }
  return -1;
}

unsigned long int envoisSendMyID=0;
unsigned long int envoisdonnees=0;
unsigned long int envoisSendMyChannel=0;

void loop() {
  /// RECEPTION
  if (receivLoRa()==1) {
      // Recoit on un ID ???
      if ((myMsg.idx == 0x1)&&(myMsg.dst==0x00)&&(myMsg.src==0x01)&&(myMsg.sdx=0x01)) {
        parseString((char *) myMsg.data);
          Serial.print("Reception d'un ID : ");
          Serial.print(arrayint[0]);
          Serial.print(" NETID : ");
          Serial.print(arrayint[1]);
          Serial.print(" au numero de serie : ");
          Serial.println(arrayint[2]);

        if (mySerialNumber==arrayint[2]) {
          // Cette affectation est pour moi
            myID=arrayint[0];
            myNetID=arrayint[1];
        }
      }

      // Recoit on un Channel ???
      if ((myMsg.idx == myNetID)&&(myMsg.dst==myID)&&(myMsg.src==0x01)&&(myMsg.sdx=0x02)) {
            parseString((char *) myMsg.data);
            Serial.print("Reception d'un Channel : ");
            Serial.print(arrayint[0]);
            Serial.print(" Field : ");
            Serial.println(arrayint[1]);
            myChannel=arrayint[0];
      }

    }
    /// FIN PARTIE RECEPTION

    /// DEMANDE ID toutes les 500 millis secondes
	if (myID==0) {
	  if ((millis()-envoisSendMyID) > 500) {
          Serial.println("J'ai besoin d'un ID");
		  sendGiveMeANodeID();
		  envoisSendMyID=millis();
	  }
	}

     if ((myID!=0)&&(myChannel==0)) {
       if ((millis()-envoisSendMyChannel) > 500) {
           Serial.println("J'ai besoin d'un Channel");
             sendGiveMeAChannelAndField();
             envoisSendMyChannel=millis();
         }
     }

     /// Envois donnees toutes les 2 secondes
     if ((myID!=0)&&(myChannel!=0)) {
       if ((millis()-envoisdonnees) > 2000) {
           Serial.println("Envois Données");
             sendMyValue(12);
             envoisdonnees=millis();
         }
      }


}