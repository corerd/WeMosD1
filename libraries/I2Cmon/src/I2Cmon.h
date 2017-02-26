#ifndef __I2CMON_H__
#define __I2CMON_H__

#include "Arduino.h"
#include "I2Cdev.h"
#include "termio.h"


struct i2c_data_t {
    bool isValToWrite;
    uint8_t dev;
    uint8_t reg;
    uint8_t reg_val;
};

class I2Cmon
{
  public:
    I2Cmon();

    static void begin(const char *prompt);
    static void process();
};


#endif // __I2CMON_H__
