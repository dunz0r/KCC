/*
 * File Name :
 * Purpose :
 * Creation Date :
 * Last Modified : lör  8 mar 2014 14:41:47
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */


// For controlling the display
#include "LedControl.h"
// 12->DATA IN, 11-> CLK, 10-> LOAD/CS
LedControl display=LedControl(12,11,10,1);

void printNumber(unsigned long v) {
	int onDisplay[8];

	for(int i=0;i<sizeof(onDisplay);i++){
		onDisplay[i] = v%10;
		v /= 10;
		display.setDigit(0,i,(byte)onDisplay[i],false);
	}
}

void setup() {

	// Enable the display
	display.shutdown(0,false);
	// Set brightness
	display.setIntensity(0,8);
	// Clear the display
	display.clearDisplay(0);

	Serial.begin(38400);

	printNumber(3400);
}

void loop() {
	if(Serial.available() > 0){
		unsigned long incomingByte = Serial.read();
		printNumber(incomingByte);
	}
}
