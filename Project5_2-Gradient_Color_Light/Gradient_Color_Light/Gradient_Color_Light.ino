/*
	Project 5.2 Gradient Color Light

	Realize a fashionable Light with soft color changes using a RGB LED (Common anode).
*/

// Define led pins
const byte ledPins[] = {9, 10, 11};

String command; // Declare variable

void setup() {
	for (int i = 0; i < 3; i++) {
		// Setup the pwm channels
		pinMode(ledPins[i], OUTPUT);
		analogWrite(ledPins[i], 256);
	}

	Serial.begin(9600); // Initialize serial communication
}

void loop() {
	int time_period = 100; // Declare variable

	detect_trigger_word();

	while (command == "start") {
		for (int i = 0; i < 256; i++) {
			setColor(wheel(i));
			Serial.print("on," + String(wheel(i)));
			custom_delay(time_period); // Wait for a time and return string variable

			if (command == "stop") {stop(); break;}
		}
	}
}

void setColor(long rgb) {
	analogWrite(ledPins[0], 255 - (rgb >> 16) & 0xFF);
	analogWrite(ledPins[1], 255 - (rgb >> 8) & 0xFF);
	analogWrite(ledPins[2], 255 - (rgb >> 0) & 0xFF);
}

long wheel(int pos) {
	long WheelPos = pos % 0xff;

	if (WheelPos < 85) return ((255 - WheelPos * 3) << 16) | ((WheelPos * 3) << 8);
	else if (WheelPos < 170) {
		WheelPos -= 85;
		return (((255 - WheelPos * 3) << 8) | (WheelPos * 3));
	}
	else {
		WheelPos -= 170;
		return ((WheelPos * 3) << 16 | (255 - WheelPos * 3));
	}
}

void stop() {
	for (int i = 0; i < 3; i++) analogWrite(ledPins[i], 256);

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