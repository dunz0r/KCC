/*
 * File Name :
 * Purpose :
 * Creation Date :
 * Last Modified : sön 23 feb 2014 18:00:01
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

// MAX7219-controlled display library
#include <LedControl.h>

LedControl altitudeDisplay = LedControl(8,9,10,1);
void setup() {
	Serial.begin(9600);

	// Initialize display
	// Enable display
	altitudeDisplay.shutdown(0, false);
	// Set brightness
	altitudeDisplay.setIntensity(0,5);
	// Clear the display register
	altitudeDisplay.clearDisplay(0);
}

void printNumber(int v) {
	int ones;
	int tens;
	int hundreds;
	int thousands;
	int tenthousands;
	bool negative;

	if(v<0) {
		negative=true;
		v= v*-1;
	}
	// Convert in to groups
	ones = v%10;
	v=v/10;

	tens=v%10;
	v=v/10;

	hundreds=v%10;
	v=v/10;

	if(negative) {
		altitudeDisplay.setChar(0,7,'-',false);
	} else {
		altitudeDisplay.setChar(0,7,0,false);
	}

	altitudeDisplay.setDigit(0,2,hundreds,false);
	altitudeDisplay.setDigit(0,1,tens,false);
	altitudeDisplay.setDigit(0,0,ones,false);
}

void loop() {
	// Just a simple counter for now
	for(int i=-999; i<999;i++) {
		printNumber(i);
		delay(10);
	}
}
