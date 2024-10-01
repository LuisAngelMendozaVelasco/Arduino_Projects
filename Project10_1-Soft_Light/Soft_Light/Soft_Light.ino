/*
	Project 10.1 Soft Light

	Use an ADC Module to read ADC values of a potentiometer 
	and map it to duty cycle of the PWM used to control the brightness of an LED.
*/

#define PIN_ADC0 0

String command;

void setup() {
	// Put your setup code here, to run once:
	pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(9600);
}

void loop() {
	// Put your main code here, to run repeatedly:
	int ADC_mapped;

	detect_trigger_word();

	while (command == "start") {
		if (map(analogRead(PIN_ADC0), 0, 1023, 0, 255) != ADC_mapped) {
			ADC_mapped = map(analogRead(PIN_ADC0), 0, 1023, 0, 255);
			analogWrite(PIN_LED, ADC_mapped);
			Serial.print("on," + String(ADC_mapped));
			custom_delay(10);
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