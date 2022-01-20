#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.H>


/*
pins connections
 

 
 
*/


 
RF24 radio(9, 8);

char rcvd[50] = "";
 
void setup()
 {
 Serial.begin(9600);
 printf_begin();
 radio.begin();
 
 
 radio.openReadingPipe(1, 0xE8E8F0F0E1LL);
 radio.setChannel(0x77);
 radio.setPALevel(RF24_PA_MIN);
 radio.enableDynamicPayloads();
 radio.startListening();
 radio.printDetails();
 Serial.println("receiver ok");
 
 }
 
void loop()
 {
  
  if (radio.available()) {
    radio.read(&rcvd, sizeof(rcvd));
    Serial.println(rcvd);
  }
  
  
  
  
  delay(100);
 }
