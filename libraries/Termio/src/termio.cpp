#include "termio.h"

#define KEY_ESC     27


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
char *readline()
{
    static char inBuffer[81] = {0}; // Allocate some space for the string
    static uint8_t skipChar = 0;
    static uint8_t index = 0; // Index into array; where to store the character
    char inChar; // Where to store the character read

    inChar = '\0';
    while (Serial.available())
    {
        inChar = Serial.read(); // Read a character
        if (skipChar)
        {
            // discard the character
            skipChar--;
            continue;
        }
        if (inChar == KEY_ESC)
        {
            // it will follow a 16 bits coded character
            // skip this and next 2 characters
            skipChar = 2;
            continue;
        }
        if (inChar == '\b')
        {
            // backspace
            if (index)
            {
                Serial.print("\b \b");
                index--;
                inBuffer[index] = '\0'; // Null terminate the string
            }
            continue;
        }
        if (inChar == '\n')
        {
            // End Of Line: hit ENTER key
            break;
        }
        if ( (inChar != ' ') && (!isalnum(inChar)) )
        {
            continue;
        }
        if ( index < (sizeof(inBuffer)-1) ) // Two less than the size of the array
        {
            Serial.write(inChar);   // Echo the character
            inBuffer[index] = inChar;
            index++; // Increment where to write next
        }
        else
        {
            // input buffer full
            inChar = '\n';  // force End Of Line
            break;
        }
    }
    if ( (!skipChar) && (inChar == '\n') )
    {
        // End Of Line
        inBuffer[index] = '\0'; // Null terminate the string
        index = 0;
        Serial.println();
        return inBuffer;
    }
    return nullptr;
}
