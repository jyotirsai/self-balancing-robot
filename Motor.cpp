#include <Arduino.h>
#include "Motor.h"

void Motor::pinInit(){
    // sets pin as output
    pinMode(AIN1, OUTPUT); 
    pinMode(BIN1, OUTPUT);
    pinMode(PWMA_LEFT, OUTPUT);
    pinMode(PWMB_RIGHT, OUTPUT);
    pinMode(STBY_PIN, OUTPUT);
    // sets the STBY pin on
    digitalWrite(STBY_PIN, HIGH); 
}

void Motor::Forward(int speed){
    digitalWrite(AIN1, 0); // for CCW rotation
    digitalWrite(BIN1, 0); 
    analogWrite(PWMA_LEFT, speed); // set speed of motors, betwen 0 and 255
    analogWrite(PWMB_RIGHT, speed);
}

void Motor::Reverse(int speed){
    digitalWrite(AIN1, 1); // for CW rotation
    digitalWrite(BIN1, 1);
    analogWrite(PWMA_LEFT, speed);
    analogWrite(PWMB_RIGHT, speed);
}