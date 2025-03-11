/*
    Project 14.1 Flowing Water Light

    Use the 74HC595 IC Chip to make a flowing water light using less GPIOs.
*/

int dataPin = 8; // Pin connected to DS of 74HC595(Pin14)
int latchPin = 9; // Pin connected to ST_CP of 74HC595(Pin12)
int clockPin = 10; // Pin connected to SH_CP of 74HC595(Pin11)
String command;

void setup() {
    // Put your setup code here, to run once:
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    writeTo595(LSBFIRST, 0x00);
    Serial.begin(9600);
}

void loop() {
    // Put your main code here, to run repeatedly:
    // Define a variable to use the 8 bits to represent the state of 8 LEDs of LED bar graph.
    // This variable is assigned to 0x01, which indicates only one LED light on.
    byte x;
    int time_period = 100;

    detect_trigger_word();

    while (command == "start") {
        x = 0x01; // 0b 0000 0001

        for (int j = 0; j < 8; j++) { // Let led light up from right to left
            writeTo595(LSBFIRST, x);
            x <<= 1; // Make the variable move one bit to left once, then the bright LED move one step to the left once.
            Serial.print("on," + String(j));
            custom_delay(time_period);

            if (command == "stop") break;
        }

        if (command == "stop") {stop(); break;}

        x = 0x80; //0b 1000 0000

        for (int j = 7; j > -1; j--) { // Let led light up from left to right
            writeTo595(LSBFIRST, x);
            x >>= 1;
            Serial.print("on," + String(j));
            custom_delay(time_period);

            if (command == "stop") {stop(); break;}
        }
    }
}

void writeTo595(BitOrder order, byte _data) {
    // Output low level to latchPin
    digitalWrite(latchPin, LOW);
    // Send serial data to 74HC595
    shiftOut(dataPin, clockPin, order, _data);
    // Output high level to latchPin, and 74HC595 will update the data to the parallel output port.
    digitalWrite(latchPin, HIGH);
}

void stop() {
    writeTo595(LSBFIRST, 0x00);
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
