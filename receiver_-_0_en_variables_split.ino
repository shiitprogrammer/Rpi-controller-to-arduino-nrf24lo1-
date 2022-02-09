#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.H>
#include <SafeString.h>


/*
pins connections
 
 
 
*/


 
RF24 radio(9, 8);

char rcvd[32] = "";




void removezeros() {
    
    int i = 0;
    
    createSafeString(value, 20);
    createSafeString(type, 20);
    createSafeString(id, 20);
    
  
    cSFA(data,rcvd);
    while (data[i] == '0') {
       i++;
    
    }
    data.remove(0, i);
    //Serial.println(appCmd);
    size_t nextIdx = 1; //step over leading {
    nextIdx = data.stoken(value, nextIdx, "', ");
    nextIdx++; //step over delimiter
    nextIdx = data.stoken(type, nextIdx, "', ");
    nextIdx++; //step over delimiter
    nextIdx = data.stoken(id, nextIdx, "', ");
    nextIdx++; //step over delimiter
    // can trim tokens if needed e.g. token1.trim()
    String arduinostrval = value.c_str();
    int val = arduinostrval.toInt();
    
    //Serial.print(val);
    //Serial.print("/");
    
    String arduinostrtype = type.c_str();
    int typeval = arduinostrtype.toInt();

    //Serial.print(typeval);
    //Serial.print("/");
    
    
    String arduinostrid = id.c_str();
    int idval = arduinostrid.toInt();

    //Serial.println(idval);
     switch (typeval) {
    case 1: // buttons
      
    break;

    case 3: //joysticks + arrows
        switch (idval) {
          case 0: // ABS LX 
            Serial.println("LX");
          break;

          case 1: // ABS LY 
            Serial.println("LY");
          break;
          
          case 3: // ABS RX
            Serial.println("RX");
          break;

          case 4: // ABS RY 
            Serial.println("RY");
          break;
        }
    break;
    }
    
  
  }     
  
    

  



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
 //radio.printDetails();
 Serial.println("receiver ok");
 
 }
 
void loop()
 {
  
  if (radio.available()) {
    radio.read(&rcvd, sizeof(rcvd));
    removezeros();
   

   }
  
   
  delay(100);
 }
