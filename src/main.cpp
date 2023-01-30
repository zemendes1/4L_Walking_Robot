#include <Arduino.h>
#include <EEPROM.h>
#include <RP2040_PWM.h>
#include <WiFi.h>

#include "internet.h"
#include "sensor.h"

//  -----               -----
// |  8  |   -------   |  7  |
// |     |  |HC_SR04|  |     |
//  ----- -----   ----- -----
//       |  4  | |  3  |
//       |     | |     |
//        -----   -----
//       |  2  | |  1  |
//       |     | |     |
//  ----- -----   ----- -----
// |  6  |             |  5  |
// |     |             |     |
//  -----               -----  (Top View)

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

#define _90graus_Motor5 23.2
#define _180graus_Motor5 7.5

#define _0graus_Motor6 37
#define _90graus_Motor6 21.7

#define _0graus_Motor7 39
#define _90graus_Motor7 24.7

#define _90graus_Motor8 21.8
#define _180graus_Motor8 7.7

RP2040_PWM *PWM_Instance_1A;
RP2040_PWM *PWM_Instance_1B;
RP2040_PWM *PWM_Instance_6A;
RP2040_PWM *PWM_Instance_6B;
RP2040_PWM *PWM_Instance_7A;
RP2040_PWM *PWM_Instance_7B;
RP2040_PWM *PWM_Instance_0A;
RP2040_PWM *PWM_Instance_0B;

sensors_event_t aceleracao_previa;
float pitchangle_previo=0.00000f;


void servo_angle(int angle, int motor);
void recebe_angulos(int angulo1, int angulo2, int angulo3, int angulo4, int angulo5, int angulo6, int angulo7, int angulo8, int delayms);
void calibra();void obstacle_turn_right();void move_forward_no_sensor();


void move_forward();
void move_backwards();
void move_left();
void move_right();
void turn_left();
void turn_right();
void liedown();
void standup();
void turn_angulo_definido(int angulo_requerido);
void climbing();

/*
typedef struct {
  int state, new_state;
  // tes - time entering state
  // tis - time in state
  unsigned long tes, tis;
} fsm_t;

// Our finite state machines
fsm_t fsm1, fsm2;

// Input variables
uint8_t S1, prevS1;
uint8_t S2, prevS2;

unsigned long S1_time , S2_time;


unsigned long interval, last_cycle;
unsigned long loop_micros;


// Set new state
void set_state(fsm_t& fsm, int new_state)
{
  if (fsm.state != new_state) {  // if the state chnanged tis is reset
    fsm.state = new_state;
    fsm.tes = millis();
    fsm.tis = 0;
  }
}*/


float m1= 0.000f,m2= 0.000f,m3= 0.000f,m4= 0.000f,m5= 0.000f,m6= 0.000f,m7= 0.000f,m8= 0.000f;
float b1= 0.000f,b2= 0.000f,b3= 0.000f,b4= 0.000f,b5= 0.000f,b6= 0.000f,b7= 0.000f,b8= 0.000f;
int stop_distance=0, move_forward_is_on=0, iteracao =0;

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

  Serial.begin(9600); // Starts the serial communication

  /*interval = 10;
  set_state(fsm1, 0);*/

  //conecta_wifi();
  //sonar_setup();
  imu_setup();
  //stop_distance=15;
}

void loop()
{   
  //sonar_loop();
  //conexao_html();
  //imu_loop();

  //standup();
  //liedown();
  //move_forward_no_sensor();
  //move_right();
  //turn_left();
  //turn_right();
  //obstacle_turn_right();
  climbing();
  
  
  /*
  if (move_forward_bool) {move_forward_no_sensor();}
  else if (obstacle_bool) {obstacle_turn_right();}
  //else if (obstacle_bool) {não implementado}
  else if(turn_bool){
    turn_angulo_definido(AnguloDefinido);
    turn_bool=false;
  }
  */

 
 

}

void obstacle_turn_right()
{ 
  sonar_loop();
  if(distance_sonar<stop_distance){
    move_right();
  }
  else{
    move_forward();
  }
}

void servo_angle(int angle, int motor)
{ 
  if(motor==1 || motor==4 || motor==5 || motor==8){
    if(angle < 75 || angle > 195){
      return;
    }
  }
  if(motor==2 || motor==3 || motor==6 || motor==7){
    if(angle < -15 || angle > 105){
      return;
    }
  }

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
  if(move_forward_is_on && distance_sonar < stop_distance){
    return;
  }
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

void move_forward_no_sensor()
{
  recebe_angulos(191,45,-11,135,173,28,6,152,100);
  recebe_angulos(191,45,66,135,173,28,63,152,100);
  recebe_angulos(135,66,45,191,152,63,28,174,100);
  recebe_angulos(135,-11,45,191,152,6,28,174,100);
  recebe_angulos(135,-11,45,114,152,6,28,116,100);
  recebe_angulos(114,45,-11,135,116,28,6,152,100);
  recebe_angulos(191,45,-11,135,173,28,6,152,100);
}

void move_forward()
{
  move_forward_is_on=1;
  recebe_angulos(191,45,-11,135,173,28,6,152,100);
  recebe_angulos(191,45,66,135,173,28,63,152,100);
  recebe_angulos(135,66,45,191,152,63,28,174,100);
  recebe_angulos(135,-11,45,191,152,6,28,174,100);
  recebe_angulos(135,-11,45,114,152,6,28,116,100);
  recebe_angulos(114,45,-11,135,116,28,6,152,100);
  recebe_angulos(191,45,-11,135,173,28,6,152,100);
  move_forward_is_on=0;
}

void move_backwards(){
  recebe_angulos(135,-11,45,191,152,6,28,173,100);
  recebe_angulos(135,66,45,191,152,63,28,173,100);
  recebe_angulos(191,45,66,135,174,28,63,152,100);
  recebe_angulos(191,45,-11,135,174,28,6,152,100);
  recebe_angulos(114,45,-11,135,116,28,6,152,100);
  recebe_angulos(135,-11,45,114,152,6,28,116,100);
  recebe_angulos(135,-11,45,191,152,6,28,173,100);
  
}

void move_right(){

  recebe_angulos(80,100,45,135,180,0,20,170,100);
  recebe_angulos(155,100,45,135,135,0,20,170,100);
  recebe_angulos(135,45,100,155,170,20,0,135,100);
  recebe_angulos(135,45,100,80,170,20,0,180,100);
  recebe_angulos(135,45,25,80,170,20,45,180,100);
  recebe_angulos(80,25,45,135,180,45,0,135,100);
  recebe_angulos(80,100,45,135,180,0,0,135,100);  

}

void turn_left(){

  recebe_angulos(90,0,0,90,160,20,20,160,100);

  recebe_angulos(90,0,0,90,140,20,20,140,100);    //perna 1 e 4 up
  recebe_angulos(135,0,0,135,140,20,20,140,100);    //perna 1 e 4 vira
  recebe_angulos(135,0,0,135,160,20,20,160,100);    //perna1 e 4 down
 
  recebe_angulos(135,0,0,135,160,40,40,160,100);    //perna 2 e 3 up
  recebe_angulos(135,45,45,135,160,40,40,160,100);    //perna 2 e 3 vira
  recebe_angulos(135,45,45,135,160,20,20,160,100);    //perna 2 e 3 down
 
  recebe_angulos(90,0,0,90,160,20,20,160,100);
 
 
}

void turn_right(){

  recebe_angulos(180,90,90,180,160,20,20,160,100);
  recebe_angulos(180,90,90,180,140,20,20,140,100);    //perna 1 e 4 up
  recebe_angulos(135,90,90,135,140,20,20,140,100);    //perna 1 e 4 vira
  recebe_angulos(135,90,90,135,160,20,20,160,100);    //perna1 e 4 down
  recebe_angulos(135,90,90,135,160,40,40,160,100);    //perna 2 e 3 up
  recebe_angulos(135,45,45,135,160,40,40,160,100);    //perna 2 e 3 vira
  recebe_angulos(135,45,45,135,160,20,20,160,100);    //perna 2 e 3 down
  recebe_angulos(180,90,90,180,160,20,20,160,100);
 

}


void climbing()
{
  int angulo_climbing=90;
  if(iteracao==0){
    recebe_angulos(191,45,-11,135,173,28,6,152,100);
    delay(100);
    imu_loop();
    delay(500);
    recebe_angulos(191,45,-11,135,173,28,90,152,100);
    delay(100);
    imu_loop();
    delay(500);
    recebe_angulos(191,45,66,135,173,28,90,152,100);
    delay(100);
    imu_loop();
    delay(500);
  }

  else{
    recebe_angulos(191,90,-11,135,173,28,6,152,100);
    delay(100);
    imu_loop();
    delay(500);
    recebe_angulos(191,90,-11,135,173,28,90,152,100);
    delay(100);
    imu_loop();
    delay(500);
    recebe_angulos(191,90,66,135,173,28,90,152,100);
    delay(100);
    imu_loop();
    delay(500);

  }
  if(iteracao==0){
    while(1){
      angulo_climbing=angulo_climbing-3;
      recebe_angulos(191,45,66,135,173,28,angulo_climbing,152,100);
      delay(100);
      pitchangle_previo=pitchangle;
      imu_loop();
      if(angulo_climbing<=0){
        angulo_climbing=28;
        break;
      }
      else if(pitchangle_previo+0.0005>=pitchangle && pitchangle_previo-0.0005<=pitchangle){
        break;
      }

      Serial.println();
      Serial.println(pitchangle);
      Serial.println(pitchangle_previo);
      Serial.println("angulo_climbing");
      Serial.println();


    }
  }
  else{
    angulo_climbing=0;
  }

  if(iteracao==0){

    delay(500);
    recebe_angulos(135,66,45,191,152,63,angulo_climbing,174,100);
    delay(500);
    recebe_angulos(135,66,45,191,152,90,angulo_climbing,174,100);
    delay(500);
    recebe_angulos(135,-11,45,191,152,90,angulo_climbing,174,100);
    delay(500);
    recebe_angulos(135,-11,45,191,152,6,angulo_climbing,174,100);
    delay(500);
    recebe_angulos(135,-11,45,191,152,6,angulo_climbing,90,100);
    delay(500);
    recebe_angulos(135,-11,45,114,152,6,angulo_climbing,90,100);
    delay(500);
    recebe_angulos(135,-11,45,114,152,6,6,180,100);
    delay(500);

    
    recebe_angulos(114,90,40,135,116,28,6,180,100);
    delay(500);
    recebe_angulos(114,90,40,135,90,28,6,180,100);
    delay(500);
    recebe_angulos(191,90,40,135,90,28,6,180,100);
    delay(500);
    iteracao++;
  }
  else if (iteracao ==1){
    delay(500);
    recebe_angulos(135,66,45,191,152,63,angulo_climbing,174,100);
    delay(500);
    recebe_angulos(135,66,45,191,152,90,angulo_climbing,174,100);
    delay(500);
    recebe_angulos(135,45,45,191,152,90,angulo_climbing,174,100);
    delay(500);
    recebe_angulos(135,45,45,191,152,6,angulo_climbing,174,100);
    delay(500);
    recebe_angulos(135,45,45,191,152,6,angulo_climbing,90,100);
    delay(500);
    recebe_angulos(135,45,45,114,152,6,angulo_climbing,90,100);
    delay(500);
    recebe_angulos(135,45,45,114,152,6,6,180,100);
    delay(500);
    recebe_angulos(114,66,40,135,116,28,6,180,100);
    delay(500);
    recebe_angulos(114,66,40,135,90,28,6,180,100);
    delay(500);
    recebe_angulos(191,66,40,135,90,28,6,180,100);
    delay(500);
    iteracao++;
    
    
  }
  else if (iteracao ==2){
    delay(500);
    recebe_angulos(135,66,45,191,152,63,angulo_climbing,174,100);
    delay(500);
    recebe_angulos(135,66,45,191,152,90,angulo_climbing,174,100);
    delay(500);
    recebe_angulos(135,-11,45,191,152,90,angulo_climbing,174,100);
    delay(500);
    recebe_angulos(135,-11,45,191,152,6,angulo_climbing,174,100);
    delay(500);
    recebe_angulos(135,-11,45,191,152,6,angulo_climbing,90,100);
    delay(500);
    recebe_angulos(135,-11,45,114,152,6,angulo_climbing,90,100);
    delay(500);
    recebe_angulos(135,-11,45,114,152,6,6,180,100);
    delay(500);
    recebe_angulos(114,66,-11,135,116,28,6,180,100);
    delay(500);
    recebe_angulos(114,66,-11,135,90,28,6,180,100);
    delay(500);
    recebe_angulos(191,66,-11,135,90,28,6,180,100);
    delay(500);
    iteracao++;
    
    
  }
  recebe_angulos(191,45,40,135,173,28,6,180,100);
  delay(500);
  
 
}

void turn_angulo_definido(int angulo_requerido){
  
  
  int servo_angle = angulo_requerido*2;
  uint num_90_degree_turns=0;
  
  if(servo_angle>0){
    while(servo_angle>90){
      servo_angle = servo_angle-90;
      num_90_degree_turns++;

    }
  }

  else if(servo_angle<0){
    while(servo_angle<-90){
      servo_angle = servo_angle+90;
      num_90_degree_turns++;

    }
  }
    

  if(servo_angle>0){

    for(int i=0; i<num_90_degree_turns;i++){

      recebe_angulos(180,90,90,180,160,20,20,160,100);
      recebe_angulos(180,90,90,180,140,20,20,140,100);    //perna 1 e 4 up
      recebe_angulos(90,90,90,90,140,20,20,140,100);    //perna 1 e 4 vira
      recebe_angulos(90,90,90,90,160,20,20,160,100);    //perna1 e 4 down
      recebe_angulos(90,90,90,90,160,40,40,160,100);    //perna 2 e 3 up
      recebe_angulos(90,0,0,90,160,40,40,160,100);    //perna 2 e 3 vira
      recebe_angulos(90,0,0,90,160,20,20,160,100);    //perna 2 e 3 down
    }
    
    recebe_angulos(180,90,90,180,160,20,20,160,100);
    recebe_angulos(180,90,90,180,140,20,20,140,100);    //perna 1 e 4 up
    recebe_angulos(180-servo_angle,90,90,180-servo_angle,140,20,20,140,100);    //perna 1 e 4 vira
    recebe_angulos(180-servo_angle,90,90,180-servo_angle,160,20,20,160,100);    //perna1 e 4 down
    recebe_angulos(180-servo_angle,90,90,180-servo_angle,160,40,40,160,100);    //perna 2 e 3 up
    recebe_angulos(180-servo_angle,90-servo_angle,90-servo_angle,180-servo_angle,160,40,40,160,100);    //perna 2 e 3 vira
    recebe_angulos(180-servo_angle,90-servo_angle,90-servo_angle,180-servo_angle,160,20,20,160,100);    //perna 2 e 3 down
    recebe_angulos(180,90,90,180,160,20,20,160,100);
  }

  else if(servo_angle<0){

    for(int i=0;i<num_90_degree_turns;i++){

      recebe_angulos(90,0,0,90,160,20,20,160,100);
      recebe_angulos(90,0,0,90,140,20,20,140,100);    //perna 1 e 4 up
      recebe_angulos(180,0,0,180,140,20,20,140,100);    //perna 1 e 4 vira
      recebe_angulos(180,0,0,180,160,20,20,160,100);    //perna1 e 4 down
      recebe_angulos(180,0,0,180,160,40,40,160,100);    //perna 2 e 3 up
      recebe_angulos(180,90,90,180,160,40,40,160,100);    //perna 2 e 3 vira
      recebe_angulos(180,90,90,180,160,20,20,160,100);    //perna 2 e 3 down
    }
      
    
    recebe_angulos(90,0,0,90,160,20,20,160,100);
    recebe_angulos(90,0,0,90,140,20,20,140,100);    //perna 1 e 4 up
    recebe_angulos(90-servo_angle,0,0,90-servo_angle,140,20,20,140,100);    //perna 1 e 4 vira
    recebe_angulos(90-servo_angle,0,0,90-servo_angle,160,20,20,160,100);    //perna1 e 4 down
    recebe_angulos(90-servo_angle,0,0,90-servo_angle,160,40,40,160,100);    //perna 2 e 3 up
    recebe_angulos(90-servo_angle,-servo_angle,-servo_angle,90-servo_angle,160,40,40,160,100);    //perna 2 e 3 vira
    recebe_angulos(90-servo_angle,-servo_angle,-servo_angle,90-servo_angle,160,20,20,160,100);    //perna 2 e 3 down  
    recebe_angulos(90,0,0,90,160,20,20,160,100);

  }

}




void liedown(){
  recebe_angulos(180,0,0,180,90,90,90,90,100);
}

void standup(){
  recebe_angulos(90,90,90,90,180,0,0,180,100);
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
