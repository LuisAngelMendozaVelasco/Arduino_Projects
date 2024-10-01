/*
	Project 7.1 Doorbell

	When the button is pressed, the buzzer sounds; and when the button is
	released, the buzzer stops sounding.
*/

#define PIN_BUZZER 3
#define PIN_BUTTON 2

// Variable will change
bool isBuzzerHigh = false;

void setup() {
	// Put your setup code here, to run once:
	pinMode(PIN_BUZZER, OUTPUT);
	pinMode(PIN_BUTTON, INPUT);
	digitalWrite(PIN_BUZZER, LOW);
	Serial.begin(9600); // Initialize serial communication
}

void loop() {
	// Put your main code here, to run repeatedly:
	int buttonState = digitalRead(PIN_BUTTON); // Read the state of the push button value

	if (buttonState == LOW) {
		if (!isBuzzerHigh) {
			digitalWrite(PIN_BUZZER, HIGH);
			Serial.write("on"); // Write binary data to the serial port
			isBuzzerHigh = !isBuzzerHigh;
		}
	}
	else {
		if (isBuzzerHigh) {
			digitalWrite(PIN_BUZZER, LOW); // Turn LED off
			Serial.write("off"); // Write binary data to the serial port
			isBuzzerHigh = !isBuzzerHigh;
		}
	}
}