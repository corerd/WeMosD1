/*
 * MPU-9250 and Arduino (9-Axis IMU)
 * http://www.lucidarme.me/?p=5057
 */

#include "Arduino.h"
#include "LedCtrl.h"
#include <Wire.h>

/*
 * 10DOF - GY-91 4-in-1 MPU-9250 and BMP280 Multi-Sensor Module
 * Specifications: http://artofcircuits.com/product/10dof-gy-91-4-in-1-mpu-9250-and-bmp280-multi-sensor-module
 *
 * Pinouts
 *  1. VIN: Voltage Supply Pin
 *  2. 3V3: 3.3v Regulator output
 *  3. GND: 0V Power Supply
 *  4. SCL: I2C Clock / SPI Clock
 *  5. SDA: I2C Data or SPI Data Input
 *  6. SDO/SAO: SPI Data output / I2C Slave Address configuration pin
 *  7. NCS: Chip Select for SPI mode only for MPU-9250
 *  8. CSB: Chip Select for BMP280
 *
 *  I2C Addressing
 *  The slave address of the MPU-9250 is b110100X which is 7 bits long.
 *  The LSB bit of the 7 bit address is determined by the logic level on pin SA0.
 *
 *  Auxiliary I2C Bus Pass-Through mode is used to access the AK8963 magnetometer directly from the host.
 *  In this configuration the slave address for the AK8963 is always 0x0C
 *  and deesn't depend on the logic level on pin SA0.
 */

// Set the logic level on pin SA0
#define    MPU9250_SA0                0
//#define    MPU9250_SA0                1

#define    MPU9250_ADDRESS            (0x68+MPU9250_SA0)
#define    MAG_ADDRESS                0x0C
#define    BMP280_ADDRESS             (0x76+MPU9250_SA0)

#define    GYRO_FULL_SCALE_250_DPS    0x00
#define    GYRO_FULL_SCALE_500_DPS    0x08
#define    GYRO_FULL_SCALE_1000_DPS   0x10
#define    GYRO_FULL_SCALE_2000_DPS   0x18

#define    ACC_FULL_SCALE_2_G        0x00
#define    ACC_FULL_SCALE_4_G        0x08
#define    ACC_FULL_SCALE_8_G        0x10
#define    ACC_FULL_SCALE_16_G       0x18


// built in led
LedCtrl ledBlue;
LedCtrl ledRed(LED_CUSTOM);

// Incoming serial data
int inByte = -1;

// Initial time
long int ti;

// Counter
long int cpt=0;


// This function read Nbytes bytes from I2C device at address Address.
// Put read bytes starting at register Register in the Data array.
void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();

  // Read Nbytes
  Wire.requestFrom(Address, Nbytes);
  uint8_t index=0;
  while (Wire.available())
    Data[index++]=Wire.read();
}


// Write a byte (Data) in device (Address) at register (Register)
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}


// Initializations
void setup()
{
  // Arduino initializations
  Wire.begin();
  Serial.begin(115200);

  // Set accelerometers low pass filter at 5Hz
  I2CwriteByte(MPU9250_ADDRESS,29,0x06);
  // Set gyroscope low pass filter at 5Hz
  I2CwriteByte(MPU9250_ADDRESS,26,0x06);

  // Configure gyroscope range
  I2CwriteByte(MPU9250_ADDRESS,27,GYRO_FULL_SCALE_1000_DPS);
  // Configure accelerometers range
  I2CwriteByte(MPU9250_ADDRESS,28,ACC_FULL_SCALE_4_G);
  // Set by pass mode for the magnetometers
  I2CwriteByte(MPU9250_ADDRESS,0x37,0x02);

  // Request continuous magnetometer measurements in 16 bits
  I2CwriteByte(MAG_ADDRESS,0x0A,0x16);


  // Store initial time
  ti=millis();
}


// Main loop, read and display data
void loop()
{
  delay(100);  // wait 1/2 seconds for next scan
  ledBlue.toggle();

  if (!Serial.available())
    return;
  while (Serial.available()) { // If data is available to read,
   inByte = Serial.read(); // read it and store it in val
  }
  ledRed.toggle();

  // Display time
  Serial.print (millis()-ti,DEC);
  Serial.print (";");


  // _______________
  // ::: Counter :::

  // Display data counter
  //Serial.print (cpt++,DEC);
  //Serial.print ("\t");


  // ____________________________________
  // :::  accelerometer and gyroscope :::

  // Read accelerometer and gyroscope
  uint8_t Buf[14];
  I2Cread(MPU9250_ADDRESS,0x3B,14,Buf);

  // Create 16 bits values from 8 bits data

  // Accelerometer
  int16_t ax=-(Buf[0]<<8 | Buf[1]);
  int16_t ay=-(Buf[2]<<8 | Buf[3]);
  int16_t az=Buf[4]<<8 | Buf[5];

  // Gyroscope
  int16_t gx=-(Buf[8]<<8 | Buf[9]);
  int16_t gy=-(Buf[10]<<8 | Buf[11]);
  int16_t gz=Buf[12]<<8 | Buf[13];

    // Display values

  // Accelerometer
  Serial.print (ax,DEC);
  Serial.print (";");
  Serial.print (ay,DEC);
  Serial.print (";");
  Serial.print (az,DEC);
  Serial.print (";");

  // Gyroscope
  Serial.print (gx,DEC);
  Serial.print (";");
  Serial.print (gy,DEC);
  Serial.print (";");
  Serial.print (gz,DEC);
  Serial.print (";");


  // _____________________
  // :::  Magnetometer :::


  // Read register Status 1 and wait for the DRDY: Data Ready

  uint8_t ST1;
  do
  {
    I2Cread(MAG_ADDRESS,0x02,1,&ST1);
  }
  while (!(ST1&0x01));

  // Read magnetometer data
  uint8_t Mag[7];
  I2Cread(MAG_ADDRESS,0x03,7,Mag);


  // Create 16 bits values from 8 bits data

  // Magnetometer
  int16_t mx=-(Mag[3]<<8 | Mag[2]);
  int16_t my=-(Mag[1]<<8 | Mag[0]);
  int16_t mz=-(Mag[5]<<8 | Mag[4]);


  // Magnetometer
  Serial.print (mx+200,DEC);
  Serial.print (";");
  Serial.print (my-70,DEC);
  Serial.print (";");
  Serial.print (mz-700,DEC);
  Serial.print (";");



  // End of line
  Serial.println("");
//  delay(100);
}
