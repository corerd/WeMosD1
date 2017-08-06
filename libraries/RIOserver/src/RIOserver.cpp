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

#include "RIOserver.h"

/// PIN types
#define PIN_ANALOG	'A'
#define PIN_DIGITAL	'D'
#define PIN_VIRTUAL	'V'

/// Received control characters
#define COMMAND_SET		'='
#define COMMAND_STOPPER	'*'

/// Receive timer
#define TIMER_RX_IDLE		0
#define TIMER_RX_EXPIRED	3000  // ms

enum Status_rx {WAIT_PIN_TYPE, WAIT_PIN_ADDRESS, WAIT_SEPARATOR, WAIT_VALUE, WAIT_STOPPER};


RIOserver::RIOserver(BluetoothSerial &channel) :
						m_channel(channel),
						m_timer_rx_cnt(TIMER_RX_IDLE),
						m_run_status(WAIT_PIN_TYPE)
{
	// class constructor
}

RIOserver::~RIOserver()
{
	// class destructor here
}

/**
 * Process incoming commands and perform connection housekeeping.
 *
 * Command format:
 * <command> ::= <pin_type><pin_address><separator><pin_value><stopper>
 * <pin_type> ::= 'A' | 'D' | 'V'
 * <pin_address> ::= <integer>
 * <separator> ::= '#'
 * <pin_value> ::= <integer>
 * <stopper> ::= '*'
 * <integer> ::= <digit> | <integer><digit>
 */
void RIOserver::run()
{
	while (m_channel.available())
	{
		switch(m_run_status)
		{
			case WAIT_PIN_TYPE:
				m_pin_type = m_channel.read();
				switch (m_pin_type) {
					case PIN_ANALOG:
					case PIN_DIGITAL:
					case PIN_VIRTUAL:
						m_timer_rx_cnt = millis();
						m_run_status = WAIT_PIN_ADDRESS;
						break;
				}
				break;
			case WAIT_PIN_ADDRESS:
				m_pin_address = m_channel.parseInt();
				m_run_status = WAIT_SEPARATOR;
				break;
			case WAIT_SEPARATOR:
				if (m_channel.read() == COMMAND_SET)
				{
					m_run_status = WAIT_VALUE;
				}
				else
				{
					m_timer_rx_cnt = TIMER_RX_IDLE;
					m_run_status = WAIT_PIN_TYPE;
				}
				break;
			case WAIT_VALUE:
				m_pin_value = m_channel.parseInt();
				m_run_status = WAIT_STOPPER;
				break;
			case WAIT_STOPPER:
				if (m_channel.read() == COMMAND_STOPPER)
				{
					exec_command();
				}
				m_timer_rx_cnt = TIMER_RX_IDLE;
				m_run_status = WAIT_PIN_TYPE;
				break;
		}
	}
	if (m_timer_rx_cnt != TIMER_RX_IDLE)
	{
		if ( (millis()-m_timer_rx_cnt) > TIMER_RX_EXPIRED )
		{
			Serial.println("");
			Serial.println("TIMEOUT");
			Serial.println("");
			m_timer_rx_cnt = TIMER_RX_IDLE;
			m_run_status = WAIT_PIN_TYPE;
		}
	}
}

void RIOserver::exec_command()
{
	switch (m_pin_type) {
		case PIN_DIGITAL:
			pinMode(m_pin_address, OUTPUT);
			digitalWrite(m_pin_address, m_pin_value);
			break;
		case PIN_ANALOG:
			pinMode(m_pin_address, OUTPUT);
			if (m_pin_value > 255)
			{
				// margin high
				m_pin_value = 255;
			}
			analogWrite(m_pin_address, m_pin_value);
			break;
		case PIN_VIRTUAL:
			Serial.println("");
			Serial.println(m_pin_type);
			Serial.println(m_pin_address);
			Serial.println(m_pin_value);
			Serial.println("");
			break;
	}
}
