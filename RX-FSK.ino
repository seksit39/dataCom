// Recieve FSK


int input,max,prev,currentTime,prevTime,period,totalTime;
float currentFrequency,prevFrequency;
boolean check;

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
      int diff = abs(currentFrequency - prevFrequency);
      if(diff < 100)
        totalTime += period; 
      else{
         if(400 < currentFrequency && currentFrequency > 600){
            int cycle = round(totalTime/2000);
            for(int i=0 ; i<cycle ; i++)
              Serial.print("0");
         }
         else if(900 < currentFrequency && currentFrequency > 1100){
            int cycle = round(totalTime/1000);
            for(int i=0 ; i<cycle ; i++)
              Serial.print("1");
         } 
         totalTime = 0; 
      }      
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
