#include <NTC.h>

#define heaterPin 12
#define readyLedPin 13

double R0 = 20000;		// NTC resistance @T0 =25°C
double Rh = 100000;		//pull-up resistance
double B = 3950;		//NTC B coefficient
double VCC = 5.0000;	//...
int ADC_PIN = A0;		//D14

int setTempPin = A1;
float tDelta = 3.00;	//half hysteresis temp. delta
float setTemp=0;

NTC ntc(R0 ,B ,Rh ,VCC ,ADC_PIN);	//NTC instance

void setup(){

	pinMode(heaterPin, OUTPUT);	//
	pinMode(readyLedPin, OUTPUT);
}
int bounceCount =0;


void loop(){
	
	if(setTemp != map(analogRead(setTempPin),0 ,1023 ,80.00, 130.00)){

		setTemp = map(analogRead(setTempPin),0 ,1023 ,80.00, 130.00);
		bounceCount =0;
	}

	if(ntc.getTemperatureC() >= setTemp + tDelta){
		digitalWrite(heaterPin, 1);
		bounceCount ++;
	}

	if(ntc.getTemperatureC() <= setTemp - tDelta){
		digitalWrite(heaterPin, 0);
	}

	if(bounceCount > 10 && (abs(setTemp - ntc.getTemperatureC()) <= tDelta)) digitalWrite(readyLedPin, 1);
	else{
		digitalWrite(readyLedPin,0);		
	}
}