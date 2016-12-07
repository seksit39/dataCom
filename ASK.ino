#include <Wire.h>
#include <Adafruit_MCP4725.h>

#define pi 3.14159265
#define frequency  100

Adafruit_MCP4725 dac;

float amplitude = 0.5;

void setup(void) {
  
  Serial.begin(9600);
  dac.begin(0x62);      // is default
    
}

void loop(void) {

      int ask = 1024*(0.5+(amplitude*sin(2*pi*frequency*micros()/1000000)));

      dac.setVoltage(ask, false);

}
