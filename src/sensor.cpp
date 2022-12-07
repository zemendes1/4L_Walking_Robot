#include <Arduino.h>
#include "sensor.h"

#include "pico/cyw43_arch.h"
#include <Wire.h>
#include <VL53L0X.h>

long duration;
float distance_sonar=0.000f;

float distance_tof, prev_distance_tof;
VL53L0X tof;

void sonar_setup() {
  
  // defines variables
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

}

void sonar_loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance in cm
  distance_sonar = duration * 0.034 / 2;

  /* Debug distance
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);*/
}



void tof_setup() {
 
  Wire.setSDA(8);//GPIO8
  Wire.setSCL(9);//GPIO9

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
    distance_tof = tof.readRangeMillimeters() * 1e-3;

     
    // Start new distance measure
    tof.startReadRangeMillimeters(); 

    //Debug distance_tof
    Serial.print(" Dist: ");
    Serial.print(distance_tof, 3);
    Serial.println(); 
    delay(1000); 
  }

    
}

