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

#include "SMBus.h"


/**
 * SMBus Class constructor.
 *
 * @param chk_PEC enables optional PEC verification (default TRUE).
 * @param clk_freq the optional value (in Hertz) of communication clock (default SMB_CLK_STANDARD).
 */
SMBus::SMBus(bool chk_PEC, uint32_t clk_freq)
{
    chk_PEC = chk_PEC;
    clk_freq = clk_freq;
    smb_error = SMB_ERR_NONE;
}


/**
 * Setup SMBus communication.
 */
void SMBus::begin()
{
    Wire.begin();
}


/**
 * Check if some SMBus device responds to the suppled address.
 *
 * @param addr  7 bit SMBus slave device address.
 *
 * @Return      Two's complement negative communication error code.
 */
int SMBus::chk_address(uint8_t addr)
{
    uint8_t error;

    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(addr);
    error = Wire.endTransmission();
    return -error;
}


/**
 * Perform complete SMBus master read transaction.
 *
 * @param addr     7 bit SMBus slave device address.
 * @param cmd      SMBus command. Will be shifted out MSB first.
 * @param in_buf   Pointer to read data buffer
 * @param in_sz    Read data requested bytes
 *
 * @Return         Number of read bytes on success, otherwise
 *                 two's complement negative communication error code.
 */
int SMBus::read(uint8_t addr, uint16_t cmd, uint8_t* in_buf, uint8_t in_sz)
{
    uint8_t cmd_data[2];
    uint8_t cmd_len;
    uint8_t request_size;
    uint8_t nread;

    smb_error = SMB_ERR_NONE;
    cmd_len = 0;
    if(cmd > 255)
    {
        // MSB hifted out first
        cmd_data[0] = cmd >> 8;
        cmd_len = 1;
    }
    cmd_data[cmd_len++] = cmd; // command LSB

    if (in_sz <= 2)
    {
        // perform a read byte / word
        request_size = in_sz;
    }
    else
    {
        // perform a block read
        request_size = in_sz + 1;
    }

    Wire.beginTransmission(addr); // start transmission
    Wire.write(cmd_data, cmd_len); // send command
    smb_error = Wire.endTransmission(false); // don't send a stop condition
    if (smb_error != SMB_ERR_NONE)
        return -smb_error;

    request_size = Wire.requestFrom(addr, request_size);
    if (in_sz > 2)
    {
        // block read requested
        if (request_size < 2)
        {
            // At least Byte Count more one data byte is expected
            smb_error = SMB_ERR_BREAD;
            return -smb_error;
        }
        request_size = Wire.read(); // skip Byte Count
    }
    if (request_size > in_sz)
    {
        smb_error = SMB_ERR_BSIZE;
        return -smb_error;
    }

    nread = 0;
    while((Wire.available()) && (nread < request_size)) // slave may send less than requested
    {
       *in_buf++ = Wire.read();  // receive and store a byte
       nread++;
    }
    return nread;
}


/**
 * Perform complete SMBus master write transaction.

 * @param addr     7 bit SMBus slave device address.
 * @param cmd      SMBus command. Will be shifted out MSB first.
 * @param out_buf  Pointer to data buffer to send
 * @param out_sz   Number of data bytes to send
 *
 * @Return         Number of written bytes on success, otherwise
 *                 two's complement negative communication error code.
 */
int SMBus::write(uint8_t addr, uint16_t cmd, uint8_t* out_buf, uint8_t out_sz)
{
    uint8_t frame[16];
    uint8_t frame_len;

    smb_error = SMB_ERR_NONE;
    frame_len = 0;
    if(cmd > 255)
    {
        // MSB hifted out first
        frame[0] = cmd >> 8;
        frame_len = 1;
    }
    frame[frame_len++] = cmd; // command LSB
    if (out_sz > 2)
    {
        // perform a block write
        frame[frame_len++] = out_sz; // Byte Count
    }
    memcpy(&frame[frame_len], out_buf, out_sz); // payload
    frame_len += out_sz;

/*
    Serial.println();
    Serial.print("---DEBUG--- frame=");
    print_hex(frame, frame_len);
    Serial.println();
*/

    Wire.beginTransmission(addr); // start transmission
    Wire.write(frame, frame_len); // send command
    smb_error = Wire.endTransmission(); // send a stop condition
    if (smb_error != SMB_ERR_NONE)
        return -smb_error;

/*
    Wire.beginTransmission(addr); // start transmission
    Wire.write(cmd_data, cmd_len); // send command
    if (out_sz > 2)
    {
        // perform a block write
        Wire.write(out_sz); // Byte Count
    }
    Wire.write(out_buf, out_sz); // send command
    Wire.endTransmission(); // send a stop condition
*/

    return out_sz;
}
