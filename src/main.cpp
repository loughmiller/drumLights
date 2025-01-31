#include <Arduino.h>

// Define the LED pin
const int ledPin = LED_BUILTIN; // For built-in LED, or any other digital pin

void setup() {
  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
    // Analog read pin A6
    // 0 - 1023
    int velocity = analogRead(A6);

    // print the velocity if it is greater than 800
    if (velocity > 200) {
        Serial.println(velocity);
    }
}