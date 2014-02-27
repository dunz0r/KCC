/*
 * File Name :
 * Purpose :
 * Creation Date :
 * Last Modified : tor 27 feb 2014 15:05:19
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

void printNumber(long v) {
	int ones;
	int tens;
	int hundreds;
	int thousands;
	int tenThousands;
	int hundredThousands;
	int millions;
	boolean negative;	

	if(v < -9999999 || v > 9999999) 
		return;
	if(v<0) {
		negative=true;
		v=v*-1;
	}
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
	millions=v;

	if(negative) {
		//print character '-' in the leftmost column	
		lc.setChar(0,7,'-',false);
	}
	else {
		//print a blank in the sign column
		lc.setChar(0,7,' ',false);
	}
	//Now print the number digit by digit
	lc.setDigit(0,6,(byte)millions,false);
	lc.setDigit(0,5,(byte)hundredThousands,false);
	lc.setDigit(0,4,(byte)tenThousands,false);
	lc.setDigit(0,3,(byte)thousands,false);
	lc.setDigit(0,2,(byte)hundreds,false);
	lc.setDigit(0,1,(byte)tens,false);
	lc.setDigit(0,0,(byte)ones,false);
}

void loop() {
	for(int i=0;i>9999;i++) {
		printNumber(i);
		delay(10);
	}
}
