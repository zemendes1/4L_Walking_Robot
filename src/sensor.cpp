#include <Arduino.h>
#include "sensor.h"

long duration;
float distance=0.000f;

void ultrasom_setup() {
  // defines variables
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

}

void ultrasom_loop() {
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
  distance = duration * 0.034 / 2;

  /* Debug distance
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);*/
}