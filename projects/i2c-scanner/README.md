i2c-scanner
===========

*Conform the original [Arduino Playground](http://playground.arduino.cc/Main/I2cScanner#)
sketch to the PlatformIO IDE.*

`i2c-scanner` is a simple application to scan the I2C-bus for devices.
If a device is found, it is reported to the serial monitor.

GY-91 Multi-Sensor Module example
---------------------------------
The slave addresses of any of the sensors on the GY-91 module are 7 bits long.

The LSB bit of the 7 bit address is determined by the logic level on `SA0` pin.

If the `SA0` pin is **set to logic level 0** (unconnected or grounded),
the GY-91 sensors addresses found are listed by `i2c-scanner` as:

```
Scanning...
I2C device found at address 0x0C  !
I2C device found at address 0x68  !
I2C device found at address 0x76  !
done
```
That is:

Device           | Address
---------------- | ------
AK8963           | 0x0C
MPU-6500         | 0x68
BMP280           | 0x76

The **AK8963** magnetometer is available by means of the MPU-6500
auxiliary I2C Bus Pass-Through mode, and it is directly accessible by the host.
In this configuration the slave address for the AK8963 is always **0x0C**
and doesn't depend on the logic level on `SA0` pin.

On the other hand, if the `SA0` pin is **set to logic level 1** (3.3 V),
the GY-91 sensors addresses found are:
```
Scanning...
I2C device found at address 0x69  !
I2C device found at address 0x77  !
done
```
As expected, the LSB bits of the MPU-6500 and BMP280 addresses changed to 1.

**Note that the AK8963 sensor is no longer listed.**
