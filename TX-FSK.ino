/*
created by sek su
uncomment sender or reciever to select
sine delay
20  micros 1500 Hz
100 micros 1000 Hz
350 micros 500  Hz
*/
#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <Adafruit_ADS1015.h>

#define SENDER
//#define RECIEVER

#ifdef SENDER
  Adafruit_MCP4725 dac;
  uint16_t a = 0;
  uint16_t input[10] = {0,0,0,0,0,0,0,0,0,0};
  //const uint16_t sine[16] = {0,156,600,1264,2048,2831,3495,3939,4095,3939,3495,2831,2048,1264,600,156}; // At 430 Hz
  //const uint16_t sine[8]  = {2048,3495,4095,3495,2048,600,0,600};  // At 870 Hz
  const uint16_t sine[4]  = {2048,4095,2048,0};                      // At 1700 Hz     
  int del = 0;
#endif

#ifdef RECIEVER
  Adafruit_ADS1115 ads;
  int sum = 0;
  int max = 0;
  int prev = 0;
  int check = true;
  int output = -1;
  int cout = 0; 
#endif

void setup(void) {
  
  Serial.begin(115200);
  
  #ifdef SENDER
    dac.begin(0x62);
  #endif
  
  #ifdef RECIEVER
    ads.begin();  
  #endif
  
}

void loop(void) {
  
#ifdef SENDER
/*
    if(Serial.available() > 0){         // For test sine delay
      del = Serial.parseInt();
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
        
        //for(int x=0 ; x<100 ; x++)
        for(int k=0 ; k<10 ; k++){
          
          if(input[k] == 0){                    // 500 Hz
            del = 350; 
            for(int j=0 ; j<2 ; j++)
              for(int i=0 ; i<4 ; i++){
                dac.setVoltage(sine[i], false);
                delayMicroseconds(del);
              }
          }
          else if(input[k] == 1){               // 1000 Hz
            del = 100; 
            for(int j=0 ; j<3 ; j++)
              for(int i=0 ; i<4 ; i++){
                dac.setVoltage(sine[i], false);
                delayMicroseconds(del);
              }
          }
        }   
      }
      dac.setVoltage(0, false);

#endif
#ifdef RECIEVER
  output = -1;
  sum = 0;


  
  //Serial.println(tmp);
  
  if(-3500<tmp && tmp<3500){
    
    if(check == true){
      if(-3500<max && max<2000)
        output=-1;
      else if(2000<max && max<21000)
        output=0;
      else if(21000<max && max<29998)
        output=1;
      
      if(output!=-1){
          cout++;
          Serial.print(output);
          if(cout == 10){
            Serial.println();
            cout = 0;
          }
      }
      check = false;
      max = 0;
    }
  }
  if(tmp>max){
    max=tmp;
  }
  if(max-tmp > 1000 && check==false){       //check and show output 
    check = true;
  }
  prev = tmp;  

#endif
  }
