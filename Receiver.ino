#include <SPI.h>  
#include "RF24.h"

RF24 myRadio (7, 8);
byte addresses[][6] = {"10"};

struct package {
  int lSpeed = 0;
  int rSpeed = 0;
  int s = 0;
};


typedef struct package Package;
Package dataRecieve;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  myRadio.begin();  
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS );
  
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}

void loop() {
  if ( myRadio.available()) {
    while (myRadio.available()){
      myRadio.read( &dataRecieve, sizeof(dataRecieve) );
    
    Serial.println("Recieve: ");
    Serial.print("Package:");
    Serial.print(dataRecieve.lSpeed);
    Serial.print("\n");
    Serial.println(dataRecieve.rSpeed);
  }
  Serial.println("Available");
  }
  delay(150);
}
