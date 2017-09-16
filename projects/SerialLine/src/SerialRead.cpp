// Wiring/Arduino code:
// Read data from the serial and turn ON or OFF a light depending on the value

#include "Arduino.h"
#include "LedCtrl.h"

// Defines the GPIO pin where is connected a custom led
#define LED_CUSTOM  D0

LedCtrl ledBlue; // built in led
LedCtrl ledRed(LED_CUSTOM); // Define a custom led
char val; // Data received from the serial port

void setup() {
  Serial.begin(115200); // Start serial communication at 9600 bps
}

void loop() {
  ledBlue.toggle();
  while (Serial.available()) { // If data is available to read,
    val = Serial.read(); // read it and store it in val
  }
  if (val == 'H') { // If H was received
    // turn the LED on
    ledRed.on();
  } else {
    // Otherwise turn it OFF
    ledRed.off();
  }
  delay(100); // Wait 100 milliseconds for next reading
}
