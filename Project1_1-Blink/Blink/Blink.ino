/*
	Project 1.1 Blink

	Turn an LED on for one second, then off for one second, repeatedly.
*/

// Declare variables
String command;
int time_period = 1000;

// The setup function runs once when you press reset or power the board
void setup() {
	pinMode(LED_BUILTIN, OUTPUT); // Initialize digital pin as an output
	Serial.begin(9600); // Initialize serial communication
}

// The loop function runs over and over again forever
void loop() {
	// Serial.available() -> Get the number of bytes (characters) available for reading from the serial port
	if (Serial.available() > 0) {
		command = Serial.readStringUntil('\n'); // Read incoming serial data
	}
			
	while (command == "start") {
		digitalWrite(LED_BUILTIN, HIGH); // Turn the LED on (HIGH is the voltage level)
		Serial.write("on"); // Write binary data to the serial port                      
		command = custom_delay(time_period); // Wait for a time and return string variable

		if (command == "stop") break;

		digitalWrite(LED_BUILTIN, LOW); // Turn the LED off by making the voltage LOW
		Serial.write("off"); // Write binary data to the serial port
		command = custom_delay(time_period); // Wait for a time and return string variable

		if (command == "stop") break;
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
				digitalWrite(LED_BUILTIN, LOW);
				Serial.write("off"); // Write binary data to the serial port
				
				return command;
			}
		}        
	}
	
	return command;
}