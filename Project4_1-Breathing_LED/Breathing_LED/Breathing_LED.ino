/*
	Project 4.1 Breathing LED

	Breathing light, that is, LED is turned from off to on gradually, and gradually from on to off, just like "breathing".
	We will use PWM to control the brightness of an LED.
*/

// Declare variables
String command;
int time_period = 5;
int values[] = {0, 51, 102, 153, 204, 255};
char cstr[3];

// The setup function runs once when you press reset or power the board
void setup() {
	pinMode(LED_BUILTIN, OUTPUT); // Initialize digital pin as an output
	Serial.begin(9600); // Initialize serial communication
}

void loop() {
	// Serial.available() -> Get the number of bytes (characters) available for reading from the serial port
	if (Serial.available() > 0) {
		command = Serial.readStringUntil('\n'); // Read incoming serial data
	}

	while (command == "start") {
		// Make light fade in
		for (int i = 0; i < 256; i++) { 
			analogWrite(LED_BUILTIN, i);

			for (int j = 0; j < 6; j++) {
				if (i == values[j]) {
					Serial.write(itoa(i, cstr, 10));
				}
			}

			command = custom_delay(time_period); // Wait for a time and return string variable

			if (command == "stop") break;
		}

		if (command == "stop") break;

		// Make light fade out
		for (int i = 255; i > -1; i--) { 
			analogWrite(LED_BUILTIN, i);

			for (int j = 0; j < 6; j++) {
				if (i == values[j]) {
					Serial.write(itoa(i, cstr, 10));
				}
			}

			command = custom_delay(time_period); // Wait for a time and return string variable

			if (command == "stop") break;
		}
	}
}

// Function for custom time delay
String custom_delay (int time_period) {
	String command = "start";
	unsigned long time_now = millis(); // Return the number of milliseconds passed since the Arduino board began running the current program
	
	while (millis() < time_now + time_period) {
		if (Serial.available() > 0) {
				command = Serial.readStringUntil('\n'); // Read incoming serial data

			if (command == "stop") {
				analogWrite(LED_BUILTIN, 0);
				Serial.write("off"); // Write binary data to the serial port
				
				return command;
			}
		}        
	}
	
	return command;
}