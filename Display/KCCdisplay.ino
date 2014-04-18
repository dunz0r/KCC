/*
 * File Name :
 * Purpose :
 * Creation Date :
 * Last Modified : lör 19 apr 2014 01:33:54
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */


// This switch is connected to three resistors, giving three different modes
#define VEL_SWITCH A0

// Number of displays
#define NUM_DISPLAYS 3
// For controlling the display
#include "LedControl.h"
// 12->DATA IN, 11-> CLK, 10-> LOAD/CS, number of displays
LedControl display=LedControl(12,11,10,NUM_DISPLAYS);

void setup() {

	// Enable the display
	for(unsigned int i=0;i < NUM_DISPLAYS;i++){
		display.shutdown(i,false);
		display.setIntensity(i,4);
		display.clearDisplay(i);
	}

	Serial.begin(38400);
}


void printDecimalNumber(uint32_t v, int address, bool decimalPoint) {
	int onDisplay[8];

	for(unsigned int i=0;i<sizeof(onDisplay);i++){
		onDisplay[i] = v%10;
		v /= 10;
		// The first character printed will be the decimal number, so put the decimal point 
		// so put the decimal point on the second character
		if(i == 1)
			display.setDigit(address,i,(byte)onDisplay[i],decimalPoint);
		else if( i != 1)
			display.setDigit(address,i,(byte)onDisplay[i],false);
	}
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

uint32_t getVelocity(uint8_t mode) {
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
	return velocity;
}

uint32_t getApoapsis() {
	uint32_t apoapsis;
	Serial.print("ap");
	apoapsis = Serial.parseInt();
	// Divide by 10 to get rid of the decimal
	return apoapsis/10;
}
uint32_t getAltitude() {
	uint32_t altitude;

	Serial.print("al");
	altitude = Serial.parseInt();
	// Divide by 10 to get rid of the decimal
	return altitude/10;
}

uint8_t getVelocityMode() {
	// This is what gets returned
	uint8_t mode = 0;
	int switchReading = analogRead(VEL_SWITCH);

	if(switchReading > 600)
		mode = 0;
	else if((VEL_SWITCH < 600) && (VEL_SWITCH > 300))
		mode = 1;
	else
		mode = 2;
	return mode;
}

void loop() {
	int chargePercent = getCharge();
	int fuelPercent = getFuel();
	uint8_t velocityMode = getVelocityMode();
	analogWrite(6,chargePercent);
	analogWrite(3,fuelPercent);
	printDecimalNumber(getApoapsis(), 2, false);
	printDecimalNumber(getAltitude(), 1, false);
	printDecimalNumber(getVelocity(velocityMode), 0, true);
}
