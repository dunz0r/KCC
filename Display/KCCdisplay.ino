/*
 * File Name :
 * Purpose :
 * Creation Date :
 * Last Modified : tor 27 feb 2014 15:09:27
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
	int ones;
	int tens;
	int hundreds;
	int thousands;
	int tenThousands;
	int hundredThousands;
	int millions;
	int tenMillions;

	ones=v%10;
	v=v/10;
	tens=v%10;
	v=v/10;
	hundreds=v%10;
	v=v/10;
	thousands=v%10;
	v=v/10;
	tenThousands=v%10;
	v=v/10;
	hundredThousands=v%10;
	v=v/10;
	millions=v%10;
	v=v/10;
	tenMillions=v;

	//Now print the number digit by digit
	display.setDigit(0,7,(byte)tenMillions,false);
	display.setDigit(0,6,(byte)millions,false);
	display.setDigit(0,5,(byte)hundredThousands,false);
	display.setDigit(0,4,(byte)tenThousands,false);
	display.setDigit(0,3,(byte)thousands,false);
	display.setDigit(0,2,(byte)hundreds,false);
	display.setDigit(0,1,(byte)tens,false);
	display.setDigit(0,0,(byte)ones,false);
}

void loop() {
	for(unsigned long i=0;i>9999999;i++) {
		printNumber(i);
	}
}
