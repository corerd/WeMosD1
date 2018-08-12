/**
 * ESP8266 WeMos D1 mini library collection
 * BluetoothSerial Terminal Demo
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

#include "Arduino.h"
#include "BluetoothSerial.h"

/// Bluetooth module interface pins
#ifdef WEMOS_D1
#define BT_EN_PIN   D0  // orange wire
#define BT_RXD_PIN  D5  // green wire
#define BT_TXD_PIN  D6  // yellow wire
#define BT_DSR_PIN  D7  // blue wire (STATUS pin)
#else
#define BT_EN_PIN   2   // orange wire (voltage divider)
#define BT_RXD_PIN  3   // green wire
#define BT_TXD_PIN  4   // yellow wire (voltage divider)
#define BT_DSR_PIN  5   // blue wire (STATUS pin)
#endif

// BluetoothSerial instance
BluetoothSerial bt = BluetoothSerial(BT_RXD_PIN, BT_TXD_PIN,
                            BluetoothControlPIns()
                              .statePin(BT_DSR_PIN) );
                              //.enPin(BT_EN_PIN) );

void chkBluetoothStatus()
{
  static int bt_connected = -1;
  int bt_status;

  bt_status = bt.status();
  if (bt_connected != bt_status) {
    bt_connected = bt_status;
    Serial.println("");
    if (bt_connected) {
      Serial.println(">CONNECTED<");
    } else {
      Serial.println(">DISCONNECTED<");
    }
  }
}

void terminal()
{
  char SerialData;

  while (Serial.available() > 0)
  {
    SerialData = Serial.read();
    if (SerialData == 27)  // ESC
    {
      bt.reset();
    }
    else
    {
      Serial.print(SerialData);  // local echo
      bt.print(SerialData);
    }
  }

  while (bt.available() > 0)
  {
    Serial.print((char)bt.read());
  }
}

void setup()
{
  // Initialize embedded Serial line
  Serial.begin(9600);

  // Initialize Bluetooth Serial line
  bt.begin(9600);

  Serial.print("\nBluetooth Terminal\n");
}

void loop()
{
  chkBluetoothStatus();
  terminal();
}
