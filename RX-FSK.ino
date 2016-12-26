// Recieve FSK


int input,max,prev,currentTime,prevTime,period,totalTime = 0;
float currentFrequency,prevFrequency;
boolean check,cp = true;

void setup(void) 
{
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
      
         if(400 < currentFrequency && currentFrequency < 600){
              if(cp)
                Serial.print("0");
               cp = !cp;
              
         }
         else if(900 < currentFrequency && currentFrequency < 1100){
              if(cp)
                Serial.print("1");
              cp = !cp;
         }  
            
      prevFrequency = currentFrequency;
      prevTime = currentTime;
      //Serial.println(currentFrequency);
      check = false;
    }
    if(input>max){
    max=input;
    }
    if(max-input > 400 && check==false){
    check = true;
    }
  
}
