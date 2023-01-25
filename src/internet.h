#ifndef _INTERNET_H
#define _INTERNET_H
/****/

#include <Arduino.h>
#include <EEPROM.h>
#include <RP2040_PWM.h>
#include <WiFi.h>



void conecta_wifi();
void conexao_html();


extern const char* ssid;
extern const char* password;
extern WiFiServer server;
extern String header;
extern String picoLEDState;
extern unsigned long currentTime;
extern unsigned long previousTime;
extern const long timeoutTime;
extern bool move_forward_bool; 
extern bool obstacle_bool;
extern bool climb_bool;

#endif