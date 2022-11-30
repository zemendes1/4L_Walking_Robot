#include <Arduino.h>
#include <EEPROM.h>
#include <RP2040_PWM.h>
#include <WiFi.h>

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
void conexao_html();
void conecta_wifi();


float m1= 0.000f,m2= 0.000f,m3= 0.000f,m4= 0.000f,m5= 0.000f,m6= 0.000f,m7= 0.000f,m8= 0.000f;
float b1= 0.000f,b2= 0.000f,b3= 0.000f,b4= 0.000f,b5= 0.000f,b6= 0.000f,b7= 0.000f,b8= 0.000f;




const char* ssid = "MEO-F44E90";
const char* password = "de6ee7ea05";




// Set web server port number to 80
WiFiServer server(80);
 
// Variable to store the HTTP request
String header;
 
// Variable to store onboard LED state
String picoLEDState = "off";
 
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;




void setup()
{
  // put your setup code here, to run once:
  calibra();

  /*PWM_Instance_1A = new RP2040_PWM(MOTOR_1, Freq, _180graus_Motor1);
  PWM_Instance_1B = new RP2040_PWM(MOTOR_2, Freq, _90graus_Motor2);

  PWM_Instance_6A = new RP2040_PWM(MOTOR_3, Freq, _90graus_Motor3);
  PWM_Instance_6B = new RP2040_PWM(MOTOR_4, Freq, _180graus_Motor4);

  PWM_Instance_7A = new RP2040_PWM(MOTOR_5, Freq, _90graus_Motor5);
  PWM_Instance_7B = new RP2040_PWM(MOTOR_6, Freq, _90graus_Motor6);

  PWM_Instance_0A = new RP2040_PWM(MOTOR_7, Freq, _90graus_Motor7);
  PWM_Instance_0B = new RP2040_PWM(MOTOR_8, Freq, _90graus_Motor8);*/

  conecta_wifi();
  
}

void loop()
{   
  //standup();
  //standby();
  //move_forward();
  //dancing();
  //liedown();
  //recebe_angulos(180,0,-10,180,180,0,0,180,1000);

  //PWM_Instance_1A->setPWM(MOTOR_1, Freq, 20.3);

  conexao_html();
  
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
recebe_angulos(80,25,45,135,180,45,0,45,100);
recebe_angulos(80,100,45,135,180,0,0,45,100);*/

//codigo de casa
recebe_angulos(80,100,45,135,180,0,20,170,300);
recebe_angulos(155,100,45,135,135,0,20,170,300);
recebe_angulos(135,45,100,155,170,20,0,135,300);
recebe_angulos(135,45,100,80,170,20,0,180,300);
recebe_angulos(135,45,25,80,170,20,45,180,300);
recebe_angulos(80,25,45,135,180,45,20,170,300);
recebe_angulos(80,100,45,135,180,0,20,170,300);


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

void conexao_html (){

  WiFiClient client = server.available();   // Listen for incoming clients
 
  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
 
            // Switch the LED on and off
            if (header.indexOf("GET /led/on") >= 0) {
              Serial.println("LED on");
              picoLEDState = "on";
              digitalWrite(6, HIGH);
            } else if (header.indexOf("GET /led/off") >= 0) {
              Serial.println("LED off");
              picoLEDState = "off";
              digitalWrite(6, LOW);
            }
 
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
 
            // CSS to style the on/off buttons
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #F23A3A;}</style></head>");
 
            // Web Page Heading
            client.println("<body><h1>Pico W LED Control</h1>");
 
            // Display current state, and ON/OFF buttons for Onboard LED
            client.println("<p>Onboard LED is " + picoLEDState + "</p>");
            
            // Set buttons
            if (picoLEDState == "off") {
              
              //picoLEDState is off, display the ON button
              client.println("<p><a href=\"/led/on\"><button class=\"button\">ON</button></a></p>");
            } else {
 
              //picoLEDState is on, display the OFF button
              client.println("<p><a href=\"/led/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
 
            client.println("</body></html>");
 
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }

}

void conecta_wifi(){
    // Start Serial Monitor
  Serial.begin(115200);
 
  // Initialize the LED as an output
  pinMode(6, OUTPUT);
 
  // Set LED off
  digitalWrite(6, LOW);
 
  // Connect to Wi-Fi network with SSID and password
  WiFi.begin(ssid, password);
 
  // Display progress on Serial monitor
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  // Print local IP address and start web server
  Serial.println("");
  Serial.print("WiFi connected at IP Address ");
  Serial.println(WiFi.localIP());
 
  // Start Server
  server.begin();
}