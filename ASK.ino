/*
created by sek su
uncomment sender or reciever to select
*/
#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <Adafruit_ADS1015.h>

//#define SENDER
//#define RECIEVER

Adafruit_ADS1115 ads;
Adafruit_MCP4725 dac;
uint16_t a = 0;
uint16_t input[10] = {0,0,0,0,0,0,0,0,0,0};

const uint16_t sine[32] =
{
  2048, 2447, 2831, 3185, 3495, 3750, 3939, 4056,
  4095, 4056, 3939, 3750, 3495, 3185, 2831, 2447,
  2048, 1648, 1264,  910,  600,  345,  156,   39,
     0,   39,  156,  345,  600,  910, 1264, 1648
};

void setup(void) {
  
  Serial.begin(9600);
  dac.begin(0x62);
  ads.begin();  
}

void loop(void) {
#ifdef SEND
      if(Serial.available() != 0){
        for(int i=0 ; i<10 ; i++){
          input[i] = Serial.parseInt(); 
          Serial.parseInt();
        } 
        for(int k=0 ; k<10 ; k+=2){
          if(input[k] == 0){
            if(input[k+1] == 0){
              a = 1;
            }
            else if(input[k+1] == 1){
              a = 2;
            }
          }
          else if(input[k] == 1){
            if(input[k+1] == 0){
              a = 3;
            }
            else if(input[k+1] == 1){
              a = 4;
            }
          }
          for(int j=0 ; j<4 ; j++){
              for(int i=0 ; i<32 ; i++){
                dac.setVoltage(sine[i]*a/4, false);
              }
          }
        }   
      }
  

#endif
#ifdef RECIEVER
  uint16_t tmp = ads.readADC_SingleEnded(0);
#endif
}
