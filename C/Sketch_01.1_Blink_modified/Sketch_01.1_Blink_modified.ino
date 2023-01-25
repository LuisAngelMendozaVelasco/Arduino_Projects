#define LED_BUILTIN 25

// the setup function runs once when you press reset or power the board
void setup() {
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);
    // initialize serial communication
    Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
    // declare local variables
    char data = '0';
    unsigned long time_now = 0;
    int time_period = 1000;
    
    /*
    Serial.available()
    Get the number of bytes (characters) available for reading from the serial port. This is data that’s already arrived and stored in the serial 
    receive buffer (which holds 64 bytes).
    */
    if(Serial.available() > 0){
        data = Serial.read();   // Reads incoming serial data.
    }
        
    while(data == '1'){
        digitalWrite(LED_BUILTIN, HIGH);    // turn the LED on (HIGH is the voltage level)
        Serial.write("1");  // Writes binary data to the serial port.                          
        time_now = millis();    // Returns the number of milliseconds passed since the Arduino board began running the current program.
        data = custom_delay(time_now, time_period); // wait for a second and return char variable
        if(data == '0') {
            break;
        }
        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
        Serial.write("0");  // Writes binary data to the serial port.    
        time_now = millis();    // Returns the number of milliseconds passed since the Arduino board began running the current program.
        data = custom_delay(time_now, time_period); // wait for a second and return char variable
        if(data == '0') {
            break;
        }
    }
}

// Function for custom time delay. If "0" is received during the time delay, the LED stops blinking.
char custom_delay(unsigned long time_now, int time_period) {
    char data = '1';
    
    while(millis() < time_now + time_period) {
        if(Serial.available() > 0){
            if(Serial.read() == '0') {
                data = '0';
                digitalWrite(LED_BUILTIN, LOW);
                Serial.write("0");
                break; 
            }
        }        
    }
    
    return data;
}
