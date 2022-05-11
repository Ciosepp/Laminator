#include <NTC.h>

#define outputPin 0
#define readyLedPin 1

double R0 = 20000;
double Rh = 100000;
double B = 3950;
double VCC = 5.0000;
int ADC_PIN = A3;

int setTempPin = A1;
double tDelta = 3;
double  setTemp;

NTC ntc(R0 ,B ,Rh ,VCC ,ADC_PIN);

void setup(){

	pinMode(outputPin, OUTPUT);
	pinMode(readyLedPin, OUTPUT);
 
  pinMode(setTempPin, INPUT);
  pinMode(ADC_PIN, INPUT);
 
}
int bounceCount =0;
bool Ready =false;
int val =0;

void loop(){
    if(setTemp != map(analogRead(setTempPin),0 ,1023 ,50.00 , 150.00 )){
        setTemp = map(analogRead(setTempPin),0 ,1023 ,50.00 , 150.00 );
        digitalWrite(readyLedPin, 0);
    }
	
    Serial.println(ntc.getTemperatureC());

	  if(ntc.getTemperatureC() >= (setTemp+tDelta)){
      
		    digitalWrite(outputPin, 0);
		    if(!Ready){
		       bounceCount ++;
           Ready = true;
		    }
	  }
    else{
      digitalWrite(outputPin, 1);
      Ready =false;
    }
    if(Ready && (bounceCount>3)){
        digitalWrite(readyLedPin, 1);
    }
    delay(1);
}
