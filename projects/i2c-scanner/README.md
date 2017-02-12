i2c-scanner
===========

*Conform the original [Arduino Playground](http://playground.arduino.cc/Main/I2cScanner#) sketch to the PlatformIO IDE.*

`i2c-scanner` is a simple application to scan the I2C-bus for devices. If a device is found, it is reported to the serial monitor.

It should return for the 10DOF Acceleration Gyroscope Compass Nine Shaft Sensor breakout board `GY-91`:

```
Scanning...
I2C device found at address 0x0C  !
I2C device found at address 0x68  !
I2C device found at address 0x76  !
done
```
That is:

Device                                          | Address
----------------------------------------------- | ------
MPU9250 3-axis magnetic field                   | 0x0C
MPU9250 3-axis gyroscope + 3-axis accelerometer | 0x68
BMP280 pressure                                 | 0x76
