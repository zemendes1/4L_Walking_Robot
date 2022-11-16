#include <Arduino.h>
#include <EEPROM.h>
#include <RP2040_PWM.h>


#define MOTOR 3

RP2040_PWM* PWM_Instance;


void setup() {
  // put your setup code here, to run once:
  
  PWM_Instance = new RP2040_PWM(MOTOR,100,26);

}

void loop() {
  // put your main code here, to run repeatedly:

    PWM_Instance -> setPWM(MOTOR,100,4);
    Serial.print("aa");
    delay(1000);

    PWM_Instance -> setPWM(MOTOR,100,26);
    delay(1000);
    
}
