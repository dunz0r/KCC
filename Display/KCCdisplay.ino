/*
 * File Name :
 * Purpose :
 * Creation Date :
 * Last Modified : sön 23 feb 2014 16:11:23
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

void loop() {
	// Just a simple counter for now
	for(int i=0; i<8; i++) {
		altitudeDisplay.setDigit(0, i, (i+1), false);
	}
	delay(1000);
}
