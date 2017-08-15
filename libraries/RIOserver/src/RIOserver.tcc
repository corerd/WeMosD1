/**
 * ESP8266 WeMos D1 mini library collection
 * Remote GPIO (the server part)
 *
 * Implementations of templates declared in RIOserver.h
 *
 * A template is not a class or a function.
 * A template is a pattern that the compiler uses to generate a family
 * of classes or functions.
 *
 * In order for the compiler to generate the code, it must see both
 * the template definition (not just declaration) and the specific types/whatever
 * used to fill in the template.
 *
 * A common solution to this is to write the template declaration in a header file,
 * then implement the class in an implementation file (for example .tcc),
 * and include this implementation file at the end of the header.
 *
 * See: https://cpp.cb-geo.com/header/tcc_file.html
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
 # error "Don't include this file directly, include RIOserver.h instead"
 #endif

/**
 * Send data to the client over a virtual pin
 *
 * @param virtual_pin   virtual pin ID
 * @param v_pin_value   value to send - any data type
 */
template <typename T> void RIOserver::virtualPush(int virtual_pin, T v_pin_value)
{
  m_channel.print(PIN_VIRTUAL);
  m_channel.print(virtual_pin);
  m_channel.print(COMMAND_SET);
  m_channel.print(v_pin_value);
  m_channel.print(COMMAND_STOPPER);
}
