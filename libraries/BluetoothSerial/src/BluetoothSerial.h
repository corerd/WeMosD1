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

#ifndef __BLUETOOTHSERIAL__
#define __BLUETOOTHSERIAL__

#include "Arduino.h"
#include "SoftwareSerial.h"


/**
 * BluetoothControlPIns Class
 *
 * Defines the pins numbers through which to control the Bluetooth module
 * as member variables.
 *
 * The class member variables are also the optional constructor parameters
 * of the declared friend class.
 * The class exposes set pin number methods for each parameter.
 * The set methods return the *this object by reference so that
 * other set methods can be chained together to set remaining parameters.
 *
 * Named parameters (a.k.a. Method chaining, Fluent interface) references:
 * https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Named_Parameter
 * https://marcoarena.wordpress.com/2011/05/27/learn-how-to-support-named-parameters-in-cpp/
 * https://marcoarena.wordpress.com/2014/12/16/bring-named-parameters-in-modern-cpp/
 */
class BluetoothControlPIns
{
  public:
    /**
     * Default BluetoothControlPIns Class constructor
     *
     * By default no pin is connected.
     */
    BluetoothControlPIns();

    /**
     * Set pin number connected to Bluetooth module STATE pin
     *
     * @param _statePin pin number
     * @return *this object by reference so that other set methods can be chained together
     */
    BluetoothControlPIns& statePin(int _statePin);

    /**
     * Set pin number connected to Bluetooth module EN pin
     *
     * @param _statePin pin number
     * @return *this object by reference so that other set methods can be chained together
     */
    BluetoothControlPIns& enPin(int _enPin);

  private:
    friend class BluetoothSerial;

    /**
     * Check the valid range of the pin number parameter
     *
     * @param pin number
     * @return false if pin number out of range, true otherwise
     */
    bool isValidPin(int pin);

    // Member variables
    int m_statePin;  /// pin number connected to Bluetooth module STATE pin
    int m_enPin;     /// pin number connected to Bluetooth module EN pin
};


/**
 * BluetoothSerial Class
 *
 * It is derived from SoftwareSerial class and
 * adds methods to access the control pins of the Bluetooth module.
 *
 * Required constructor parameters are the pins on which to receive / transmit
 * serial data from / to the Bluetooth module.
 * The optional parameters are the pins numbers through which to control
 * the Bluetooth module.
 *
 * In order to simulate named (key-value pair) parameter passing style,
 * all the optional constructor parameters are methods of BluetoothControlPIns class.
 * They return a reference to their *this object, so the method calls can be chained.
 *
 * According to positional parameters passing, a caller of a function has to list
 * its parameters following the order declared in the method’s signature.
 * Also, default values can only be given to the last parameters,
 * so it is not possible to specify one of the later parameters and use
 * the default value for former ones.
 * Named parameters let the caller pass the parameters to a function
 * in any order and they are distinguished by a name.
 * So the caller can explicitly pass all the needed parameters and default values
 * without worrying about the order used in the function declaration.
 *
 * Named parameters (a.k.a. Method chaining, Fluent interface) references:
 * https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Named_Parameter
 * https://marcoarena.wordpress.com/2011/05/27/learn-how-to-support-named-parameters-in-cpp/
 * https://marcoarena.wordpress.com/2014/12/16/bring-named-parameters-in-modern-cpp/
 *
 * SoftwareSerial base class reference:
 * https://www.arduino.cc/en/Reference/SoftwareSerial
 */
class BluetoothSerial : public SoftwareSerial
{
  public:
    /**
     * Default BluetoothSerial Class constructor
     *
     * @param receivePin the pin on which to receive serial data
     * @param transmitPin the pin on which to transmit serial data
     *
     * By default no pin is connected other than receive / transmit serial data
     * from / to the Bluetooth module.
     */
    BluetoothSerial(int receivePin, int transmitPin);

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
    BluetoothSerial(int receivePin, int transmitPin,
                      BluetoothControlPIns const& btCtrlPins);

    /// Get Bluetooth module status
    int status();

    /// Reset Bluetooth module
    void reset();

  private:
    /// Pins numbers through which to control the Bluetooth module
    BluetoothControlPIns m_btCtrlPins;
};

#endif /* __BLUETOOTHSERIAL__ */
