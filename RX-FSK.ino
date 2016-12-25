// Recieve FSK


int input,max,prev,currentTime,prevTime,period;
float currentFrequency,prevFrequency;
boolean check;

void setup(void) 
{
/*  
  // defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// set prescale to 16
cbi(ADCSRA,ADPS2) ;
cbi(ADCSRA,ADPS1) ; //
cbi(ADCSRA,ADPS0) ;
*/
  Serial.begin(115200);

  long first = micros();
  long cout = 0;
  while(micros()-first < 1000000){
    int temp = analogRead(A0);
    //Serial.println(temp);
    cout++;
  }
  
  Serial.print(cout);
  Serial.println(" Hz");

}

void loop(void) 
{
    input = analogRead(A0);
    
    if(input > 600 && check == true){
      currentTime = micros();
      period =  currentTime -  prevTime;
      currentFrequency = 1000000/period;
      
      prevFrequency = currentFrequency;
      prevTime = currentTime;
      Serial.println(currentFrequency);
      check = false;
    }
    if(input>max){
    max=input;
    }
    if(max-input > 400 && check==false){
    check = true;
    }
  
}
