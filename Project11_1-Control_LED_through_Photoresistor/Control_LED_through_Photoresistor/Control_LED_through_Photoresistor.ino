/*
    Project 11.1 Control LED through Photoresistor

    Make a night lamp with the following function: when the ambient light is less (darker environment) the LED
    will automatically become brighter to compensate and when the ambient light is greater (brighter
    environment) the LED will automatically dim to compensate.
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
    int time_period = 100;

    detect_trigger_word();
    
    while (command == "start") {
        if (map(analogRead(PIN_ADC0), 0, 1023, 0, 255) != ADC_mapped) {
            ADC_mapped = map(analogRead(PIN_ADC0), 0, 1023, 0, 255);
            
            analogWrite(LED_BUILTIN, ADC_mapped);
            Serial.print("on," + String(ADC_mapped));
            custom_delay(time_period);
        }

        if (command == "stop") {stop(); break;}
    }
}

void stop() {
    analogWrite(LED_BUILTIN, 0);
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
