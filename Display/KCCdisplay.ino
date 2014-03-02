/*
 * File Name :
 * Purpose :
 * Creation Date :
 * Last Modified : mån  3 mar 2014 00:48:00
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */


// For controlling the display
#include "LedControl.h"
LedControl display=LedControl(12,11,10,1);
void setup() {

	// Enable the display
	display.shutdown(0,false);
	// Set brightness
	display.setIntensity(0,8);
	// Clear the display
	display.clearDisplay(0);
}

void printNumber(unsigned long v) {
	int onDisplay[8];

	for(int i=0;i<sizeof(onDisplay);i++){
		onDisplay[i] = v%10;
		v /= 10;
		display.setDigit(0,i,(byte)onDisplay[i],false);
	}
}

void loop() {
	for(unsigned long i=0;i<9999999;i++) {
		printNumber(i);
	}
}
