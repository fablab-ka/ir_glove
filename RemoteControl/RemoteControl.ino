#include <IRLibDecodeBase.h>  //We need both the coding and
#include <IRLibSendBase.h>    // sending base classes
#include <IRLib_P01_NEC.h>    //Lowest numbered protocol 1st
#include <IRLib_P02_Sony.h>   // Include only protocols you want
#include <IRLib_P03_RC5.h>
#include <IRLib_P04_RC6.h>
#include <IRLib_P05_Panasonic_Old.h>
#include <IRLib_P07_NECx.h>
#include <IRLib_HashRaw.h>    //We need this for IRsendRaw
#include <IRLibCombo.h>       // After all protocols, include this

IRdecode myDecoder;
IRsend mySender;
#include <IRLibRecv.h>
IRrecv myReceiver(A2); //pin number for the receiver


void setup() {
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  pinMode(A1, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  myReceiver.enableIRIn(); // Start the receiver
}


void loop() {
  delay(100);
  if (myReceiver.getResults()) {
    myDecoder.decode();
    //myDecoder.dumpResults();
    long value = myDecoder.value;
    Serial.print("New Code received: ");
    Serial.println(value, HEX);
    myReceiver.enableIRIn();
    switch (value) {
      case 0xCD02F:
        digitalWrite(13, HIGH);
        break;
      case 0xC30CF:
        digitalWrite(13, LOW);
        break;
    }
  }
}
