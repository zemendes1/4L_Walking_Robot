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

//motores 1 a 4

#define _90graus_Motor1 20.5
#define _180graus_Motor1 35.167

#define _0graus_Motor2 19.667
#define _90graus_Motor2 35.1667

#define _0graus_Motor3 19
#define _90graus_Motor3 34.333

#define _90graus_Motor4 21.333
#define _180graus_Motor4 36

//motores 5 a 8

#define _90graus_Motor5 9.5
#define _180graus_Motor5 24.8

#define _0graus_Motor6 21.7
#define _90graus_Motor6 37

#define _0graus_Motor7 22.4
#define _90graus_Motor7 37.5

#define _90graus_Motor8 10
#define _180graus_Motor8 25.3

RP2040_PWM *PWM_Instance_1A;
RP2040_PWM *PWM_Instance_1B;
RP2040_PWM *PWM_Instance_6A;
RP2040_PWM *PWM_Instance_6B;
RP2040_PWM *PWM_Instance_7A;
RP2040_PWM *PWM_Instance_7B;
RP2040_PWM *PWM_Instance_0A;
RP2040_PWM *PWM_Instance_0B;

void servo_angle(int angle, int motor);
void recebe_angulos(int angulo1, int angulo2, int angulo3, int angulo4, int angulo5, int angulo6, int angulo7, int angulo8, int delayms);
void move_forward();// por faser
void move_backwards();
void move_left();
void move_right();
void turn_left();
void turn_right();
void standby();
void liedown();
void standup();
void dancing();

void setup()
{
  // put your setup code here, to run once:

  PWM_Instance_1A = new RP2040_PWM(MOTOR_1, Freq, _90graus_Motor1);
  PWM_Instance_1B = new RP2040_PWM(MOTOR_2, Freq, _90graus_Motor2);

  PWM_Instance_6A = new RP2040_PWM(MOTOR_3, Freq, _90graus_Motor3);
  PWM_Instance_6B = new RP2040_PWM(MOTOR_4, Freq, _90graus_Motor4);

  PWM_Instance_7A = new RP2040_PWM(MOTOR_5, Freq, _180graus_Motor5);
  PWM_Instance_7B = new RP2040_PWM(MOTOR_6, Freq, _0graus_Motor6);

  PWM_Instance_0A = new RP2040_PWM(MOTOR_7, Freq, _0graus_Motor7);
  PWM_Instance_0B = new RP2040_PWM(MOTOR_8, Freq, _180graus_Motor8);
}

void loop()
{   
  //standup();
  //standby();
  move_forward();
  //dancing();
  //liedown();

  
}

void servo_angle(int angle, int motor)
{
  

  float m = 0.000f, b = 0.000f;
  float value = 0.000f;

  if (motor == 1)
  { // Cada if faz uma regressão linear mediante os parametros definidos em cima
    m = (_180graus_Motor1 - _90graus_Motor1);
    m = m / (180 - 90); // calcula declive
    b = _90graus_Motor1 - (90*m);  
    value = m * angle + b; // formato y=mx+b 
    PWM_Instance_1A->setPWM(MOTOR_1, Freq, value);
  }

  else if (motor == 2)
  {
    m = (_0graus_Motor2 - _90graus_Motor2);
    m = m / (0 - 90);
    b = _0graus_Motor2;
    value = m * angle + b;
    PWM_Instance_1B->setPWM(MOTOR_2, Freq, value);
  }

  else if (motor == 3)
  {
    m = (_0graus_Motor3 - _90graus_Motor3);
    m = m / (0 - 90);
    b = _0graus_Motor3;
    value = m * angle + b;
    PWM_Instance_6A->setPWM(MOTOR_3, Freq, value);
  }

  else if (motor == 4)
  {
    m = (_180graus_Motor4 - _90graus_Motor4);
    m = m / (180 - 90); // calcula declive
    b = _90graus_Motor4 - (90*m);  
    value = m * angle + b;
    PWM_Instance_6B->setPWM(MOTOR_4, Freq, value);
  }

  else if (motor == 5)
  {
    m = (_180graus_Motor5 - _90graus_Motor5);
    m = m / (180 - 90); // calcula declive
    b = _90graus_Motor5 - (90*m);  
    value = m * angle + b; // formato y=mx+b 
    PWM_Instance_7A->setPWM(MOTOR_5, Freq, value);
  }

  else if (motor == 6)
  {
    m = (_0graus_Motor6 - _90graus_Motor6);
    m = m / (0 - 90);
    b = _0graus_Motor6;
    value = m * angle + b;
    PWM_Instance_7B->setPWM(MOTOR_6, Freq, value);
  }

  else if (motor == 7)
  {
    m = (_0graus_Motor7 - _90graus_Motor7);
    m = m / (0 - 90);
    b = _0graus_Motor7;
    value = m * angle + b;
    PWM_Instance_0A->setPWM(MOTOR_7, Freq, value);
  }

  else if (motor == 8)
  {
    m = (_180graus_Motor8 - _90graus_Motor8);
    m = m / (180 - 90); // calcula declive
    b = _90graus_Motor8 - (90*m);  
    value = m * angle + b; // formato y=mx+b 
    PWM_Instance_0B->setPWM(MOTOR_8, Freq, value);
  }
}

void recebe_angulos(int angulo1, int angulo2, int angulo3, int angulo4, int angulo5, int angulo6, int angulo7, int angulo8, int delayms)
{

  servo_angle(angulo1, 1);
  servo_angle(angulo2, 2);
  servo_angle(angulo3, 3);
  servo_angle(angulo4, 4);
  servo_angle(angulo5, 5);
  servo_angle(angulo6, 6);
  servo_angle(angulo7, 7);
  servo_angle(angulo8, 8);

  delay(delayms);
}

void move_forward()
{
  recebe_angulos(90,90,90,90,110,70,70,110,100); // standby, ; 
  recebe_angulos(90,90,45,90,110,90,90,110,100); // leg1, 4 up;  leg4 fw
  recebe_angulos(90,90,45,90,110,70,70,110,100); // leg1, 4 dn; 
  recebe_angulos(90,90,45,90,90,70,70,90,100); // leg2, 3 up; 
  recebe_angulos(90,45,90,135,90,70,70,90,100); // leg1, 4 bk;  leg2 fw
  recebe_angulos(90,45,90,135,110,70,70,110,100); // leg2, 3 dn; 
  recebe_angulos(90,90,90,135,110,90,90,110,100); // leg1, 4 up;  leg1 fw
  recebe_angulos(135,90,90,90,110,90,90,110,100); // leg2, 3 bk; 
  recebe_angulos(135,90,90,90,110,70,70,110,100); // leg1, 4 dn; 
  recebe_angulos(135,90,90,90,90,70,70,110,100); // leg3 up, ; 
  recebe_angulos(90,90,90,90,110,70,70,110,100); // leg3 fw dn, ; 
}

void standby(){

}

void liedown(){
  
}

void standup(){
  
}

void dancing(){
 

}