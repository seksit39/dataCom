/*
created by sek su
uncomment sender or reciever to select
*/
#include <Wire.h>
#include <Adafruit_MCP4725.h>

//#define SENDER
//#define RECIEVER

Adafruit_MCP4725 dac;

int input[10] = {0,0,0,0,0,0,0,0,0,0};

const uint16_t sine[32] =
{
  2048, 2447, 2831, 3185, 3495, 3750, 3939, 4056,
  4095, 4056, 3939, 3750, 3495, 3185, 2831, 2447,
  2048, 1648, 1264,  910,  600,  345,  156,   39,
     0,   39,  156,  345,  600,  910, 1264, 1648
};

void setup(void) {
  
  Serial.begin(9600);
  dac.begin(0x62);      // is default
    
}

void loop(void) {
#ifdef SEND
      if(Serial.available() != 0){
        int tmp = Serial.parseInt();
        if(tmp > 0){
          multipi = tmp;
          Serial.println(multipi);
        } 
      }
    for(int a=1 ; a<5   ; a++){
      for(int b=0 ; b<2 ; b++){
          for(int i=0 ; i<32 ; i++){
            dac.setVoltage(sine[i]*a/4, false);
          }
      }
    }
}
