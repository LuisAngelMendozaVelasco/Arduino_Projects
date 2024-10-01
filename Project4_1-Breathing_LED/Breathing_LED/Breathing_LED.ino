/*
	Project 4.1 Breathing LED

	Breathing light, that is, LED is turned from off to on gradually, and gradually from on to off, just like "breathing".
	We will use PWM to control the brightness of an LED.
*/

String command; // Declare variables

// The setup function runs once when you press reset or power the board
void setup() {
	pinMode(LED_BUILTIN, OUTPUT); // Initialize digital pin as an output
	Serial.begin(9600); // Initialize serial communication
}

void loop() {
	int time_period = 5; // Declare variable

	detect_trigger_word();

	while (command == "start") {
		// Make light fade in
		for (int i = 0; i < 256; i++) {
			analogWrite(LED_BUILTIN, i);

			if (i % 5 == 0) Serial.print("on," + String(i));
			
			custom_delay(time_period); // Wait for a time and return string variable

			if (command == "stop") break;
		}

		if (command == "stop") {stop(); break;}

		// Make light fade out
		for (int i = 255; i > -1; i--) {
			analogWrite(LED_BUILTIN, i);

			if (i % 5 == 0) Serial.print("on," + String(i));

			custom_delay(time_period); // Wait for a time and return string variable

			if (command == "stop") {stop(); break;}
		}
	}
}

void stop() {
	analogWrite(LED_BUILTIN, 0);
	Serial.write("off"); // Write binary data to the serial port
}

// Function for custom time delay
void custom_delay(int time_period) {
	unsigned long time_now = millis(); // Return the number of milliseconds passed since the Arduino board began running the current program
	
	while (millis() < time_now + time_period) {
		detect_trigger_word();
		
		if (command == "stop") break;
	}
}

void detect_trigger_word() {
	String aux;
	
	if (Serial.available() > 0) { // Serial.available() -> Get the number of bytes (characters) available for reading from the serial port
		aux = Serial.readStringUntil('\n'); // Read incoming serial data
		
		if (aux == "start" || aux == "stop") {command = aux;}
	}
}