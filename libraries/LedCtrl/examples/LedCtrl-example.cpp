#include "Arduino.h"
#include "LedCtrl.h"

// Defines the GPIO pin where is connected a custom led
#define LED_CUSTOM  D0

LedCtrl ledBlue;
LedCtrl ledRed(LED_CUSTOM);

void setup()
{
  ledBlue.on();
  ledRed.off();
}

void loop()
{
  ledBlue.toggle();
  ledRed.toggle();
  delay(1500);
}
