/*
	Project 9.1 Read the Voltage of Potentiometer

	Use ADC function of Arduino to read the voltage output by potentiometer.
*/

#define PIN_ANALOG_IN 0

String command;

void setup() {
	// Put your setup code here, to run once:
	Serial.begin(9600);
}

void loop() {
	// Put your main code here, to run repeatedly:
	int ADC;

	detect_trigger_word();

	while (command == "start") {
		if (analogRead(PIN_ANALOG_IN) != ADC) {
			ADC = analogRead(PIN_ANALOG_IN);
			Serial.print("on," + String(ADC));
			custom_delay(500);
		}

		if (command == "stop") {Serial.write("off"); break;}
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