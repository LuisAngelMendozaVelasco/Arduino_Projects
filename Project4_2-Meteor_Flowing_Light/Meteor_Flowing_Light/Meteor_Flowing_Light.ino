/*
	Project 4.2 Meteor Flowing Light
*/

// Declare variables
const int dutys[] = {0,    0,    0,    0,   0,   0,   0,  0,  0,  0, // Define the pwm dutys
					4096, 2048, 1024, 512, 256, 128, 64, 32, 16, 8,
					0,    0,    0,    0,   0,   0,   0,  0,  0,  0};

const byte ledPins[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // Define led pins
int ledCounts = sizeof(ledPins); // The number of leds
String command;

void setup() {
	for (int i = 0; i < ledCounts; i++) pinMode(ledPins[i], OUTPUT);

	Serial.begin(9600); // Initialize serial communication
}

void loop() {
	int time_period = 50; // Flowing speed ,the smaller, the faster

	detect_trigger_word();

	while (command == "start") {
		// Flowing one side to other side
		for (int i = 0; i < 2 * ledCounts; i++) {
			for (int j = 0; j < ledCounts; j++) analogWrite(ledPins[j], map(dutys[i + j], 0, 4096, 0, 255));
			
			Serial.print("on," + String(i));
			custom_delay(time_period); // Wait for a time and return string variable

			if (command == "stop") break;
		}

		if (command == "stop") {stop(); break;}

		// Flowing one side to other side
		for (int i = 0; i < 2 * ledCounts; i++) {
			for (int j = 0; j < ledCounts; j++) analogWrite(ledPins[ledCounts - j - 1], map(dutys[i + j], 0, 4096, 0, 255));

			Serial.print("on," + String(i));
			custom_delay(time_period); // Wait for a time and return string variable

			if (command == "stop") {stop(); break;}
		}
	}
}

void stop() {
	for (int j = 0; j < ledCounts; j++) analogWrite(ledPins[j], 0);

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