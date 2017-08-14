/**
 * ESP8266 WeMos D1 mini library collection
 * BluetoothSerial demo
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
#include "RIOserver.h"

/// Demo pin
#define DIMMER_PIN  15

/// Bluetooth module interface pins
#define BT_RXD_PIN  D5  // green wire
#define BT_TXD_PIN  D6  // yellow wire
#define BT_DSR_PIN  D7  // blue wire (STATUS pin)

// BluetoothSerial instance
BluetoothSerial bt = BluetoothSerial(BT_RXD_PIN, BT_TXD_PIN,
														BluetoothControlPIns()
															.statePin(BT_DSR_PIN) );

/// RIOserver instance
RIOserver remote = RIOserver(bt);

/// RIOserver callback
void virtualWrite(int pin, int value)
{
  switch(pin)
  {
    case 0:
      // set Red component value
      remote.widgetLights_setColour(value, -1, -1);
      // feedback
      analogWrite(DIMMER_PIN, value);
      break;
  }
}

/// Show Bluetooth Status
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

void setup() {
  // Set Analog pin
  pinMode(DIMMER_PIN, OUTPUT);

	// Initialize embedded Serial line for debug
	Serial.begin(9600);

  // Initialize RIO server
  remote.begin(9600, virtualWrite);
}

void loop() {
  chkBluetoothStatus();

	//Process any info coming from the bluetooth serial link
	remote.run();
}
