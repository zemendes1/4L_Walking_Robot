#include <Arduino.h>
#include <EEPROM.h>
#include <RP2040_PWM.h>


#define MOTOR 3

RP2040_PWM* PWM_Instance;


void setup() {
  // put your setup code here, to run once:
  
  PWM_Instance = new RP2040_PWM(MOTOR,150,36);

}

void loop() {
  // put your main code here, to run repeatedly:

    PWM_Instance -> setPWM(MOTOR,150,6);
    //Serial.print("aa");
    delay(1000);

    PWM_Instance -> setPWM(MOTOR,150,36);
    delay(1000);
    
}


int servo_angle(int angle, int servo){
  int value=0;
  value=0,1667*angle+6;  
  if(servo=1){return 0;}
  return 0;
} 
