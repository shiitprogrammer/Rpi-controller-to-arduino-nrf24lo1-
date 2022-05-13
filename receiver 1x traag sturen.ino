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
    
    size_t nextIdx = 1; //step over leading {
    nextIdx = data.stoken(value, nextIdx, "', ");
    nextIdx++; 
    nextIdx = data.stoken(type, nextIdx, "', ");
    nextIdx++;
    nextIdx = data.stoken(id, nextIdx, "', ");
    nextIdx++;
    
    String arduinostrval = value.c_str();
    int val = arduinostrval.toInt();
  
    String arduinostrtype = type.c_str();
    int typeval = arduinostrtype.toInt();
 
    String arduinostrid = id.c_str();
    int idval = arduinostrid.toInt();


     switch (typeval) {
    case 1: // buttons
      switch (idval) {
          case 308: //  BTN Y
          digitalWrite(2, HIGH);
          Serial.println("motor aan");
          break;
          case 304: // BTN A
          digitalWrite(2, LOW);
          Serial.println("motor uit");
          break;
          case 310:
          Serial.println("right 90");
          digitalWrite(3, HIGH);
          digitalWrite(4, LOW);

          digitalWrite(5, LOW);
          digitalWrite(6, HIGH);
          break;
          case 311:
          Serial.println("left 90");
          digitalWrite(3, LOW);
          digitalWrite(4, HIGH);

          digitalWrite(5, HIGH);
          digitalWrite(6, LOW);
          break;
      }
    break;

    case 3: //joysticks + arrows
    
        switch (idval) {
          
         
          case 3: // ABS RX
            
            if (val < -50) {
              Serial.print(val);Serial.print("\t");Serial.println("Left");
              digitalWrite(3, LOW);
              analogWrite(4, 100);

              analogWrite(5, 100);
              digitalWrite(6, LOW);
              
            }
            else if ((50 > val) && (-50 < val)) {
              Serial.print(val);Serial.print("\t");Serial.println("Center");
              digitalWrite(3, LOW);
              digitalWrite(4, LOW);
              
              digitalWrite(5, LOW);
              digitalWrite(6, LOW); 
              
            }
            else if (50 < val) {
              Serial.print(val);Serial.print("\t");Serial.println("Right");
              analogWrite(3, 100);
              digitalWrite(4, LOW);

              digitalWrite(5, LOW);
              analogWrite(6, 100); 
              
            }
          break;
          
          case 1: // ABS LY 
           
            if (val < -50) {
              Serial.print(val);Serial.print("\t");Serial.print("Forward");
              
              /////////////linker///////////////
              digitalWrite(3, HIGH);
              digitalWrite(4, LOW);
              /////////////rechter///////////////
              digitalWrite(5, HIGH);
              digitalWrite(6, LOW);

            }
            else if ((50 > val) && (-50 < val)) {
              Serial.print(val);Serial.print("\t");Serial.print("Brake");
              /////////////linker///////////////
              digitalWrite(3, LOW);
              digitalWrite(4, LOW);
              /////////////rechter///////////////
              digitalWrite(5, LOW);
              digitalWrite(6, LOW);

            }
            else if (50 < val) {
              Serial.print(val);Serial.print("\t");Serial.print("Reverse");
              
              /////////////linker///////////////
              digitalWrite(3, LOW);
              digitalWrite(4, HIGH);
              /////////////rechter///////////////
              digitalWrite(5, LOW);
              digitalWrite(6, HIGH);

            }
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
 Serial.println("receiver ok");
 
 }
 
void loop()
 {
  
  if (radio.available()) {
    radio.read(&rcvd, sizeof(rcvd));
    removezeros();
   

   }
  
   
  delay(1);
 }
