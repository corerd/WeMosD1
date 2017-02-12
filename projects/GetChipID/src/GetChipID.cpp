/*  Find WeMos Chip ID
 *  wemos.cc
 *
 *  See: https://www.wemos.cc/tutorial/how-find-chip-id.html
 *
 */

#include "Arduino.h"

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("");
  Serial.println("");
  Serial.println("Check ID in:");
  Serial.println("https://www.wemos.cc/verify_products");
  Serial.printf("Chip ID = %08X\n", ESP.getChipId());
  Serial.println("");
  Serial.println("");
  delay(5000);
}
