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

#include "BluetoothSerial.h"

#define MAX_PIN 16


BluetoothSerial::BluetoothSerial(int receivePin, int transmitPin, int statusPin, int enPin) :
										SoftwareSerial(receivePin, transmitPin)
{
	// class constructor
	m_statusPin = statusPin;
	if (isValidPin(m_statusPin))
	{
		pinMode(m_statusPin, INPUT);
	}

	m_enPin = enPin;
	if (isValidPin(m_enPin))
	{
		pinMode(m_enPin, OUTPUT);
		digitalWrite(m_enPin, HIGH);
	}
}

BluetoothSerial::~BluetoothSerial()
{
	// class destructor here
}

/**
 * Get Bluetooth module status
 *
 * @return HIGH or LOW
 *
 * If statusPin is not valid, returns always HIGH
 */
int BluetoothSerial::status()
{
	if (!isValidPin(m_statusPin))
	{
		return HIGH;
	}
  return digitalRead(m_statusPin);
}

/**
 * Reset Bluetooth module
 *
 * Use EN pin to disable/enable the module.
 * If the module was previously connected, this function will disconnect it.
 */
void BluetoothSerial::reset()
{
	if (isValidPin(m_enPin))
	{
		digitalWrite(m_enPin, LOW);
		delay(100);  // ms
		digitalWrite(m_enPin, HIGH);
	}
}

bool BluetoothSerial::isValidPin(int pin) {
   return (pin >= 0 && pin <= 5) || (pin >= 12 && pin <= MAX_PIN);
}
