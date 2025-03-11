/*
    Project 15.1 7-Segment Display

    Use 74HC595 to control 7-segment display and make it display hexadecimal character "0-F".
*/

int dataPin = 8; // Pin connected to DS of 74HC595（Pin14）
int latchPin = 9; // Pin connected to ST_CP of 74HC595（Pin12）
int clockPin = 10; // Pin connected to SH_CP of 74HC595（Pin11
String command;

// Define the encoding of characters 0-F for the common-anode 7-Segment Display
byte num[] = {
    0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
    0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e
};

void setup() {
    // Put your setup code here, to run once:
    // Set pins to output
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    writeData(0xff); // Clear the display content
    Serial.begin(9600);
}

void loop() {
    // Put your main code here, to run repeatedly:
    // Display 0-F on digital tube
    int time_period = 1000;

    detect_trigger_word();

    while (command == "start") {
        for (int i = 0; i < 16; i++) {
            writeData(num[i]); // Send data to 74HC595
            Serial.print("on," + String(i));
            custom_delay(time_period);

            if (command == "stop") break;

            writeData(0xff); // Clear the display content
        }

        if (command == "stop") {stop(); break;}
    }
}

void writeData(int value) {
    // Make latchPin output low level
    digitalWrite(latchPin, LOW);
    // Send serial data to 74HC595
    shiftOut(dataPin, clockPin, LSBFIRST, value);
    // Make latchPin output high level
    digitalWrite(latchPin, HIGH);
}

void stop() {
    writeData(0xff); // Clear the display content
    Serial.write("off");
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
