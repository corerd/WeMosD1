#include "Arduino.h"
#include "LedCtrl.h"

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
