/*
	Project 5.1 Random Color Light

	Control an RGB LED (Common anode) to switch different colors automatically.
*/

// Define red, green, blue led pins
int ledPins[] = {9, 10, 11};
int red, green, blue;

String command; // Declare variable

void setup() {
	// Setup the pwm channels, 1KHz, 8bit
	for (int i = 0; i < 3; i++) {
		pinMode(ledPins[i], OUTPUT);
		analogWrite(ledPins[i], 256);
	}

	Serial.begin(9600); // Initialize serial communication
}

void loop() {
	int time_period = 500; // Declare variable

	detect_trigger_word();

	while (command == "start") {
		red = random(0, 255);
		green = random(0, 255);
		blue = random(0, 255);

		setColor(red, green, blue);
		Serial.print("on," + String(red) + "," + String(green) + "," + String(blue)); // Write data to the serial port                     
		custom_delay(time_period); // Wait for a time and return string variable
	}
}

void setColor(byte r, byte g, byte b) {
	// Common anode LED, low level to turn on the led.
	analogWrite(ledPins[0], 255 - r);
	analogWrite(ledPins[1], 255 - g);
	analogWrite(ledPins[2], 255 - b);
}

// Function for custom time delay
void custom_delay(int time_period) {
	unsigned long time_now = millis(); // Return the number of milliseconds passed since the Arduino board began running the current program
	
	while (millis() < time_now + time_period) {
		detect_trigger_word();
		
		if (command == "stop") {
			for (int i = 0; i < 3; i++) analogWrite(ledPins[i], 256);

			Serial.write("off"); // Write binary data to the serial port
			
			break;
		}
	}
}

void detect_trigger_word() {
	String aux;
	
	if (Serial.available() > 0) { // Serial.available() -> Get the number of bytes (characters) available for reading from the serial port
		aux = Serial.readStringUntil('\n'); // Read incoming serial data
		
		if (aux == "start" || aux == "stop") {command = aux;}
	}
}