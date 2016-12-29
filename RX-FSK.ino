// Recieve FSK

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

int input,max,prev,currentTime,prevTime,period,cout = 0,totalTime = 0;
float currentFrequency,prevFrequency;
boolean check,cp = true;

void setup(void) 
{
  sbi(ADCSRA,ADPS2) ;
  cbi(ADCSRA,ADPS1) ;
  cbi(ADCSRA,ADPS0) ;
  
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
    
    if(input > 750 && check == true){
      currentTime = micros();
      period =  currentTime -  prevTime;
      currentFrequency = 1000000/period;
      
         if(300 < currentFrequency && currentFrequency < 700){
              if(cp){
                Serial.print("0 ");
                cout++;
              }
               cp = !cp;
              
         }
         else if(800 < currentFrequency && currentFrequency < 1500){
              if(cp){
                Serial.print("1 ");
                cout++;
                delayMicroseconds(2200);
              }
                
              cp = !cp;
         }  
      if(cout == 10){
        Serial.println();
        cout = 0;      
      }
      prevFrequency = currentFrequency;
      prevTime = currentTime;
      //Serial.println(currentFrequency);
      check = false;
    }
    if(input>max){
    max=input;
    }
    if(max-input > 50 && check==false){
    check = true;
    }
  
}
