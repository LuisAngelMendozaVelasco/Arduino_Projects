/*
	Project 3.1 Flowing Light

	This project is designed to make a flowing water lamp, which are these actions: First turn LED #1 ON, then
	turn it OFF. Then turn LED #2 ON, and then turn it OFF... and repeat the same to all 10 LEDs until the last LED
	is turns OFF. This process is repeated to achieve the “movements” of flowing water.
*/

// Declare variables
byte ledPins[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int ledCounts = sizeof(ledPins);
String command;
int time_period = 100;
char cstr[2];

void setup() {
	Serial.begin(9600); // Initialize serial communication

	for (int i = 0; i < ledCounts; i++) {
		pinMode(ledPins[i], OUTPUT);
	}
}

void loop() {
	// Serial.available() -> Get the number of bytes (characters) available for reading from the serial port
	if (Serial.available() > 0) {
		command = Serial.readStringUntil('\n'); // Read incoming serial data
	}

	while (command == "start") {
		for (int i = 0; i < ledCounts; i++) {
			digitalWrite(ledPins[i], HIGH);
			Serial.write(itoa(i, cstr, 10)); // Write binary data to the serial port
			command = custom_delay(time_period); // Wait for a time and return string variable
			digitalWrite(ledPins[i], LOW);

			if (command == "stop") break;
		}

		if (command == "stop") break;

		for (int i = ledCounts - 1; i > -1; i--) {
			digitalWrite(ledPins[i], HIGH);
			Serial.write(itoa(i, cstr, 10)); // Write binary data to the serial port
			command = custom_delay(time_period); // Wait for a time and return string variable
			digitalWrite(ledPins[i], LOW);

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
				Serial.write("off"); // Write binary data to the serial port
				
				return command;
			}
		}        
	}
	
	return command;
}