/*
	Button

	Turns on and off a light emitting diode(LED) connected to digital pin 13,
	when pressing a pushbutton attached to pin 2.

	The circuit:
	- LED attached from pin 13 to ground through 220 ohm resistor
	- pushbutton attached to pin 2 from +5V
	- 10K resistor attached to pin 2 from ground

	- Note: on most Arduinos there is already an LED on the board
		attached to pin 13.
*/

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;  // the number of the pushbutton pin

// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status
bool isTimeChecked = false;
unsigned long time_now;

void setup() {
	// initialize the LED pin as an output:
	pinMode(LED_BUILTIN, OUTPUT);
	// initialize the pushbutton pin as an input:
	pinMode(buttonPin, INPUT);
	Serial.begin(9600);
}

void loop() {
	// read the state of the pushbutton value:
	buttonState = digitalRead(buttonPin);
	int time_period = 100;

	// check if the pushbutton is pressed. If it is, the buttonState is HIGH:
	if (buttonState == HIGH) {
		// turn LED on:
		digitalWrite(LED_BUILTIN, HIGH);

		if (!isTimeChecked) {
			Serial.write("1"); // Writes binary data to the serial port.
			time_now = millis(); // Return the number of milliseconds passed since the Arduino board began running the current program.
			isTimeChecked = true;
		}
		else {
			if(millis() > time_now + time_period) {
				isTimeChecked = false;
			}
		}		
	} else {
		// turn LED off:
		digitalWrite(LED_BUILTIN, LOW);

		if (!isTimeChecked) {
			Serial.write("0"); // Writes binary data to the serial port.
			time_now = millis(); // Return the number of milliseconds passed since the Arduino board began running the current program.
			isTimeChecked = true;
		}
		else {
			if(millis() > time_now + time_period) {
				isTimeChecked = false;
			}
		}	
	}
}
