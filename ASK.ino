/*
created by sek su
uncomment sender or reciever to select
*/
#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <Adafruit_ADS1015.h>

//#define SENDER
//#define RECIEVER

#ifdef SENDER
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
#endif

#ifdef RECIEVER
  Adafruit_ADS1115 ads;
  uint16_t sum = 0;
  uint16_t max = 0;
  uint16_t prev = 0;
  boolean 
#endif

void setup(void) {
  
  Serial.begin(9600);
  
  #ifdef SENDER
    dac.begin(0x62);
  #endif
  
  #ifdef RECIEVER
  ads.begin();  
  #endif
  
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
            if(input[k+1] == 0)
              a = 0;
            else if(input[k+1] == 1)
              a = 1;
          }
          else if(input[k] == 1){
            if(input[k+1] == 0)
              a = 2;
            else if(input[k+1] == 1)
              a = 3;
          }
          for(int j=0 ; j<4 ; j++){
              for(int i=0 ; i<32 ; i++)
                dac.setVoltage(sine[i]*(a+1)/4, false);
          }
        }   
      }
      dac.setVoltage(0, false);

#endif
#ifdef RECIEVER
  sum = 0;
  for(int i=0 ; i<cout ; i++){
    sum += ads.readADC_SingleEnded(0);
  }
  uint16_t tmp = sum/cout;

  if(tmp>prev && -10<tmp && tmp<10)
    max = 0;
  else if(tmp>max)
    max=tmp;
  else if(tmp<max && check==false){
      int output = 0;                //check and show output 
      if(-3333<max && max>3333)
        output=-1;
      else if(3333<max && max<9999)
        output=0;
      else if(9999<max && max<16665)
        output=1;
      else if(16665<max && max<23332)
        output=2;
      else if(23332<max && max<29998)
        output=3;
      
      if(output!=-1)
        Serial.print((BIN)output);
  }
  prev = tmp;  

#endif
}
