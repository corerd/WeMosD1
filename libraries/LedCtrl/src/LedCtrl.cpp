/**
 * ESP8266 WeMos D1 mini library collection
 * Abstracts led functions into a convenient class
 *
 * By default it is used the blue LED on the WeMos D1 mini board,
 * otherwise the user has to supplied the GPIO pin where the led is connected.
 *
 * The blue LED on the WeMos D1 mini board is connected to D4 (GPIO2).
 * It is referenced as LED_BUILTIN and it is active LOW.
 *
 * To connect an external led, follow this tutorial:
 * http://iot-playground.com/blog/2-uncategorised/38-esp8266-and-arduino-ide-blink-example
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


#include "LedCtrl.h"

/**
 * LedMan constructor
 *
 * @param pin int GPIO connecting the LED
 * @param voltageToActivate int voltage value (HIGH|LOW) to activate the LED
 */
LedCtrl::LedCtrl(int pin, int voltageToActivate)
{
  _pin = pin;
  _voltageToActivate = voltageToActivate & (LOW+HIGH);
  if (_pin == LED_BUILTIN)
  {
    // The on board blue LED_BUILTIN it is active LOW
    _voltageToActivate = LOW;
  }
  pinMode(_pin, OUTPUT);
}

/**
 * Turn LED on
 *
 * Apply the voltage level (HIGH or LOW) to the LED pin
 * according to the logic level stored in the _voltageToActivate member.
 */
void LedCtrl::on()
{
  digitalWrite(_pin, _voltageToActivate);
}

/**
 * Turn LED off
 *
 * Apply the voltage level to the LED pin
 * according to the logic level stored in the _voltageToActivate member.
 */
void LedCtrl::off()
{
  // Since HIGH value is 1 and _voltageToActivate is in the range 0..1,
  // the expression (HIGH-_voltageToActivate) represents
  // the direct or reversed logic to apply to the LED pin.
  digitalWrite(_pin, HIGH - _voltageToActivate);
}

/**
 * Toggle the LED pin voltage level
 */
void LedCtrl::toggle()
{
  digitalWrite(_pin, digitalRead(_pin) ^ 1);
}
