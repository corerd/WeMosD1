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

#define MAX_PIN_NUMBER 		16
#define PIN_UNCONNECTED		-1


/**
 * Default BluetoothSerial Class constructor
 *
 * @param receivePin the pin on which to receive serial data
 * @param transmitPin the pin on which to transmit serial data
 *
 * By default no pin is connected other than receive / transmit serial data
 * from / to the Bluetooth module.
 */
BluetoothSerial::BluetoothSerial(int receivePin, int transmitPin) :
									SoftwareSerial(receivePin, transmitPin)
{
	// Initialize pin numbers through which to control the Bluetooth module
	// with default values (no control pins is connected)
	m_btCtrlPins = BluetoothControlPIns();
}

/**
 * BluetoothSerial Class constructor assigning pin numbers through which
 * to control the Bluetooth module.
 *
 * @param receivePin the pin on which to receive serial data
 * @param transmitPin the pin on which to transmit serial data
 * @param btCtrlPins the object referenced to copy to member variable
 *
 * The optional control pins numbers are set by calling BluetoothControlPIns
 * class methods in a named (key-value pair) parameter passing style.
 */
BluetoothSerial::BluetoothSerial(int receivePin, int transmitPin,
																	BluetoothControlPIns const& btCtrlPins) :
																			SoftwareSerial(receivePin, transmitPin),
																			m_btCtrlPins(btCtrlPins)
{
}

/**
 * Get Bluetooth module status
 *
 * @return HIGH or LOW
 *
 * If statePin is not valid, returns always HIGH
 */
int BluetoothSerial::status()
{
	if (m_btCtrlPins.m_statePin == PIN_UNCONNECTED)
	{
		return HIGH;
	}
	return digitalRead(m_btCtrlPins.m_statePin);
}

/**
 * Reset Bluetooth module
 *
 * Use EN pin to disable/enable the module.
 * If the module was previously connected, this function will disconnect it.
 */
void BluetoothSerial::reset()
{
	if (m_btCtrlPins.m_enPin == PIN_UNCONNECTED)
	{
		return;
	}
	digitalWrite(m_btCtrlPins.m_enPin, LOW);
	delay(100);  // ms
	digitalWrite(m_btCtrlPins.m_enPin, HIGH);
}


 /**
	* Default BluetoothControlPIns Class constructor
	*
	* By default no pin is connected.
	*/
BluetoothControlPIns::BluetoothControlPIns() :
												m_statePin(PIN_UNCONNECTED),
												m_enPin(PIN_UNCONNECTED)
{
	// class constructor
}

/**
 * Set pin number connected to Bluetooth module STATE pin
 *
 * @param _statePin pin number
 * @return *this object by reference so that other set methods can be chained together
 */
BluetoothControlPIns& BluetoothControlPIns::statePin(int _statePin)
{
	if (isValidPin(_statePin))
	{
		m_statePin = _statePin;
		pinMode(m_statePin, INPUT);
	}
	return *this;
}

/**
 * Set pin number connected to Bluetooth module EN pin
 *
 * @param _enPin pin number
 * @return *this object by reference so that other set methods can be chained together
 */
BluetoothControlPIns& BluetoothControlPIns::enPin(int _enPin)
{
	if (isValidPin(_enPin))
	{
		m_enPin = _enPin;
		pinMode(m_enPin, OUTPUT);
		digitalWrite(m_enPin, HIGH);
	}
	return *this;
}

/**
 * Check the valid range of the pin number parameter
 *
 * @param pin number
 * @return false if pin number out of range, true otherwise
 */
bool BluetoothControlPIns::isValidPin(int pin)
{
   return (pin >= 0 && pin <= 5) || (pin >= 12 && pin <= MAX_PIN_NUMBER);
}
