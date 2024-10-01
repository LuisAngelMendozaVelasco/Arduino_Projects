/*
	Project 6.1 NeoPixel

	Use NeoPixel to blink red, green, blue and white.
*/

#include <Adafruit_NeoPixel.h>
#define PIN 3
#define NUMPIXELS 8

// Declare variables
int setColor[5][3] = {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 255}, {0, 0, 0}};
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
String command;

void setup() {
	// Put your setup code here, to run once:
	pixels.begin();
	pixels.setBrightness(20);
	Serial.begin(9600); // Initialize serial communication
}

void loop() {
	// Put your main code here, to run repeatedly:
	detect_trigger_word();

	while (command == "start") {
		for (int j = 0; j < 5; j++) {
			for (int i = 0; i < NUMPIXELS; i++) {
				pixels.setPixelColor(i, setColor[j][0], setColor[j][1], setColor[j][2]);
				pixels.show();
				Serial.print("on," + String(i) + "," + String(j));
				custom_delay(100);

				if (command == "stop") break;
			}

			if (command == "stop") {stop(); break;}

			custom_delay(500);
			
			if (command == "stop") {stop(); break;}
		}
	}
}

void stop() {
	for (int i = 0; i < NUMPIXELS; i++) {
		pixels.setPixelColor(i, setColor[4][0], setColor[4][1], setColor[4][2]);
		pixels.show();
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