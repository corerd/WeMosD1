#ifndef __TERMIO_H__
#define __TERMIO_H__

#include "Arduino.h"


/**
 * Read from serial port till EOL or buffer full
 *
 * Read incoming serial characters and store them in a buffer until new line.
 * New line character is not included.
 * The function doesn't suspend.
 *
 * @return nullptr if ENTER key (new line) is not hit,
 *         otherwise the pointer to the buffer.
 */
char *readline();

#endif // __TERMIO_H__
