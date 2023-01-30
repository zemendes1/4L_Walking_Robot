#ifndef _SENSOR_H
#define _SENSOR_H
/****/
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <HCSR04.h>


// Ultrasom
#define triggerPin 27 
#define echoPin 28

extern float distance_sonar;
extern float rollangle, pitchangle;

void sonar_setup();
void sonar_loop();

void imu_setup();
void imu_loop();

float filter(float newAngle, float newRate,int looptime);


#endif