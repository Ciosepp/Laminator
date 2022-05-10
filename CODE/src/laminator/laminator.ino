#include <NTC.h>

#define outputPin 0
#define readyLedPin 1

double R0 = 20000;
double Rh = 100000;
double B = 3950;
double VCC = 5.0000;
int ADC_PIN = A3;

int setTempPin = A1;
float tDelta = 3.00;
float setTemp;

NTC ntc(R0 ,B ,Rh ,VCC ,ADC_PIN);

void setup(){

	pinMode(outputPin, OUTPUT);
	pinMode(readyLedPin, OUTPUT);
}
int bounceCount =0;

void loop(){
	setTemp = map(analogRead(setTempPin),0 ,1023 ,80.00, 150.00);

	if(ntc.getTemperatureC() >= setTemp + tDelta){
		digitalWrite(outputPin, 1);
		bounceCount ++;
	}

	if(ntc.getTemperatureC() <= setTemp - tDelta){
		digitalWrite(outputPin, 0);
	}

	if(bounceCount > 10) digitalWrite(readyLedPin, 1);
}
