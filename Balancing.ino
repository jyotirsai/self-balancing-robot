#include "Motor.h"
#include "mpu.h"

mpu mpu; // instantiate MPU class
Motor Motor; // instantiate Motor class

void setup() {
  // put your setup code here, to run once:
  mpu.init(); // initialize mpu
  Motor.pinInit(); // initialize motor pins
  
  

}

float output;

void loop() {
  // put your main code here, to run repeatedly:
  mpu.retrieveData(); // retrieves raw accelerometer data
  mpu.processData(); // converts raw data into angles
  output = PID(mpu.angleY); // compute pid using current angleY measurement

  if (output > 0){
    Motor.forward(output);
  } else if (output < 0) {
    Motor.reverse(output);
  }

}

// PID Variables
float previousTime = 0;
float prevErr = 0;
float currentTime, deltaTime, error, sumErr, dErr, pid;
float desired = 0; // desired angle is 0 degrees
float Kp = 40;
float Ki = 10;
float Kd = 5;

float PID(float measured){
   currentTime = millis();
   deltaTime = currentTime-previousTime;

   // error calcs
   error = desired - measured;
   sumErr += error*deltaTime;
   dErr = (error-prevErr)/deltaTime;

   // pid calc
   pid = Kp*error+Ki*sumErr+Kd*dErr;

   // keep values for next iteration
   prevErr = error;
   previousTime = currentTime;

   return pid;
}
