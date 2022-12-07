#ifndef _SENSOR_H
#define _SENSOR_H
/****/
#include <Arduino.h>
#include "pico/cyw43_arch.h"
#include <Wire.h>
#include <VL53L0X.h>

// defines pins numbers
#define trigPin 27 
#define echoPin 28


extern long duration;
extern float distance_sonar;

extern VL53L0X tof;
extern float distance_tof, prev_distance_tof;

void sonar_setup();
void sonar_loop();
void tof_setup();
void tof_loop();

#endif