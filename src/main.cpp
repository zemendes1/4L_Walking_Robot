#include <Arduino.h>
#include <EEPROM.h>
#include <RP2040_PWM.h>


#define MOTOR_1 2
#define MOTOR_2 3

RP2040_PWM* PWM_Instance;
RP2040_PWM* PWM_Instance1;

void setup() {
  // put your setup code here, to run once:
  
  PWM_Instance = new RP2040_PWM(MOTOR_1,50,10);
  PWM_Instance1 = new RP2040_PWM(MOTOR_2,50,10);
 

}

void loop() {
  // put your main code here, to run repeatedly:
    
    if (PWM_Instance){
      PWM_Instance1-> setPWM(MOTOR_2,50,10);
      PWM_Instance -> setPWM(MOTOR_1,50,10);
    }
    delay(1000);
    PWM_Instance1 -> setPWM(MOTOR_2, 50, 5);
    PWM_Instance -> setPWM(MOTOR_1,50,10);
    delay(1000);
    
}
