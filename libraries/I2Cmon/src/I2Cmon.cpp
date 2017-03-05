#include "I2Cmon.h"


const char *I2CmonPprompt = "> ";  // default
struct i2c_data_t i2c_cmd_data;


bool isStrHex(char *str)
{
    if (*str == '\0')
    {
        return false;
    }
    while (*str)
    {
        if ( !isxdigit(*str) )
        {
            return false;
        }
        str++;
    }
    return true;
}

int strtobyte(char *str)
{
    long byteval;

    if (!isStrHex(str))
    {
        return -1;
    }
    byteval = strtol(str, NULL, 16);
    if ( (byteval < 0) || (byteval > 255) )
    {
        return -1;
    }
    return (uint8_t)byteval;
}

// <device-addr> <register-addr> [<register-value>]
bool cmd_parse(char *input, i2c_data_t *i2c_conf)
{
    int deviceAddr = -1;
    int registerAddr = -1;
    int registerValue = -1;
    char mode = 0;

    uint8_t nToken = 0;
    char* token = strtok(input, " ");
    while (token != NULL)
    {
        switch (nToken) {
        case 0:
            // device address
            deviceAddr = strtobyte(token);
            break;
        case 1:
            // register address
            registerAddr = strtobyte(token);
            mode = 'r';
            break;
        case 2:
            // value
            mode = 'w';  // overwrite mode
            registerValue = strtobyte(token);
            break;
        }
        nToken++;
        token = strtok(NULL, " ");
    }
    if ( (nToken < 2) || (nToken > 3) )
    {
        Serial.println("Syntax: <device-addr> <register-addr> [<register-value>]");
        return false;
    }
    if (deviceAddr < 0)
    {
        Serial.println("Invalid device address");
        return false;
    }
    if (registerAddr < 0)
    {
        Serial.println("Invalid register address");
        return false;
    }
    if ( (mode == 'w') && (registerValue < 0) )
    {
        Serial.println("Invalid register value");
        return false;
    }
    i2c_conf->dev = deviceAddr;
    i2c_conf->reg = registerAddr;
    i2c_conf->reg_val = registerValue;
    if (mode == 'w')
    {
        i2c_conf->isValToWrite = true;
    }
    else
    {
        i2c_conf->isValToWrite = false;
    }
    return true;
}

void cmd_exec(i2c_data_t *i2c_conf)
{
    if (i2c_conf->isValToWrite)
    {
        // Serial.printf("Device 0x%02X: set register 0x%02X to 0x%02X\n",
        //                i2c_conf->dev, i2c_conf->reg, i2c_conf->reg_val);
        if ( ! I2Cdev::writeBytes(i2c_conf->dev, i2c_conf->reg,
                                                1, &i2c_conf->reg_val) )
        {
            Serial.printf("FAIL writing %02X to register %02X to device %02X\n",
                                i2c_conf->reg_val, i2c_conf->reg, i2c_conf->dev);
        }
        else
        {
            Serial.println("OK");
        }

    }
    else
    {
        // Serial.printf("Device 0x%02X: read register 0x%02X\n",
        //                                    i2c_conf->dev, i2c_conf->reg);
        if ( I2Cdev::readBytes(i2c_conf->dev, i2c_conf->reg,
                                                1, &i2c_conf->reg_val, 0) != 1 )
        {
            Serial.printf("FAIL reading register %02X from device %02X\n",
                                                i2c_conf->reg, i2c_conf->dev);
        }
        else
        {
            Serial.printf("%02X\n", i2c_conf->reg_val);
        }
    }
}


I2Cmon::I2Cmon()
{
  // class constructor here
}

void I2Cmon::begin(const char *prompt)
{
    I2CmonPprompt = prompt;
    Serial.print(I2CmonPprompt);
}

/**
 * Get a line from the input stream and process it.
 *
 * This function doesn't suspend waiting for the input line completion.
 *
 * @return true if input line complete and precessed,
 *         false otherwise
 */
bool I2Cmon::process()
{
    char *inLine;

    // The readline function doesn't wait for the input line completion.
    // It returns nullptr if the input line is not complete.
    inLine = readline();
    if (inLine == nullptr)
    {
        return false;
    }
    if (strlen(inLine) > 0)
    {
        // Serial.printf("Received: %s\n", inLine);
        if (cmd_parse(inLine, &i2c_cmd_data))
        {
            cmd_exec(&i2c_cmd_data);
        }
    }
    Serial.print(I2CmonPprompt);
    return true;
}
