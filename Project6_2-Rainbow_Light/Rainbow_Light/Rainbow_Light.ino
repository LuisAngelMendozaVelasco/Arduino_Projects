/*
	Project 6.2 Rainbow Light

	Use NeoPixel to realize a slightly complicated Rainbow Light.
*/

#include <Adafruit_NeoPixel.h>
#define PIN 3
#define NUMPIXELS 8

// Declare variables
int red = 0;
int green = 0;
int blue = 0;
Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
String command;

void setup() {
	// Put your setup code here, to run once:
	strip.begin();
	strip.setBrightness(20);

	Serial.begin(9600); // Initialize serial communication
}

void loop() {
	// Put your main code here, to run repeatedly:
	int k = 0; // Declare variable

	detect_trigger_word();

	while (command == "start") {
		for (int j = 0; j < 256 * 5; j++) {
			for (int i = 0; i < 8; i++) {
				Wheel(((i * 256 / 8) + j) % 255);
				strip.setPixelColor(i, strip.Color(red, green, blue));

				if (k == i) Serial.print("on," + String(i) + "," + String(red) + "," + String(green) + "," + String(blue));
			}

			if (k == 7) {k = 0;}
			else {k += 1;}

			strip.show();
			custom_delay(10);

			if (command == "stop") {stop(); break;}
		}
	}
}

void Wheel(byte WheelPos) {
	WheelPos = 255 - WheelPos;

	if (WheelPos < 85) {
		red = 255 - WheelPos * 3;
		green = 0;
		blue = WheelPos * 3;
	}
	else if (WheelPos < 170) {
		WheelPos -= 85;
		red = 0;
		green = WheelPos * 3;
		blue = 255 - WheelPos * 3;
	}
	else {
		WheelPos -= 170;
		red = WheelPos * 3;
		green = 255 - WheelPos * 3;
		blue = 0;
	}
}

void stop() {
	for (int i = 0; i < NUMPIXELS; i++) {
		strip.setPixelColor(i, 0, 0, 0);
		strip.show();
	}

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