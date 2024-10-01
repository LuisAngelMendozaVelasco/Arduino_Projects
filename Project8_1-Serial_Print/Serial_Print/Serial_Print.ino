/*
	Project 8.1 Serial Print

	Send data to the computer and print it on the serial monitor.
*/

String command;

void setup() {
	// Put your setup code here, to run once:
	Serial.begin(9600);
}

void loop() {
	// Put your main code here, to run repeatedly:
	int i = 0;

	detect_trigger_word();

	while (command == "start") {
		Serial.print("on,Hello " + String(i));
		i += 1;
		custom_delay(1000);

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