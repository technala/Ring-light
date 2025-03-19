#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "credentials.h"  // Include credentials from separate file

// Web server on port 80
ESP8266WebServer server(80);

// Configuration variables
int delayTime = 50;  // Time in milliseconds between LED transitions
bool isRunning = false;  // Flag to control LED sequence
bool isSequenceMode = true;  // true = sequence mode, false = all LEDs mode

// Define the pins for D0 to D7 on ESP8266
// D0 = GPIO16, D1 = GPIO5, D2 = GPIO4, D3 = GPIO0, D4 = GPIO2, D5 = GPIO14, D6 = GPIO12, D7 = GPIO13
const int ledPins[] = {16, 5, 4, 0, 2, 14, 12, 13};  // GPIO numbers for D0-D7
const int numPins = 8;  // Number of LEDs

void handleRoot() {
  String html = "<html><head>";
  html += "<link rel='stylesheet' href='https://bergenroth.de/simple.min.css'>";
  html += "<link rel='stylesheet' href='https://bergenroth.de/style.css'>";
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; margin: 20px; }";
  html += "button { padding: 10px 20px; margin: 5px; }";
  html += ".control-panel { background-color: #f0f0f0; padding: 20px; border-radius: 10px; }";
  html += ".mode-active { background-color: #2196F3 !important; }";
  html += "</style>";
  html += "</head><body>";
  html += "<div class='control-panel'>";
  html += "<h1>LED Control Panel</h1>";
  
  // Mode selection buttons
  html += "<p>Mode: ";
  html += "<a href='/sequence'><button style='background-color: " + String(isSequenceMode ? "#2196F3" : "#808080") + "; color: white;'>Sequence Mode</button></a>";
  html += "<a href='/all'><button style='background-color: " + String(!isSequenceMode ? "#2196F3" : "#808080") + "; color: white;'>All LEDs Mode</button></a>";
  html += "</p>";
  
  // Start/Stop buttons
  html += "<p><a href='/start'><button style='background-color: #4CAF50; color: white;'>Start LEDs</button></a>";
  html += "<a href='/stop'><button style='background-color: #f44336; color: white;'>Stop LEDs</button></a></p>";
  
  // Delay control (only shown in sequence mode)
  if (isSequenceMode) {
    html += "<form action='/setdelay' method='get'>";
    html += "<p>Current Delay: " + String(delayTime) + "ms</p>";
    html += "<p>Set new delay (ms): <input type='number' name='delay' value='" + String(delayTime) + "' min='10' max='2000'>";
    html += "<input type='submit' value='Set Delay'></p>";
    html += "</form>";
  }
  
  html += "</div></body></html>";
  server.send(200, "text/html", html);
}

void handleModeChange(String mode) {
  isSequenceMode = (mode == "sequence");
  // When changing modes, stop the current operation
  isRunning = false;
  // Turn off all LEDs
  for (int i = 0; i < numPins; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleStart() {
  isRunning = true;
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleStop() {
  isRunning = false;
  // Turn off all LEDs
  for (int i = 0; i < numPins; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleSetDelay() {
  if (server.hasArg("delay")) {
    int newDelay = server.arg("delay").toInt();
    // Ensure the delay is within reasonable bounds
    if (newDelay >= 10 && newDelay <= 2000) {
      delayTime = newDelay;
    }
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  // Initialize all LED pins as outputs
  for (int i = 0; i < numPins; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);  // Ensure all LEDs are off initially
  }
  
  // Initialize serial communication
  Serial.begin(115200);
  Serial.println("LED sequence program started");

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  // Setup web server routes
  server.on("/", handleRoot);
  server.on("/sequence", []() { handleModeChange("sequence"); });
  server.on("/all", []() { handleModeChange("all"); });
  server.on("/start", handleStart);
  server.on("/stop", handleStop);
  server.on("/setdelay", handleSetDelay);
  
  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Handle client requests
  server.handleClient();

  // Only run if isRunning is true
  if (isRunning) {
    if (isSequenceMode) {
      // Sequence mode: Light up LEDs one after another
      for (int i = 0; i < numPins; i++) {
        digitalWrite(ledPins[i], HIGH);  // Turn on current LED
        delay(delayTime);                // Wait for specified time
        digitalWrite(ledPins[i], LOW);   // Turn off current LED
      }
    } else {
      // All LEDs mode: Keep all LEDs on
      for (int i = 0; i < numPins; i++) {
        digitalWrite(ledPins[i], HIGH);
      }
    }
  }
}