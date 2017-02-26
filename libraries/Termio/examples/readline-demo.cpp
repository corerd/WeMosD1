#include "Arduino.h"
#include "termio.h"

#define PROMPT  "readline: "

void setup()
{
    Serial.begin(115200);
    Serial.print(PROMPT);
}

void loop()
{
    char *inLine;

    inLine = readline();
    if (inLine == nullptr)
    {
        return;
    }
    if (strlen(inLine) > 0)
    {
        Serial.printf("Received: %s\n", inLine);
    }
    Serial.print(PROMPT);
}
