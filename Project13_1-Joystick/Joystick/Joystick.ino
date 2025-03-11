/*
    Project 13.1 Joystick

    Read the ADC values of X and Y axes of a joystick, and read digital quality of
    the Z axis, then display these values.
*/

int xyzPins[] = {0, 1, 8};
String command;

void setup() {
    // Put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(xyzPins[2], INPUT_PULLUP);
}

void loop() {
    // Put your main code here, to run repeatedly:
    int xVal, yVal, zVal;c
    int time_period = 100;

    detect_trigger_word();
    
    while (command == "start") {
        if (map(analogRead(xyzPins[0]), 0, 1023, -100, 100) != xVal || map(analogRead(xyzPins[1]), 0, 1023, -100, 100) != xVal || map(digitalRead(xyzPins[2]), 0, 1, 1, 0) != xVal) {
            xVal = map(analogRead(xyzPins[0]), 0, 1023, -100, 100);
            yVal = map(analogRead(xyzPins[1]), 0, 1023, -100, 100);
            zVal = map(digitalRead(xyzPins[2]), 0, 1, 1, 0);
            
            Serial.print("on," + String(xVal) + "," + String(yVal) + "," + String(zVal));
            custom_delay(time_period);
        }

        if (command == "stop") {Serial.write("off"); break;}
    }
}

// Function for custom time delay
void custom_delay(int time_period) {
    unsigned long time_now = millis();
    
    while (millis() < time_now + time_period) {
        detect_trigger_word();
        
        if (command == "stop") break;
    }
}

void detect_trigger_word() {
    String aux;
    
    if (Serial.available() > 0) {
        aux = Serial.readStringUntil('\n');
        
        if (aux == "start" || aux == "stop") {command = aux;}
    }
}
