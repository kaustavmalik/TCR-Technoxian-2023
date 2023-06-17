#include <SPI.h>  
#include "RF24.h"

#define joyX A0
#define joyY A2
int SW= 3;

int lValue, rValue;

RF24 myRadio (7, 8);
byte addresses[][6] = {"0"};

struct package {
  int lSpeed = 0;
  int rSpeed = 0;
  int s = 0;
};


typedef struct package Package;
Package dataTransmit;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  myRadio.begin();  
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS );
  pinMode(SW,INPUT_PULLUP);
  
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}

void loop() 
{
  myRadio.stopListening();

  lValue = analogRead(joyX);
  rValue = analogRead(joyY);
  dataTransmit.s = digitalRead(SW);

  dataTransmit.lSpeed = (255./512.)*lValue-255.;
  if(lValue == 518)
  {
    dataTransmit.lSpeed=0;
  }
  Serial.print(dataTransmit.lSpeed);

  Serial.print("    ");

  dataTransmit.rSpeed = (255./512.)*rValue-255.;
  if(rValue == 501)
  {
    dataTransmit.rSpeed=0;
  }
  Serial.println(dataTransmit.rSpeed);

  if(dataTransmit.s == 0)
  {
    Serial.println("STOP");
  }

  myRadio.write(&dataTransmit, sizeof(dataTransmit));
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}
