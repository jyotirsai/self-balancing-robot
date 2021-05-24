#include "Motor.h"
#include "mpu.h"

mpu mpu; // instantiate MPU class
Motor Motor; // instantiate Motor class

void setup() {
  // put your setup code here, to run once:
  mpu.init(); // initialize mpu
  Motor.pinInit(); // initialize motor pins
}

int output;

void loop() {
  // put your main code here, to run repeatedly:
  mpu.retrieveData(); // retrieves raw accelerometer data
  mpu.processData(); // converts raw data into angles
  output = PID(mpu.angleY); // compute pid using current angleY measurement

    
  if (mpu.angleY < 0) {
    Motor.Reverse(output);
  }

  if (mpu.angleY > 0){
    Motor.Forward(output);
  } 

}

// PID Variables
float previousTime = 0;
float prevErr = 0;
float currentTime, deltaTime, error, sumErr, dErr, pid;
float desired = 0; // desired angle is 0 degrees
float Kp = 30;
float Ki = 10;
float Kd = 1;

float PID(float measured){
   currentTime = millis();
   deltaTime = currentTime-previousTime;

   // error calcs
   error = abs(desired - measured);
   sumErr += error*deltaTime;
   dErr = (error-prevErr)/deltaTime;

   if (sumErr > 255) {
    sumErr = 255;
   }

   // pid calc
   pid = Kp*error+Ki*sumErr-Kd*dErr;

   // keep values for next iteration
   prevErr = error;
   previousTime = currentTime;

   if (pid > 255){
    pid = 255;
   }

   if (pid < 0) {
    pid = 0;
   }

   if (abs(measured) > 30){
    pid = 0;
   }

   return pid;
}
