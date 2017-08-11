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

/// Bluetooth module interface pins
#define BT_TXD_PIN  D5  // yellow wire
#define BT_RXD_PIN  D6  // blue wire
#define BT_DSR_PIN  D7  // green wire (STATUS pin)

// BluetoothSerial instance
BluetoothSerial bt = BluetoothSerial(BT_RXD_PIN, BT_TXD_PIN, BT_DSR_PIN);
int bt_connected = -1;

// RIOserver instance
RIOserver remote = RIOserver(bt);

int wLights_toggle = 0;
unsigned long wLights_toggle_timer = 0;


void setup() {
	//initialize embedded Serial line for debug
	Serial.begin(9600);

	//initialize Bluetooth line
	bt.begin(9600);
}

void loop() {
	char BluetoothData; // the data received from bluetooth serial link
	int bt_status;

	bt_status = bt.status();
	if (bt_connected != bt_status) {
		bt_connected = bt_status;
		Serial.println("");
		if (bt_connected) {
			Serial.println("CONNECTED");
		} else {
			Serial.println("DISCONNECTED");
		}
	}

	if (bt_connected)
	{
		if ( (millis()-wLights_toggle_timer) > 3000 )
		{
			 if (wLights_toggle)
			 {
				 wLights_toggle = 0;
				 remote.wLightsPropertySet(0, 0, 0);
			 }
			 else
			 {
				 wLights_toggle = 1;
				 remote.wLightsPropertySet(255, 255, 255);
			 }
			wLights_toggle_timer = millis();
		}
	}

	//Process any info coming from the bluetooth serial link
	remote.run();
}
