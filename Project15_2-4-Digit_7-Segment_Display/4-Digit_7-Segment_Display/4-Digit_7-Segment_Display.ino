/*
    Project 15.2 4-Digit 7-Segment Display

    Use the 74HC595 IC chip to control the 4-digit 7-segment display, and use the dynamic
    scanning method to show the changing number characters.
*/

int dataPin = 7; // Pin connected to DS of 74HC595（Pin14）
int latchPin = 8; // Pin connected to ST_CP of 74HC595（Pin12）
int clockPin = 9; // Pin connected to SH_CP of 74HC595（Pin11）
int comPin[] = {10, 11, 12, 13}; // Common pin (anode) of 4 digit 7-segment display
String command;

// Define the encoding of characters 0-F of the common-anode 7-Segment Display
byte num[] = {
    0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
    0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e
};

void setup() {
    // Put your setup code here, to run once:
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    writeData(0xff);
    Serial.begin(9600);

    for (int i = 0; i < 4; i++) pinMode(comPin[i], OUTPUT);
}

void loop() {
    // Put your main code here, to run repeatedly:
    int time_period_1 = 1000;
    int time_period_2 = 5;
    unsigned long time_now;

    detect_trigger_word();

    while (command == "start") {
        for (int j = 0; j < 16; j++) {
            time_now = millis();

            while (millis() < time_now + time_period_1) {
                for (int i = 0; i < 4; i++) {
                    // Select a single 7-segment display
                    electDigitalDisplay(i);

                    // Send data to 74HC595
                    if (i+j < 16) writeData(num[i+j]);
                    else writeData(num[i+j-16]);

                    custom_delay(time_period_2);

                    if (command == "stop") break;

                    // Clear the display content
                    writeData(0xff);
                }

                if (command == "stop") break;
            }

            if (command == "stop") break;
        }

        if (command == "stop") {stop(); break;}
    }
}

void electDigitalDisplay(byte com) {
    // Close all single 7-segment display
    for (int i = 0; i < 4; i++) digitalWrite(comPin[i], LOW);
    // Open the selected single 7-segment display
    digitalWrite(comPin[com], HIGH);
}

void writeData(int value) {
    // Make latchPin output low level
    digitalWrite(latchPin, LOW);
    // Send serial data to 74HC595
    shiftOut(dataPin, clockPin, LSBFIRST, value); // Make latchPin output high level
    // Make latchPin output high level, then 74HC595 will update data to parallel output
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
