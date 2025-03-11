/*
    Project 12.1 Thermometer

    A Thermistor is a temperature sensitive resistor. When it senses a change in temperature, the resistance of the
    Thermistor will change. We can take advantage of this characteristic by using a Thermistor to detect
    temperature intensity.
*/

#define PIN_ADC0 0
String command;

void setup() {
    // Put your setup code here, to run once:
    Serial.begin(9600);
}

void loop() {
    // Put your main code here, to run repeatedly:
    int adcValue;
    double adcRatio;
    double Rt; // Thermistor resistance
    int temperature;
    int time_period = 1000;

    detect_trigger_word();
    
    while (command == "start") {
        if (analogRead(PIN_ADC0) != adcValue) {
            adcValue = analogRead(PIN_ADC0);
            adcRatio = (float)adcValue / 1023.0;
            Rt = 10 * adcRatio / (1 - adcRatio);
            temperature = 1 / (1 / (273.15 + 25) + log(Rt / 10) / 3950.0) - 273.15;
            
            Serial.print("on," + String(temperature));
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
