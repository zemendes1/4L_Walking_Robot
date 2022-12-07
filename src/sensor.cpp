#include <Arduino.h>
#include "sensor.h"

//#include "pico/cyw43_arch.h"
#include <Wire.h>
#include <VL53L0X.h>
#include <HCSR04.h>

UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);
float distance_sonar=0.000f;

VL53L0X tof;
float distance_tof=0.000f, prev_distance_tof=0.000f;

void sonar_setup () {
  
}

void sonar_loop () {
  // Print the distance in centimeters
  distance_sonar = distanceSensor.measureDistanceCm();
  Serial.print("Distance_sonar: ");
  Serial.println(distance_sonar,3);
  
}



void tof_setup() {
 
  Wire.setSDA(sda_tof);//GPIO8
  Wire.setSCL(scl_tof);//GPIO9

  Wire.begin();


  tof.setTimeout(500);
  while (!tof.init()) {
    Serial.println(F("Failed to detect and initialize VL53L0X!"));
    delay(100);
  }  

  // Reduce timing budget to 20 ms (default is about 33 ms)
  tof.setMeasurementTimingBudget(20000);

  // Start new distance measure
  tof.startReadRangeMillimeters();  

}

void tof_loop() {

  if (tof.readRangeAvailable()) {
    prev_distance_tof = distance_tof;
    distance_tof = tof.readRangeMillimeters() * 0.1;

     
    // Start new distance measure
    tof.startReadRangeMillimeters(); 

    //Debug distance_tof
    Serial.print("Distance_tof: ");
    Serial.println(distance_tof, 3);

  }
 
}

