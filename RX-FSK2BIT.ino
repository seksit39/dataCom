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
/*
  long first = micros();
  long cout = 0;
  while(micros()-first < 1000000){
    int temp = analogRead(A0);
    //Serial.println(temp);
    cout++;
  }
  
  Serial.print(cout);
  Serial.println(" Hz");
*/
}

void loop(void) 
{   
    input = analogRead(A0);
    if(input > 800 && check == true){
      currentTime = micros();
      period =  currentTime -  prevTime;
      currentFrequency = 1000000/period;


         if(1125 < currentFrequency && currentFrequency < 1375){
              if(cp){
                Serial.print("1 1 ");
                cout++;
              } 
              cp = !cp;
         } 
         else if(875 < currentFrequency && currentFrequency < 1125){
              if(cp){
                Serial.print("1 0 ");
                cout++;
              } 
              cp = !cp;
         }
         else if(625 < currentFrequency && currentFrequency < 875){
              if(cp){
                Serial.print("0 1 ");
                cout++;
              } 
              cp = !cp;
         }       
         else if(375 < currentFrequency && currentFrequency < 625){
              if(cp){
                Serial.print("0 0 ");
                cout++;
              }
               cp = !cp;     
         }
   
      if(cout == 5){
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
    if(max-input > 30 && check==false){
    check = true;
    }
  
}
