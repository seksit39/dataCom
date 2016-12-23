// For find speed of ADC(Hz) 
#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */

void setup(void) 
{
  Serial.begin(9600);
  
  ads.begin();
  int first = millis();
  int cout = 0;
  while(millis()-first < 1000){
    int adc0 = ads.readADC_SingleEnded(0);
    cout++;
  }
  Serial.print(cout);
}

void loop(void) 
{
  

  
  
  
}
