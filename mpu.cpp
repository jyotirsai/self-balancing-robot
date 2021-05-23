#include <Arduino.h> // This enables us to use the arduino library in the cpp file
#include "mpu.h"
#include <Wire.h> // for I2C communication

void mpu::init(){
    // initialize mpu parameters
    Wire.beginTransmission(0b1101000); // Start communicating with I2C address of MPU
    Wire.write(0b1101011); // Access the 0x6B power management register
    Wire.write(0b00000000); // Set all parameters in register to 0
    Wire.endTransmission();
    Wire.beginTransmission(0b1101000);
    Wire.write(0b11100); // Access the 0x1C accelerometer register
    Wire.write(0b00000000); // set all bits to 0, bit 4 and 3 are set to 0 for 2g acceleration
    Wire.endTransmission();
};

void mpu::retrieveData(){
    Wire.beginTransmission(0b1101000);
    Wire.write(0b111011); // This is the starting register for accelerometer measurements (0x3B)
    Wire.endTransmission();
    Wire.requestFrom(0b1101000, 6); // read the 6 registers
    ax_raw = (Wire.read() << 8 | Wire.read()); // bit shifting, first two bytes are stored in ax (x-component acceleration)
    ay_raw = (Wire.read() << 8 | Wire.read()); // third and fourth bytes are stored in ay (y-component acceleration)
    az_raw = (Wire.read() << 8 | Wire.read()); // fifth and sixth bytes are stored in az (z-component acceleration)
};

void mpu::processData(){
    ax_g = ax_raw / 16384;
    ay_g = ay_raw / 16384;
    az_g = az_raw / 16384;
    angleX = atan(ax_g, sqrt(pow(ay_g, 2)+pow(az_g,2)))*180/PI; // acceleration in g is converted to angles in degrees
    angleY = atan(ay_g, sqrt(pow(ax_g, 2)+pow(az_g,2)))*180/PI;
    angleZ = atan(az_g, sqrt(pow(ay_g, 2)+pow(ax_g,2)))*180/PI;
}
