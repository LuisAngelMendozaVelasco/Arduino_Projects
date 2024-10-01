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

void setup() {
	for (int i = 0; i < ledCounts; i++) pinMode(ledPins[i], OUTPUT);
	
	Serial.begin(9600); // Initialize serial communication
}

void loop() {
	int time_period = 100; // Declare variable

	detect_trigger_word();

	while (command == "start") {
		for (int i = 0; i < ledCounts; i++) {
			digitalWrite(ledPins[i], HIGH);
			Serial.print("on," + String(i));
			custom_delay(time_period); // Wait for a time and return string variable
			digitalWrite(ledPins[i], LOW);

			if (command == "stop") break;
		}

		if (command == "stop") {Serial.write("off"); break;}

		for (int i = ledCounts - 1; i > -1; i--) {
			digitalWrite(ledPins[i], HIGH);
			Serial.print("on," + String(i));
			custom_delay(time_period); // Wait for a time and return string variable
			digitalWrite(ledPins[i], LOW);

			if (command == "stop") {Serial.write("off"); break;}
		}
	}
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