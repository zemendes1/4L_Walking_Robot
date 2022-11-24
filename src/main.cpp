#include <Arduino.h>
#include <EEPROM.h>
#include <RP2040_PWM.h>

#define MOTOR_1 2
#define MOTOR_2 3
#define MOTOR_3 12
#define MOTOR_4 13
#define MOTOR_5 14
#define MOTOR_6 15
#define MOTOR_7 16
#define MOTOR_8 17


#define Freq 150
#define Ograus 6

RP2040_PWM *PWM_Instance_1A;
RP2040_PWM *PWM_Instance_1B;
RP2040_PWM *PWM_Instance_6A;
RP2040_PWM *PWM_Instance_6B;
/*RP2040_PWM *PWM_Instance_7A;
RP2040_PWM *PWM_Instance_7B;
RP2040_PWM *PWM_Instance_0A;
RP2040_PWM *PWM_Instance_0B;*/

void servo_angle(int angle, int motor);

void setup()
{
  // put your setup code here, to run once:

  PWM_Instance_1A = new RP2040_PWM(MOTOR_1, Freq, Ograus);
  PWM_Instance_1B = new RP2040_PWM(MOTOR_2, Freq, Ograus);

  PWM_Instance_6A = new RP2040_PWM(MOTOR_3, Freq, Ograus);
  PWM_Instance_6B = new RP2040_PWM(MOTOR_4, Freq, Ograus);

  /*PWM_Instance_7A = new RP2040_PWM(MOTOR_5, Freq, Ograus);
  PWM_Instance_7B = new RP2040_PWM(MOTOR_6, Freq, Ograus);

  PWM_Instance_0A = new RP2040_PWM(MOTOR_7, Freq, Ograus);
  PWM_Instance_0B = new RP2040_PWM(MOTOR_8, Freq, Ograus);*/
}

void loop()
{

  for (int i = 1; i < 5; i++)
  {
    servo_angle(5, i);
  }
  delay(1000);
  
  for (int i = 1; i < 5; i++)
  {
    servo_angle(175, i);
  }
  delay(1000);
}

void servo_angle(int angle, int motor)
{

  if(angle < 0 || angle > 180){ return; }

  float value=0;
  value = (0.16666666666666667) * angle + 6;

  if (motor == 1){
    PWM_Instance_1A->setPWM(MOTOR_1, Freq, value);}

  else if (motor == 2){
    PWM_Instance_1B->setPWM(MOTOR_2, Freq, value);}

  else if (motor == 3){
    PWM_Instance_6A->setPWM(MOTOR_3, Freq, value);}

  else if (motor == 4){
    PWM_Instance_6B->setPWM(MOTOR_4, Freq, value);}

  /*else if (motor == 5){
    PWM_Instance_7A->setPWM(MOTOR_5, Freq, value);}

  else if (motor == 6){
    PWM_Instance_7B->setPWM(MOTOR_6, Freq, value);}

  else if (motor == 7){
    PWM_Instance_0A->setPWM(MOTOR_7, Freq, value);}

  else if (motor == 8){
    PWM_Instance_0B->setPWM(MOTOR_8, Freq, value);}*/
    
}