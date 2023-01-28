#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <HCSR04.h>
#include <kalman.h>

#include "sensor.h"

KalmanFilter kf;KalmanFilter kf1;
unsigned long timer = 0;

Adafruit_MPU6050 mpu;

//Ultrasom
UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);
float distance_sonar=0.000f;
float rollangle=0.00000f, pitchangle=0.00000f;

void sonar_setup () {
  
}

void sonar_loop () {
  distance_sonar = distanceSensor.measureDistanceCm();
}


void imu_setup(void) {


  Serial.println("Adafruit MPU6050 test!");

  Wire.setSDA(8);
  Wire.setSCL(9);

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");

}

void imu_loop() {

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  //Print out the values 

  if(0){
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");

  Serial.println("");
  }
  float accelX=a.acceleration.x;
  float accelY=a.acceleration.y;
  float accelZ=a.acceleration.z;
  rollangle=atan2(accelY,accelZ)*180/PI; // FORMULA FOUND ON INTERNET
  pitchangle=atan2(accelX,sqrt(accelY*accelY+accelZ*accelZ))*180/PI; //FORMULA FOUND ON INTERNET
  
  if(Serial){
  Serial.print("Roll angle: ");Serial.println(rollangle);
  Serial.print("Pitch angle: ");Serial.println(pitchangle);
  Serial.println("");
  }

}



void filter_setup() {
  // Set initial state
  kf.set(pitchangle);
  kf.setProcessNoise(0.1, 0.01); // Position, velocity
  kf.setMeasurementNoise(1);
}

void filter_loop() {

  // Delta time : time since last prediction
  float dt = (millis()-timer)/1000.f;
  timer = millis();

  // Kalman filter steps
  kf.predict(dt);
  int x = kf.get();
  kf.correct(rollangle);

  // Kalman filter steps
  kf1.predict(dt);
  int x1 = kf1.get();
  kf1.correct(pitchangle);

  if(Serial){
  Serial.print("Roll angle Corrected: ");Serial.println(rollangle);
  Serial.print("Pitch angle Corrected: ");Serial.println(pitchangle);
  Serial.println("");
  }
}
