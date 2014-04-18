/*
 * File Name :
 * Purpose :
 * Creation Date :
 * Last Modified : fre 18 apr 2014 22:11:41
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */


// For controlling the display
#include "LedControl.h"
// 12->DATA IN, 11-> CLK, 10-> LOAD/CS, number of displays
LedControl display=LedControl(12,11,10,2);

void printDecimalNumber(uint32_t v, int address) {
	int onDisplay[8];

	for(unsigned int i=0;i<sizeof(onDisplay);i++){
		onDisplay[i] = v%10;
		v /= 10;
		// The first character printed will be the decimal number, so put the decimal point 
		// so put the decimal point on the second character
		if(i == 1)
			display.setDigit(address,i,(byte)onDisplay[i],true);
		else if( i != 1)
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
	unsigned int fuelCurrent=0;
	unsigned int fuelMax=0;
	float percent;

	Serial.print("fC");
	fuelCurrent = Serial.parseInt();
	Serial.print("fM");
	fuelMax = Serial.parseInt();
	percent = (float)fuelCurrent / (float)fuelMax;
	return (int)(percent*255);
}

int getCharge() {
	unsigned int chargeCurrent=0;
	unsigned int chargeMax=0;
	float percent;

	Serial.print("cC");
	chargeCurrent = Serial.parseInt();
	Serial.print("cM");
	chargeMax = Serial.parseInt();
	percent = (float)chargeCurrent / (float)chargeMax;
	return (int)(percent*255);
}

uint32_t getVelocity(short mode) {
	uint32_t velocity;

	switch(mode) {
		case 0:
			Serial.print("sV");
			velocity = Serial.parseInt();
		case 1:
			Serial.print("oV");
			velocity = Serial.parseInt();
		case 2:
			Serial.print("tV");
			velocity = Serial.parseInt();
		default:
			Serial.print("sV");
			velocity = Serial.parseInt();
	}
	return velocity/10;
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
	analogWrite(3,fuelPercent);
	printDecimalNumber(getAltitude(), 1);
	printDecimalNumber(getVelocity(0), 0);
}
