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


void right90() {

    
}



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
          case 310:
          digitalWrite(3, HIGH);
          digitalWrite(4, LOW);

          digitalWrite(5, LOW);
          digitalWrite(6, HIGH);
          break;
          case 311
          digitalWrite(3, LOW);
          digitalWrite(4, HIGH);

          digitalWrite(5, HIGH);
          digitalWrite(6, LOW);
          break;
      }
    break;

    case 3: //joysticks + arrows
    char richting ="center";
        switch (idval) {
          //case 0: // ABS LX 
          //break;
          
          case 3: // ABS RX
            
            if (val < -50) {
              Serial.print(val);Serial.print("\t");Serial.println("Left");
              richting = "left";
              
            }
            else if ((50 > val) && (-50 < val)) {
              Serial.print(val);Serial.print("\t");Serial.println("Center");
              richting = "center";
              
            }
            else if (50 < val) {
              Serial.print(val);Serial.print("\t");Serial.println("Right");
              richting = "right";
              
            }
          return(richting);

          case 1: // ABS LY 
          int speedlinks = abs(val) ;
          int speedrechts = abs(val) ;  
            if (val < -50) {
              Serial.print(val);Serial.print("\t");Serial.println("Forward");
              if (richting = "right") {
                speedlinks = abs(val);
                speedrechts = abs(val) - 50;
              }
              else if (richting = "center") {
                speedlinks = abs(val);
                speedrechts = abs(val);
              }
              else if (richting = "left") {
                speedlinks = abs(val) - 50;
                speedrechts = abs(val);
              }
              /////////////linker///////////////
              analogWrite(3, speedlinks);
              analogWrite(4, 0);
              /////////////rechter///////////////
              analogWrite(5, speedrechts);
              analogWrite(6, 0);

            }
            else if ((50 > val) && (-50 < val)) {
              Serial.print(val);Serial.print("\t");Serial.println("Brake");
            
              /////////////linker///////////////
              analogWrite(3, 0);
              analogWrite(4, 0);
              /////////////rechter///////////////
              analogWrite(5, 0);
              analogWrite(6, 0);

            }
            else if (50 < val) {
              Serial.print(val);Serial.print("\t");Serial.println("Reverse");
              if (richting = "right") {
                speedlinks = abs(val);
                speedrechts = abs(val) - 50;
              }
              else if (richting = "center") {
                speedlinks = abs(val);
                speedrechts = abs(val);
              }
              else if (richting = "left") {
                speedlinks = abs(val) - 50;
                speedrechts = abs(val);
              }
              /////////////linker///////////////
              analogWrite(3, 0);
              analogWrite(4, speedlinks);
              /////////////rechter///////////////
              analogWrite(5, 0);
              analogWrite(6, speedrechts);

            }
          break;
          //case 4: // ABS RY 
          //break;
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
