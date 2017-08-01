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
#include "LedCtrl.h"

//BluetoothSerial instance
BluetoothSerial bt = BluetoothSerial();
int bt_connected = -1;

//LedCtrl instance
LedCtrl ledBuiltIn;

void setup() {
	ledBuiltIn.off();

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

	//Process any info coming from the bluetooth serial link
	if (bt.available()){
		BluetoothData=bt.read(); //Get next character from bluetooth
		Serial.print(BluetoothData);
		if(BluetoothData=='O') ledBuiltIn.on();
		if(BluetoothData=='o') ledBuiltIn.off();
	}
}
