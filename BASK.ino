/*
created by sek su
uncomment sender or reciever to select
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
  //uint16_t input[10] = {0,0,0,1,1,0,1,1,1,1};
  const uint16_t sine[32] =
  {
       0,   39,  156,  345,  600,  910, 1264, 1648,
    2048, 2447, 2831, 3185, 3495, 3750, 3939, 4056,
    4095, 4056, 3939, 3750, 3495, 3185, 2831, 2447,
    2048, 1648, 1264,  910,  600,  345,  156,   39 
  };
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
  
  Serial.begin(9600);
  
  #ifdef SENDER
    dac.begin(0x62);
  #endif
  
  #ifdef RECIEVER
  ads.begin();  
  #endif
  
}

void loop(void) {
#ifdef SENDER
      if(Serial.available() > 0){
        for(int i=0 ; i<10 ; i++){
          input[i] = Serial.parseInt();
          Serial.print(input[i]);  
          Serial.print(" ");
        }
        Serial.println();
        Serial.parseInt();
        for(int x=0 ; x<10 ; x++)
        for(int k=0 ; k<10 ; k++){
          if(input[k] == 0){
            a = 0; 
          }
          else if(input[k] == 1){
            a = 1;
          }
          for(int j=0 ; j<1 ; j++){
              for(int i=0 ; i<32 ; i++){
                dac.setVoltage(sine[i]*(a+1)/2, false);
                delayMicroseconds(1300);
              }
          }
        }   
      }
      dac.setVoltage(0, false);

#endif
#ifdef RECIEVER
  output = -1;
  sum = 0;

  int tmp = ads.readADC_SingleEnded(0);
  
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
