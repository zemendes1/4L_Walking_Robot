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
#define Ograus_Motor1 35.167
#define Ograus_Motor2 19.667
#define Ograus_Motor3 19.333
#define Ograus_Motor4 35.833
#define Ograus_Motor5 21
#define Ograus_Motor6 21
#define Ograus_Motor7 21
#define Ograus_Motor8 21


RP2040_PWM *PWM_Instance_1A;
RP2040_PWM *PWM_Instance_1B;
RP2040_PWM *PWM_Instance_6A;
RP2040_PWM *PWM_Instance_6B;
RP2040_PWM *PWM_Instance_7A;
RP2040_PWM *PWM_Instance_7B;
RP2040_PWM *PWM_Instance_0A;
RP2040_PWM *PWM_Instance_0B;

void servo_angle(int angle, int motor);

void setup()
{
  // put your setup code here, to run once:

  PWM_Instance_1A = new RP2040_PWM(MOTOR_1, Freq, Ograus_Motor1);
  PWM_Instance_1B = new RP2040_PWM(MOTOR_2, Freq, Ograus_Motor2);

  PWM_Instance_6A = new RP2040_PWM(MOTOR_3, Freq, Ograus_Motor3);
  PWM_Instance_6B = new RP2040_PWM(MOTOR_4, Freq, Ograus_Motor4);

  PWM_Instance_7A = new RP2040_PWM(MOTOR_5, Freq, Ograus_Motor5);
  PWM_Instance_7B = new RP2040_PWM(MOTOR_6, Freq, Ograus_Motor6);

  PWM_Instance_0A = new RP2040_PWM(MOTOR_7, Freq, Ograus_Motor7);
  PWM_Instance_0B = new RP2040_PWM(MOTOR_8, Freq, Ograus_Motor8);
}

void loop()
{

  
  servo_angle(0,1);
  servo_angle(0,2);
  servo_angle(0,3);
  servo_angle(0,4);

  //para levantar o robot angulo menor
  servo_angle(0,5);
    

  //para levantar o robot angulo maior
  servo_angle(180,6);
    

  //para levantar o robot angulo maior
  servo_angle(180,7);
    

  //para levantar o robot angulo menor
  servo_angle(0,8);
    


    
  
  delay(1000);

  

  servo_angle(90,1);
  servo_angle(90,2);
  servo_angle(90,3);
  servo_angle(90,4);

  //para levantar o robot angulo menor
  servo_angle(45,5);
    

  //para levantar o robot angulo maior
  servo_angle(135,6);
  

  //para levantar o robot angulo maior
  servo_angle(135,7);
    

  //para levantar o robot angulo menor
  servo_angle(45,8);
    

  
  delay(1000);
}

void servo_angle(int angle, int motor)
{

  if(angle < 0 || angle > 180){ return; }

  float value=0;

  if (motor == 1){
    value = 0.1630 * angle + 20.50;
    PWM_Instance_1A->setPWM(MOTOR_1, Freq, value);
  }

  else if (motor == 2){
    value = 35.17 -0.1722 * angle;
    PWM_Instance_1B->setPWM(MOTOR_2, Freq, value);
  }

  else if (motor == 3){
    value = 34.33 - 0.1704 * angle;
    PWM_Instance_6A->setPWM(MOTOR_3, Freq, value);
  }

  else if (motor == 4){
    value = 0.1630 * angle + 21.33;
    PWM_Instance_6B->setPWM(MOTOR_4, Freq, value);
  }

  else if (motor == 5){
    value = (0.16666666666666667) * angle + 6;
    PWM_Instance_7A->setPWM(MOTOR_5, Freq, value);
  }

  else if (motor == 6){
    value = (0.16666666666666667) * angle + 6;
    PWM_Instance_7B->setPWM(MOTOR_6, Freq, value);
  }

  else if (motor == 7){
    value = (0.16666666666666667) * angle + 6;
    PWM_Instance_0A->setPWM(MOTOR_7, Freq, value);
  }

  else if (motor == 8){
    value = (0.16666666666666667) * angle + 6;
    PWM_Instance_0B->setPWM(MOTOR_8, Freq, value);
  }
    
}