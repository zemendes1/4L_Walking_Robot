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
extern sensors_event_t a, g, temp;
extern float rollangle, pitchangle;

void sonar_setup();
void sonar_loop();

void imu_setup();
void imu_loop();

void filter_setup();
void filter_loop();


#endif