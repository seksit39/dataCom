/*
created by sek su
uncomment sender or reciever to select
sine delay
none       1736 Hz
20  micros 1500 Hz
50  micros 1250 Hz
100 micros 1000 Hz
190 micros 750  Hz
350 micros 500  Hz
*/
#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <Adafruit_ADS1015.h>

#define SENDER

  Adafruit_MCP4725 dac;
  uint16_t a = 0;
  uint16_t input[10] = {0,0,0,0,0,0,0,0,0,0};
  //const uint16_t sine[16] = {0,156,600,1264,2048,2831,3495,3939,4095,3939,3495,2831,2048,1264,600,156}; // At 430 Hz
  //const uint16_t sine[8]  = {2048,3495,4095,3495,2048,600,0,600};  // At 870 Hz
  const uint16_t sine[4]  = {2048,4095,2048,0};                      // At 1700 Hz     
  int del = 0;

void setup(void) {
  
  Serial.begin(115200);
  dac.begin(0x62);
  
}

void loop(void) {
/*

    if(Serial.available() > 0){         // For test sine delay
      del = Serial.parseInt();
      Serial.println(del);
      Serial.parseInt();
    }
    for(int i=0 ; i<4 ; i++){
       dac.setVoltage(sine[i], false);
       delayMicroseconds(del);
    }
*/

      if(Serial.available() > 0){
        for(int i=0 ; i<10 ; i++){
          input[i] = Serial.parseInt();
          Serial.print(input[i]);  
          Serial.print(" ");
        }
        Serial.println();
        Serial.parseInt();
        
        
        
        for(int i=0 ; i<4 ; i++){
            dac.setVoltage(sine[i], false);
            delayMicroseconds(460);
        }
        //for(int x=0 ; x<10 ; x++)
        for(int k=0 ; k<10 ; k+=2){
          
          if(input[k] == 0){                
            if(input[k+1] == 0)                 // for input 00 - 500 Hz
              for(int j=0 ; j<2 ; j++)
                for(int i=0 ; i<4 ; i++){
                  dac.setVoltage(sine[i], false);
                  delayMicroseconds(460);
                }
             else if(input[k+1] == 1)           // for input 01 - 750 Hz
              for(int j=0 ; j<3 ; j++)
                for(int i=0 ; i<4 ; i++){
                  dac.setVoltage(sine[i], false);
                  delayMicroseconds(240);
                }
          }
          else if(input[k] == 1){               // for input 10 - 1000 Hz
            if(input[k+1] == 0)
              for(int j=0 ; j<4 ; j++)
                for(int i=0 ; i<4 ; i++){
                  dac.setVoltage(sine[i], false);
                  delayMicroseconds(130);
                }
            else if(input[k+1] == 1)            // for input 11 - 1250 Hz
              for(int j=0 ; j<5 ; j++)      
                for(int i=0 ; i<4 ; i++){
                  dac.setVoltage(sine[i], false);
                  delayMicroseconds(80);
          } 
        }   
      }
      dac.setVoltage(0, false);
      }

  }
