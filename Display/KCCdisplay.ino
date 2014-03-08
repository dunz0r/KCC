/*
 * File Name :
 * Purpose :
 * Creation Date :
 * Last Modified : lör  8 mar 2014 17:56:42
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */


// For controlling the display
#include "LedControl.h"
// 12->DATA IN, 11-> CLK, 10-> LOAD/CS
LedControl display=LedControl(12,11,10,1);

const int maxChars = 9;
char strValue[maxChars + 1];
int index = 0;
unsigned long incomingNumber = 0;
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
}

void loop() {
	while(Serial.available()){
	unsigned long incomingNumber = Serial.parseInt();
	printNumber(incomingNumber);
	}
}
