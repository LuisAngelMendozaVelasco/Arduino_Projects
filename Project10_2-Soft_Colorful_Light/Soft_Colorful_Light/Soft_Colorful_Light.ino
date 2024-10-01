/*
	Project 10.2 Soft Colorful Light

	Use 3 potentiometers control a RGB LED.
*/

const byte ledPins[] = {9, 10, 11}; // Define led pins
const byte adcChns[] = {0, 1, 2}; // Define the adc channels
String command;

void setup() {
	// Put your setup code here, to run once:
	for (int i = 0; i < 3; i++) {
		pinMode(ledPins[i], OUTPUT); // Setup the pwm channels
		analogWrite(ledPins[i], 256);
	}

	Serial.begin(9600);
}

void loop() {
	// Put your main code here, to run repeatedly:
	int colors[] = {255, 255, 255}; // Red, green ,blue values of color

	detect_trigger_word();

	while (command == "start") {
		bool isColorDifferent = false;
		
		for (int i = 0; i < 3; i++) {
			if (map(analogRead(adcChns[i]), 0, 1023, 0, 255) != colors[i]) {
				colors[i] = map(analogRead(adcChns[i]), 0, 1023, 0, 255); // Calculate color value.
				analogWrite(ledPins[i], colors[i]);
				isColorDifferent = true;
			}
		}

		if (isColorDifferent) Serial.print("on," + String(colors[0]) + "," + String(colors[1]) + "," + String(colors[2]));

		custom_delay(10);

		if (command == "stop") {stop(); break;}
	}
}

void stop() {
	for (int i = 0; i < 3; i++) {
		pinMode(ledPins[i], OUTPUT); // Setup the pwm channels
		analogWrite(ledPins[i], 256);
	}

	Serial.write("off");
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