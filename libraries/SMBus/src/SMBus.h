 /**
  * ESP8266 WeMos D1 mini library collection
  * SMBus Library
  *
  * Derived from infinityPV INA233 ADC/I2C Arduino Library:
  * https://github.com/infinityPV/infinityPV_INA233_Arduino-library
  *
  * =============================================================================
  * This code is placed under the MIT license
  * Copyright (c) 2016 Corrado Ubezio
  *
  * Permission is hereby granted, free of charge, to any person obtaining a copy
  * of this software and associated documentation files (the "Software"), to deal
  * in the Software without restriction, including without limitation the rights
  * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  * copies of the Software, and to permit persons to whom the Software is
  * furnished to do so, subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in
  * all copies or substantial portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  * THE SOFTWARE.
  * =============================================================================
  */

#ifndef __SMBUS__
#define __SMBUS__

#include "Arduino.h"
#include <Wire.h>


/// Clock frequency (in Hertz) for SMBus communication
#define SMB_CLK_STANDARD     100000
#define SMB_CLK_FAST         400000
#define SMB_CLK_FAST_PLUS   1000000

/// SMBus communication error codes
#define SMB_ERR_NONE         0x00  // Success
#define SMB_ERR_TXSIZE       0x01  // Data too long to fit in transmit buffer
#define SMB_ERR_NAK_TX_ADDR  0x02  // Received NACK on transmit of address
#define SMB_ERR_NAK_TX_DTA   0x03  // Received NACK on transmit of data
#define SMB_ERR_OTHER        0x04  // Other error
#define SMB_ERR_BREAD        0x40  // Block Read byte count mismatch
#define SMB_ERR_BSIZE        0x40  // Block Read more bytes than expected


/**
 * Class SMBus
 *
 */
class SMBus
{
  public:
    SMBus(bool chk_PEC=true, uint32_t clk_freq=SMB_CLK_STANDARD);

    void begin();
    int chk_address(uint8_t addr);
    int read(uint8_t addr, uint16_t cmd, uint8_t* in_buf, uint8_t in_sz);
    int write(uint8_t addr, uint16_t cmd, uint8_t* out_buf, uint8_t out_sz);

  private:
    bool chk_PEC;
    uint32_t clk_freq;
    uint8_t smb_error;
};


#endif /* __SMBUS__ */
