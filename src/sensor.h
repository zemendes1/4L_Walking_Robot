#ifndef _SENSOR_H
#define _SENSOR_H
/****/
#include <Arduino.h>
#include <Wire.h>

#include <HCSR04.h>
#include <MPU6050.h>

// Ultrasom
#define triggerPin 27 
#define echoPin 28

//MPU
#define sda_imu 4
#define scl_imu 5

extern float distance_sonar;
extern float distance_tof, prev_distance_tof;

void sonar_setup();
void sonar_loop();

void imu_setup();
void imu_loop();
void imu_checkSettings();

#endif