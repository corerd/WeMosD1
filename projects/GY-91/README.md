10-DOF GY-91 MPU-9250 and BMP280 Multi-Sensor Module
====================================================
The [GY-91](http://artofcircuits.com/product/10dof-gy-91-4-in-1-mpu-9250-and-bmp280-multi-sensor-module)
is a 4 in 1 Multi-Sensor Module achieving 10 Degree Of Freedom (DOF).

It has Gyroscope, Accelerometer, Magnetic Compass and Pressure sensor
all on single breakout board with I2C and SPI communication interface.

![image](https://corerd.github.io/WeMosD1/img/GY-91.jpg)

The module combines the [InvenSense MPU-9250](https://www.invensense.com/products/motion-tracking/9-axis/mpu-9250/)
Inertia Measurement Unit (IMU) together with the
[Bosch BMP280](https://www.bosch-sensortec.com/bst/products/all_products/bmp280)
barometric pressure sensor.

The MPU-9250 is a System in Package (SiP) that integrates two chips:
- the **MPU-6500** which contains a 3-axis gyroscope, a 3-axis accelerometer,
  and an on-board Digital Motion Processor (DMP);
- the **AK8963**, a 3-axis digital compass.

Technical Specifications
------------------------
- Power supply: 3.0V – 5.0V (on-board low dropout regulator)
- Communication: standard IIC / SPI communications protocol
- Resolution: 16bit AD converter, 16-bit data output
- Gyroscopes range: ± 250 500 1000 2000 ° / s
- Acceleration range: ± 2 ± 4 ± 8 ± 16g
- Field range: ± 4800uT
- Pressure range: 300-1100hPa
- 2.54mm pitch
- Module size: 14.3mm * 20.5mm

Pinouts
------------------
  Pin   | Function
------- | --------
  VIN   | 3.0V - 5.0V Voltage Supply
  3V3   | 3.3v Voltage Supply bypassing the on-board LDO Regulator
  GND   | 0V Voltage Supply
  SCL   | I2C Clock / SPI Clock
  SDA   | I2C Data or SPI Data Input
SDO/SAO | SPI Data output / I2C Slave Address configuration pin
  NCS   | SPI Chip Select for MPU-9250
  CSB   | SPI Chip Select for BMP280



Connecting to the WeMos D1 Mini using I2C the interface
=======================================================

The minimal setup requires four wires to communicate with the sensors on the board.

![image](https://corerd.github.io/WeMosD1/img/GY-D1.jpg)

WeMosD1 Pin | Function                | GY-91 Pin
----------- | ----------------------- | ---------
D1          | I2C Clock               | SCL
D2          | I2C Data                | SDA
G           | Ground                  | GND
5V          | 5V                      | VIN

3.3V logic
----------
Instead of the 5V logic, it is also possible to power the GY-91 with 3.3 Volts
using the `3V3` pin which bypasses the on-board 3.3V regulator and level shifting:
- Connect the `3V3` pin on the breakout to the `3V3` supply on the WeMOsD1
- Connect `GND` on the breakout to `G` on the WeMOsD1

I2C Addressing
--------------
The slave addresses of any of the sensors on the GY-91 module are 7 bits long.

The LSB bit of the 7 bit address is determined by the logic level on `SA0` pin.

Auxiliary I2C Bus Pass-Through mode is used to access the **AK8963** magnetometer
directly from the host.
In this configuration the slave address for the AK8963 is always **0x0C**
and doesn't depend on the logic level on `SA0` pin.

Leaving the `SA0` pin unconnected (logic level 0), the sensors addresses are:

Device           | Address
---------------- | ------
AK8963           | 0x0C
MPU-6500         | 0x68
BMP280           | 0x76
