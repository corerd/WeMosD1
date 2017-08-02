 /**
  * ESP8266 WeMos D1 mini library collection
  * Bluetooth Serial Port Profile (SPP)
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

#ifndef _BLUETOOTHSERIAL_
#define _BLUETOOTHSERIAL_

#include "Arduino.h"
#include <SoftwareSerial.h>

/// Bluetooth module interface pins
#define BT_TXD_PIN  D5  // yellow wire
#define BT_RXD_PIN  D6  // blue wire
#define BT_DSR_PIN  D7  // green wire (STATUS pin)


class BluetoothSerial : public SoftwareSerial
{
  public:
    BluetoothSerial();
    ~BluetoothSerial();

    /// Get Bluetooth module status
    int status();
};

#endif /* _BLUETOOTHSERIAL_ */
