/*
	Project 10.3 Soft Rainbow Light

	Use a potentiometer to control Freenove 8 RGBLED Module.
*/

#include <Adafruit_NeoPixel.h>
#define Pin 3
#define NumPixels 8
#define Pin_ADC0 0
int red = 0;
int green = 0;
int blue = 0;
Adafruit_NeoPixel strip(NumPixels, Pin, NEO_GRB + NEO_KHZ800);
String command;

void setup() {
	// Put your setup code here, to run once:
	strip.begin();
	strip.setBrightness(20);
	Serial.begin(9600);
}

void loop() {
	// Put your main code here, to run repeatedly:
	int ADC_mapped = -1;

	detect_trigger_word();

	while (command == "start") {
		if (map(analogRead(Pin_ADC0), 0, 1023, 0, 255) != ADC_mapped) {
			ADC_mapped = map(analogRead(Pin_ADC0), 0, 1023, 0, 255);
			Serial.print("on," + String(ADC_mapped));

			for (int i = 0; i < 8; i++) {
				Wheel(((i * 256 / 8) + ADC_mapped) & 255);
				strip.setPixelColor(i, strip.Color(red, green, blue));
			}

			strip.show();
		}

		custom_delay(10);

		if (command == "stop") {stop(); break;}
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
	for (int i = 0; i < NumPixels; i++) {
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