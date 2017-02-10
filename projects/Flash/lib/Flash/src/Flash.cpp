/*
 * ESP8266 CheckFlashConfig by Markus Sattler
 *
 * This sketch tests if the EEPROM settings of the IDE match to the Hardware
 *
 * https://github.com/esp8266/Arduino/blob/master/libraries/esp8266/examples/CheckFlashConfig/CheckFlashConfig.ino
 */

#include "Arduino.h"
#include "Flash.h"

uint32_t Flash::chipID = ESP.getFlashChipId();
uint32_t Flash::chipSpeed = ESP.getFlashChipSpeed();
uint32_t Flash::realSize = ESP.getFlashChipRealSize();
uint32_t Flash::ideSize = ESP.getFlashChipSize();
FlashMode_t Flash::ideMode = ESP.getFlashChipMode();


// Requires Serial module
void Flash::printCfg()
{
  Serial.println("\n");

  Serial.printf("Flash real id:   %08X\n", chipID);
  Serial.printf("Flash real size: %u\n\n", realSize);

  Serial.printf("Flash ide  size: %u\n", ideSize);
  Serial.printf("Flash ide speed: %u\n", chipSpeed);
  Serial.printf("Flash ide mode:  %s\n", (ideMode == FM_QIO ? "QIO" : ideMode == FM_QOUT ? "QOUT" : ideMode == FM_DIO ? "DIO" : ideMode == FM_DOUT ? "DOUT" : "UNKNOWN"));
}

bool Flash::check()
{
  return (ideSize == realSize);
}
