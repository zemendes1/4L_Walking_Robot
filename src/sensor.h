#ifndef _SENSOR_H
#define _SENSOR_H
/****/
#include <Arduino.h>
#include "pico/cyw43_arch.h"
#include <Wire.h>
#include <VL53L0X.h>
#include <HCSR04.h>

// defines pins numbers
#define triggerPin 27 
#define echoPin 28

#define sda_tof 8 
#define scl_tof 9

extern float distance_sonar;

extern float distance_tof, prev_distance_tof;

void sonar_setup();
void sonar_loop();
void tof_setup();
void tof_loop();

#endif