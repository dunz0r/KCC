/*
 * File Name :
 * Purpose :
 * Creation Date :
 * Last Modified : ons 26 feb 2014 19:31:04
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

 // define max7219 registers
 const byte MAX7219_REG_NOOP        = 0x0;
 const byte MAX7219_REG_DIGIT0      = 0x1;
 const byte MAX7219_REG_DIGIT1      = 0x2;
 const byte MAX7219_REG_DIGIT2      = 0x3;
 const byte MAX7219_REG_DIGIT3      = 0x4;
 const byte MAX7219_REG_DIGIT4      = 0x5;
 const byte MAX7219_REG_DIGIT5      = 0x6;
 const byte MAX7219_REG_DIGIT6      = 0x7;
 const byte MAX7219_REG_DIGIT7      = 0x8;
 const byte MAX7219_REG_DECODEMODE  = 0x9;
 const byte MAX7219_REG_INTENSITY   = 0xA;
 const byte MAX7219_REG_SCANLIMIT   = 0xB;
 const byte MAX7219_REG_SHUTDOWN    = 0xC;
 const byte MAX7219_REG_DISPLAYTEST = 0xF;

#include <SPI.h>

void sendByte(const byte reg, const byte data) {
	SPI.transfer(reg);
	SPI.transfer(data);
}

void showNumber(const int num) {
	char buf[8];
	sprintf(buf, "%7l", min(max(num,0), 9999999));
	for(byte digit=0;digit < 7; digit++) {
		byte c = buf[digit];
		if(c == ' ')
			c = 0xFF; // Code for a blank
		else
			c -= '0';
		sendByte(digit +1, c);
	}
}

void setup() {
	Serial.begin(9600);
	SPI.begin();
	
	// Max 7 digits
	sendByte(MAX7219_REG_SCANLIMIT, 7);
	// Use digits, no bit pattern
	sendByte(MAX7219_REG_DECODEMODE, 0xFF);
	// Don't test the display first
	sendByte(MAX7219_REG_DISPLAYTEST, 0);
	
	for(byte col=0; col < 8; col++)
		sendByte(col+1,0);
	// Intensity at ~50%
	sendByte(MAX7219_REG_INTENSITY, 7);
	// Start the display
	sendByte(MAX7219_REG_SHUTDOWN, 1);
}

unsigned int i;
void loop() {
	showNumber(i++);
	delay(300);
}
