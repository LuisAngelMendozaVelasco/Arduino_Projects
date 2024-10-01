/*
	Project 2.2 MINI table lamp

	We will also use a Push Button Switch, and LED to make a MINI Table Lamp but this will
	function differently: Press the button, the LED will turn ON, and pressing the button again, the LED turns OFF.
	The ON switch action is no longer momentary (like a door bell) but remains ON without needing to continually
	press on the Button Switch.
*/

// Constants won't change, they're used here to set pin numbers
const int buttonPin = 2; // The number of the push button pin

// Variable will change:
bool isLEDHigh = false;

void setup() {
	pinMode(LED_BUILTIN, OUTPUT); // Initialize the LED pin as an output
	pinMode(buttonPin, INPUT); // Initialize the push button pin as an input
	Serial.begin(9600); // Initialize serial communication
}

void loop() {
	// Check if the push button is pressed
	if (digitalRead(buttonPin) == HIGH) {
		delay(20);

		if (digitalRead(buttonPin) == HIGH) {
			isLEDHigh = !isLEDHigh;
			digitalWrite(LED_BUILTIN, isLEDHigh);

			if (isLEDHigh) Serial.write("on"); // Write binary data to the serial port
			else Serial.write("off"); // Write binary data to the serial port
		}

		while (digitalRead(buttonPin) == HIGH);
	}
}