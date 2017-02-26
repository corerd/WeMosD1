#include "Arduino.h"
#include "I2Cmon.h"

#define PROMPT  "i2c: "


void setup()
{
    Wire.begin();
    Serial.begin(115200);
    I2Cmon::begin(PROMPT);
}

void loop()
{
    I2Cmon::process();
}
