#include <Arduino.h>
#include <EEPROM.h>
#include <RP2040_PWM.h>
#include <WiFi.h>

#include "internet.h"
#include "sensor.h"

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

#define _90graus_Motor1 20.3
#define _180graus_Motor1 35.2

#define _0graus_Motor2 19.667
#define _90graus_Motor2 35.1667

#define _0graus_Motor3 19
#define _90graus_Motor3 34.333

#define _90graus_Motor4 21.333
#define _180graus_Motor4 36

//motores 5 a 8

#define _90graus_Motor5 24.8
#define _180graus_Motor5 9.5

#define _0graus_Motor6 37
#define _90graus_Motor6 21.7

#define _0graus_Motor7 37.5
#define _90graus_Motor7 22.4

#define _90graus_Motor8 25.3
#define _180graus_Motor8 10

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
void calibra();

// Por fazer
void move_forward();
void move_backwards();
void move_left();
void move_right();
void turn_left();
void turn_right();
void standby();
void liedown();
void standup();
void dancing();


float m1= 0.000f,m2= 0.000f,m3= 0.000f,m4= 0.000f,m5= 0.000f,m6= 0.000f,m7= 0.000f,m8= 0.000f;
float b1= 0.000f,b2= 0.000f,b3= 0.000f,b4= 0.000f,b5= 0.000f,b6= 0.000f,b7= 0.000f,b8= 0.000f;



void setup()
{
  // put your setup code here, to run once:
  calibra();

  PWM_Instance_1A = new RP2040_PWM(MOTOR_1, Freq, _90graus_Motor1);
  PWM_Instance_1B = new RP2040_PWM(MOTOR_2, Freq, _90graus_Motor2);

  PWM_Instance_6A = new RP2040_PWM(MOTOR_3, Freq, _90graus_Motor3);
  PWM_Instance_6B = new RP2040_PWM(MOTOR_4, Freq, _90graus_Motor4);

  PWM_Instance_7A = new RP2040_PWM(MOTOR_5, Freq, _180graus_Motor5);
  PWM_Instance_7B = new RP2040_PWM(MOTOR_6, Freq, _0graus_Motor6);

  PWM_Instance_0A = new RP2040_PWM(MOTOR_7, Freq, _0graus_Motor7);
  PWM_Instance_0B = new RP2040_PWM(MOTOR_8, Freq, _180graus_Motor8);

  //conecta_wifi();
  //ultrasom_setup();

  delay(5000);
  
}

void loop()
{   
  //standup();
  //standby();
  move_forward();
  //dancing();
  //liedown();
  
  //PWM_Instance_1A->setPWM(MOTOR_1, Freq, 20.3);

  //conexao_html();
  //ultrasom_loop();

}

void servo_angle(int angle, int motor)
{ /*
  if(motor==1 || motor==4 || motor==5 || motor==8){
    if(angle < 80 || angle > 180){
      return;
    }
  }
  if(motor==2 || motor==3 || motor==6 || motor==7){
    if(angle < 0 || angle > 100){
      return;
    }
  }*/
  float value = 0.000f;

  if (motor == 1)
  {
    value = m1 * angle + b1; // formato y=mx+b 
    PWM_Instance_1A->setPWM(MOTOR_1, Freq, value);
  }

  else if (motor == 2)
  {
    value = m2 * angle + b2;
    PWM_Instance_1B->setPWM(MOTOR_2, Freq, value);
  }

  else if (motor == 3)
  {
    value = m3 * angle + b3;
    PWM_Instance_6A->setPWM(MOTOR_3, Freq, value);
  }

  else if (motor == 4)
  {
    value = m4 * angle + b4;
    PWM_Instance_6B->setPWM(MOTOR_4, Freq, value);
  }

  else if (motor == 5)
  {
    value = m5 * angle + b5; // formato y=mx+b 
    PWM_Instance_7A->setPWM(MOTOR_5, Freq, value);
  }

  else if (motor == 6)
  {
    value = m6 * angle + b6;
    PWM_Instance_7B->setPWM(MOTOR_6, Freq, value);
  }

  else if (motor == 7)
  {
    value = m7 * angle + b7;
    PWM_Instance_0A->setPWM(MOTOR_7, Freq, value);
  }

  else if (motor == 8)
  {
    value = m8 * angle + b8; 
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

/*
//codigo que funcionou na aula
recebe_angulos(80,100,45,135,180,0,20,170,100);
recebe_angulos(155,100,45,135,135,0,20,170,100);
recebe_angulos(135,45,100,155,170,20,0,135,100);
recebe_angulos(135,45,100,80,170,20,0,180,100);
recebe_angulos(135,45,25,80,170,20,45,180,100);
recebe_angulos(80,25,45,135,180,45,0,135,100);
recebe_angulos(80,100,45,135,180,0,0,135,100);

//codigo de casa
recebe_angulos(80,100,45,135,180,0,20,170,100);
recebe_angulos(155,100,45,135,135,0,20,170,100);
recebe_angulos(135,45,100,155,170,20,0,135,100);
recebe_angulos(135,45,100,80,170,20,0,180,100);
recebe_angulos(135,45,25,80,170,20,45,180,100);
recebe_angulos(80,25,45,135,180,45,20,170,100);
recebe_angulos(80,100,45,135,180,0,20,170,100);
*/

recebe_angulos(135,-11,45,191,152,6,28,173,100);
recebe_angulos(135,66,45,191,152,63,28,173,100);
recebe_angulos(191,45,66,135,174,28,63,152,100);
recebe_angulos(191,45,-11,135,174,28,6,152,100);
recebe_angulos(114,45,-11,135,116,28,6,152,100);
recebe_angulos(135,-11,45,114,152,6,28,116,100);
recebe_angulos(135,-11,45,191,152,6,28,173,100);






}

void standby(){

}

void liedown(){
  
}

void standup(){
  
}

void dancing(){
 

}

void calibra()
{
  m1 = (_180graus_Motor1 - _90graus_Motor1);
  m1 = m1 / (180 - 90); // calcula declive
  b1 = _90graus_Motor1 - (90*m1);  

  m2 = (_0graus_Motor2 - _90graus_Motor2);
  m2 = m2/ (0 - 90);
  b2 = _0graus_Motor2;
  
  m3 = (_0graus_Motor3 - _90graus_Motor3);
  m3 = m3 / (0 - 90);
  b3 = _0graus_Motor3;
  
  m4 = (_180graus_Motor4 - _90graus_Motor4);
  m4 = m4 / (180 - 90); 
  b4 = _90graus_Motor4 - (90*m4);  
  
  m5 = (_180graus_Motor5 - _90graus_Motor5);
  m5 = m5 / (180 - 90); 
  b5 = _90graus_Motor5 - (90*m5);  
  
  m6 = (_0graus_Motor6 - _90graus_Motor6);
  m6 = m6 / (0 - 90);
  b6 = _0graus_Motor6;
  
  m7 = (_0graus_Motor7 - _90graus_Motor7);
  m7 = m7 / (0 - 90);
  b7 = _0graus_Motor7;
  
  m8 = (_180graus_Motor8 - _90graus_Motor8);
  m8 = m8 / (180 - 90); 
  b8 = _90graus_Motor8 - (90*m8);  
  
}
