/*
 * File Name :
 * Purpose :
 * Creation Date :
 * Last Modified : lör 15 mar 2014 23:46:23
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */


// For controlling the display
#include "LedControl.h"
// 12->DATA IN, 11-> CLK, 10-> LOAD/CS
LedControl display=LedControl(12,11,10,2);

void printNumber(uint32_t v, int address) {
	int onDisplay[8];

	for(unsigned int i=0;i<sizeof(onDisplay);i++){
		onDisplay[i] = v%10;
		v /= 10;
		display.setDigit(address,i,(byte)onDisplay[i],false);
	}
}

void setup() {

	// Enable the display
	display.shutdown(0,false);
	display.shutdown(1,false);
	// Set brightness
	display.setIntensity(0,4);
	display.setIntensity(1,4);
	// Clear the display
	display.clearDisplay(0);
	display.clearDisplay(1);

	Serial.begin(38400);
}

int getFuel() {
	int fuelCurrent;
	int fuelMax;
	int percent;

	Serial.print("fC");
	fuelCurrent = Serial.parseInt();
	Serial.print("fM");
	fuelMax = Serial.parseInt();
	percent = (float)fuelCurrent / (float)fuelMax;
	return (int)(percent*255);
}

int getCharge() {
	int chargeCurrent=0;
	int chargeMax=0;
	float percent;

	Serial.print("cC");
	chargeCurrent = Serial.parseInt();
	Serial.print("cM");
	chargeMax = Serial.parseInt();
	percent = (float)chargeCurrent / (float)chargeMax;
	return (int)(percent*255);
}

uint32_t getVelocity() {
	uint32_t velocity;

	Serial.print("ve");
	velocity = Serial.parseInt();
	return velocity;
}

uint32_t getAltitude() {
	uint32_t altitude;

	Serial.print("al");
	altitude = Serial.parseInt();
	return altitude;
}

void loop() {
	int chargePercent = getCharge();
	int fuelPercent = getFuel();
	analogWrite(6,chargePercent);
	if(digitalRead(7))
		printNumber(getVelocity(), 0);
	else
		printNumber(getAltitude(), 0);
}
