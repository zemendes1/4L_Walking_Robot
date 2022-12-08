#ifndef _SENSOR_H
#define _SENSOR_H
/****/
#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>
#include <HCSR04.h>
#include <MPU6050.h>

// Ultrasom
#define triggerPin 27 
#define echoPin 28

//TOF
#define sda_tof 8 
#define scl_tof 9

//MPU
#define sda_imu 21 
#define scl_imu 22

extern float distance_sonar;
extern float distance_tof, prev_distance_tof;

void sonar_setup();
void sonar_loop();

void tof_setup();
void tof_loop();

void imu_setup();
void imu_loop();
void imu_checkSettings();

#endif