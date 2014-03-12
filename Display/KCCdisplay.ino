/*
 * File Name :
 * Purpose :
 * Creation Date :
 * Last Modified : ons 12 mar 2014 16:22:51
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */


// For controlling the display
#include "LedControl.h"
// 12->DATA IN, 11-> CLK, 10-> LOAD/CS
LedControl display=LedControl(12,11,10,2);

void printNumber(unsigned long v) {
	int onDisplay[8];

	for(int i=0;i<sizeof(onDisplay);i++){
		onDisplay[i] = v%10;
		v /= 10;
		display.setDigit(0,i,(byte)onDisplay[i],false);
		display.setDigit(1,i,(byte)onDisplay[i],false);
	}
}

void setup() {

	// Enable the display
	display.shutdown(0,false);
	display.shutdown(1,false);
	// Set brightness
	display.setIntensity(0,6);
	display.setIntensity(1,6);
	// Clear the display
	display.clearDisplay(0);
	display.clearDisplay(1);

	Serial.begin(38400);
}

void loop() {
	while(Serial.available()){
	unsigned long incomingNumber = Serial.parseInt();
	printNumber(incomingNumber);
	}
}
