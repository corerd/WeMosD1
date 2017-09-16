/*
  Basic Ticker usage

  Ticker is an object that will call a given function with a certain period.
  Each Ticker calls one function. You can have as many Tickers as you like,
  memory being the only limitation.

  A function may be attached to a ticker and detached from the ticker.
  There are two variants of the attach function: attach and attach_ms.
  The first one takes period in seconds, the second one in milliseconds.

  Use the blue built-in LED on WeMos D1 Mini Pro and an external one
  connected to one of the GPIO pins.
*/

#include "Arduino.h"
#include "Ticker.h"
#include "LedCtrl.h"

// Defines the GPIO pin where is connected a custom led
#define LED_CUSTOM  D0

Ticker flipper;

LedCtrl ledBuiltIn;
LedCtrl ledRed(LED_CUSTOM);


int count = 0;

void flip()
{
  ledBuiltIn.toggle();
  ledRed.toggle();

  ++count;
  // when the counter reaches a certain value, start blinking like crazy
  if (count == 20)
  {
    flipper.attach(0.1, flip);
  }
  // when the counter reaches yet another value, restore low blinking freq
  else if (count == 120)
  {
    count = 0;
    flipper.attach(0.3, flip);
  }
}

void setup() {
  ledBuiltIn.on();
  ledRed.off();

  // flip the pin every 0.3s
  flipper.attach(0.3, flip);
}

void loop() {
}
