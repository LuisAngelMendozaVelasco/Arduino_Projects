/*
	Project 2.1 Button & LED

	Turns on and off an LED when pressing a push button.
*/

// Constants won't change, they're used here to set pin numbers
const int buttonPin = 2; // The number of the push button pin

// Variable will change
bool isLEDHigh = false;

void setup() {
	pinMode(LED_BUILTIN, OUTPUT); // Initialize the LED pin as an output
	pinMode(buttonPin, INPUT); // Initialize the push button pin as an input
	Serial.begin(9600); // Initialize serial communication
}

void loop() {
	int buttonState = digitalRead(buttonPin); // Read the state of the push button value

	// Check if the push button is pressed, if it is, the buttonState is HIGH
	if (buttonState == HIGH) {
		if (!isLEDHigh) {
			digitalWrite(LED_BUILTIN, HIGH); // Turn LED on
			Serial.write("on"); // Write binary data to the serial port
			isLEDHigh = !isLEDHigh;
		}
	}
	else {
		if (isLEDHigh) {
			digitalWrite(LED_BUILTIN, LOW); // Turn LED off
			Serial.write("off"); // Write binary data to the serial port
			isLEDHigh = !isLEDHigh;
		}
	}
}