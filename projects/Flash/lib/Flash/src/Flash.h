/*
 * ESP8266 CheckFlashConfig by Markus Sattler
 *
 * This sketch tests if the EEPROM settings of the IDE match to the Hardware
 *
 * https://github.com/esp8266/Arduino/blob/master/libraries/esp8266/examples/CheckFlashConfig/CheckFlashConfig.ino
 */

#ifndef _FLASHCONFIG_H_
#define _FLASHCONFIG_H_


#include "Arduino.h"

class Flash
{
public:
  static void printCfg();
  static bool check();
private:
  static uint32_t chipID;
  static uint32_t chipSpeed;
  static uint32_t realSize;
  static uint32_t ideSize;
  static FlashMode_t ideMode;
};


#endif // _FLASHCONFIG_H_
