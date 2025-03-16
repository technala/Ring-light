#include <Arduino.h>

// Configuration variables
int delayTime = 300;  // Time in milliseconds between LED transitions (can be adjusted)

// Define the pins for D0 to D7 on ESP8266
// D0 = GPIO16, D1 = GPIO5, D2 = GPIO4, D3 = GPIO0, D4 = GPIO2, D5 = GPIO14, D6 = GPIO12, D7 = GPIO13
const int ledPins[] = {16, 5, 4, 0, 2, 14, 12, 13};  // GPIO numbers for D0-D7
const int numPins = 8;  // Number of LEDs

void setup() {
  // Initialize all LED pins as outputs
  for (int i = 0; i < numPins; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);  // Ensure all LEDs are off initially
  }
  
  // Initialize serial communication for debugging (optional)
  Serial.begin(115200);
  Serial.println("LED sequence program started");
}

void loop() {
  // Light up LEDs in sequence from D0 to D7
  for (int i = 0; i < numPins; i++) {
    digitalWrite(ledPins[i], HIGH);  // Turn on current LED
    delay(delayTime);                // Wait for specified time
    digitalWrite(ledPins[i], LOW);   // Turn off current LED
  }
}