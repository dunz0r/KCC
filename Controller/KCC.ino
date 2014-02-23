/*
 * File Name :
 * Purpose :
 * Creation Date :
 * Last Modified : sön 23 feb 2014 15:52:19
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

// Matt Stanleys keypadlibrary
#include <Keypad.h>
String msg;
unsigned long loopCount;
unsigned long startTime;
// Rows on the keypad (six rows)
const byte ROWS = 6;
// Columns on the keypad (five rows)
const byte COLS = 6;
unsigned char keys[ROWS][COLS] = {
	{'w','a','s','d','q','e'}, // Main steering
	{'i','j','k','l','h','n'}, // RCS steering
	{'t', 'g','u','b',KEY_BACKSPACE,'v'}, // Peripherals (SAS, gear, vehicle lights, brakes, abort, camera view)
	{'1','2','3','4','5','6'}, // Action groups 1
	{'7','8','9',' ','m','x'}, // Action groups 2 + staging, map, cut throttle
	{KEY_LEFT_SHIFT,KEY_LEFT_CTRL,KEY_CAPS_LOCK,'-','+'}, // Throttle,  soft controls, zoom in, zoom out
};
byte rowPins[ROWS]={0,1,2,3,4,5};
byte colPins[COLS]={6,7,8,9,10,11};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
	Serial.begin(9600);
	Keyboard.begin();
	keypad.setDeBounceTime(20);
}

void loop() {
	if(keypad.getKeys()) {
		for(int i=0; i<LIST_MAX; i++) {
			if(keypad.key[i].stateChanged) {
				switch(keypad.key[i].kstate) {
					case PRESSED:
						msg = " PRESSED.";
						Keyboard.press(keypad.key[i].kchar);
						break;
					case HOLD:
						msg = " HOLD.";
						break;
					case RELEASED:
						Keyboard.release(keypad.key[i].kchar);
						msg = " RELEASED.";
						break;
					case IDLE:
						msg = " IDLE.";
				}
				Serial.print("Key ");
				Serial.print(keypad.key[i].kchar);
				Serial.println(msg);
			}
		}
	}
}

