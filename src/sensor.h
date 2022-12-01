#ifndef _SENSOR_H
#define _SENSOR_H
/****/
#include <Arduino.h>
// defines pins numbers
#define trigPin 27 
#define echoPin 28


extern long duration;
extern int distance;

void ultrasom_setup();
void ultrasom_loop();

#endif