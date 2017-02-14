10-DOF GY-91 sensor module
==========================
The GY-91 is a 10 Degree Of Freedom (DOF) sensor module.

![user input clear](https://corerd.github.io/WeMosD1/img/gy91.jpg)

The module combines the [InvenSense MPU-9250](https://www.invensense.com/products/motion-tracking/9-axis/mpu-9250/)
Inertia Measurement Unit (IMU)
together with the Bosch BMP280 barometric pressure sensor.

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
  VIN   | Voltage Supply pin
  3V3   | 3.3v Regulator output
  GND   | 0V Power Supply
  SCL   | I2C Clock / SPI Clock
  SDA   | I2C Data or SPI Data Input
SDO/SAO | SPI Data output / I2C Slave Address configuration pin
  NCS   | SPI Chip Select for MPU-9250
  CSB   | SPI Chip Select for BMP280
