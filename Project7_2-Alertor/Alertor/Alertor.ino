/*
	Project 7.2 Alertor

	Use a passive buzzer to make an alarm.
*/

#define PIN_BUZZER 3
#define PIN_BUTTON 2

// Variable will change
bool isBuzzerHigh = false;

void setup() {
	// Put your setup code here, to run once:
	pinMode(PIN_BUTTON, INPUT);
	pinMode(PIN_BUZZER, OUTPUT);
	Serial.begin(9600); // Initialize serial communication
}

void loop() {
	// Put your main code here, to run repeatedly:
	int buttonState = digitalRead(PIN_BUTTON); // Read the state of the push button value

	if (buttonState == LOW) {
		Serial.write("on"); // Write binary data to the serial port
		alert();
		isBuzzerHigh = true;
	}
	else {
		if (isBuzzerHigh) {
			freq(PIN_BUZZER, 0, 10);
			Serial.write("off"); // Write binary data to the serial port
			isBuzzerHigh = !isBuzzerHigh;
		}
	}
}

void alert() {
	float sinVal; // Define a variable to save sine value
	int toneVal; // Define a variable to save sound frequency

	for (int x = 0; x < 360; x += 10) {
		// X from 0 degree->360 degree
		sinVal = sin(x * (PI / 180)); // Calculate the sine of x
		toneVal = 2000 + sinVal * 500; // Calculate sound frequency according to the sine of x
		freq(PIN_BUZZER, toneVal, 10);
	}
}

void freq(int PIN, int freqs, int times) {
	if (freqs == 0) digitalWrite(PIN, LOW);
	else {
		for (int i = 0; i < times * freqs / 1000; i ++) {
			digitalWrite(PIN, HIGH);
			delayMicroseconds(1000000 / freqs / 2);
			digitalWrite(PIN, LOW);
			delayMicroseconds(1000000 / freqs / 2);
		}
	}
}