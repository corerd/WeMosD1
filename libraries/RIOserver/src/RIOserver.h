/**
 * ESP8266 WeMos D1 mini library collection
 * Remote GPIO (the server part)
 *
 * Allow GPIO remote management.
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

#ifndef _RIOSERVER_
#define _RIOSERVER_

#include "Arduino.h"
#include "BluetoothSerial.h"

/// PIN types
#define PIN_ANALOG	'A'
#define PIN_DIGITAL	'D'
#define PIN_VIRTUAL	'V'

/// Received control characters
#define COMMAND_SET		'='
#define COMMAND_STOPPER	'*'

/// Pointer to Send value to a Virtual Pin function
typedef void (*VirtualWriteHandler)(int pin, int value);

class RIOserver
{
  public:
    RIOserver(BluetoothSerial &channel);
    ~RIOserver();

    /// Initialize
    void begin(long speed, VirtualWriteHandler virtualWriteHnd);
    /// Process incoming commands and perform connection housekeeping
    void run();

    /**
     * Change client Widget properties
     */
    /// Send data to the client over a virtual pin
    template <typename T> void virtualPush(int virtual_pin, T v_pin_value);
    /// Set Lights Widget colour
    void widgetLights_setColour(int red, int green, int blue);

    /// Member variables
    VirtualWriteHandler m_virtualWriteHnd;

  private:
    void exec_command();

    /// Member variables
    BluetoothSerial &m_channel;
    unsigned long m_timer_rx_cnt;
    char m_run_status;
    char m_pin_type;
    int m_pin_address;
    int m_pin_value;
};

#include "RIOserver.tcc"

#endif /* _RIOSERVER_ */
