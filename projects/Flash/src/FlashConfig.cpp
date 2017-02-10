/*
 * ESP8266 CheckFlashConfig by Markus Sattler
 *
 * This sketch tests if the EEPROM settings of the IDE match to the Hardware
 *
 * https://github.com/esp8266/Arduino/blob/master/libraries/esp8266/examples/CheckFlashConfig/CheckFlashConfig.ino
 */

#include "Arduino.h"
#include "LedCtrl.h"
#include "Flash.h"

LedCtrl ledRed(LED_CUSTOM);

void setup(void) {
  Serial.begin(115200);

  Flash::printCfg();

  if (Flash::check())
  {
    Serial.println("Flash Chip configuration OK.\n");
  }
  else
  {
    Serial.println("Flash Chip configuration wrong!\n");
  }
}

void loop()
{
  ledRed.toggle();
  delay(3000);
}
