// For find speed of ADC(Hz) 
#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */

void setup(void) 
{
  
  // defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// set prescale to 16
cbi(ADCSRA,ADPS2) ;
cbi(ADCSRA,ADPS1) ;
cbi(ADCSRA,ADPS0) ;

  Serial.begin(115200);

  long first = micros();
  long cout = 0;
  while(micros()-first < 1000000){
    int temp = analogRead(A0);
    cout++;
  }
  
  Serial.print(cout);
  Serial.print(" Hz");

}
/*
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
*/
void loop(void) 
{
  

  
  
  
}
