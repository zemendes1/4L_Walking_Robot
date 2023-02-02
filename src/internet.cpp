#include <Arduino.h>
#include <EEPROM.h>
#include <RP2040_PWM.h>
#include <WiFi.h>

#include "internet.h"


//const char* ssid = "C:Virus.exe";
//const char* password = "Donald1Trump2";
//const char* ssid = "MEO-F44E90";
//const char* password = "de6ee7ea05";
const char* ssid = "iPhone de Diogo";
const char* password = "obodamorreu";
//const char* ssid = "Acabou";
//const char* password = "nova1234";

// Set web server port number to 80
WiFiServer server(80);
 
// Variable to store the HTTP request
String header;

String Name ="";
String text ="";
String submit ="";

// Decode HTTP GET value
String valueString = String(5);
int pos1 = 0;
int pos2 = 0;
int AnguloDefinido=0;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

bool move_forward_bool = false;
String move_forward_state = "off";

bool obstacle_bool = false;
String obstacle_state = "off";

bool climb_bool = false;
String climb_state = "off";

bool turn_bool = false;
String turn_state = "off";




void conecta_wifi(){
  // Start Serial Monitor

 
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
 
            // Switch the FORWARD on and off
            if (header.indexOf("GET /led/on") >= 0) {
              Serial.println("Forward ON");
              move_forward_state = "on";
              move_forward_bool = true;
            } else if (header.indexOf("GET /led/off") >= 0) {
              Serial.println("Forward OFF");
              move_forward_state = "off";
              move_forward_bool = false;
            }

            // Switch the OBSTACLE on and off
            if (header.indexOf("GET /teste/on") >= 0) {
              Serial.println("OBSTACLE ON");
              obstacle_state = "on";
              obstacle_bool = true;
            } else if (header.indexOf("GET /teste/off") >= 0) {
              Serial.println("OBSTACLE OFF");
              obstacle_state = "off";
              obstacle_bool = false;
            }

            // Switch the CLIMB on and off
            if (header.indexOf("GET /climb/on") >= 0) {
              Serial.println("CLIMB ON");
              climb_state = "on";
              climb_bool = true;
            } else if (header.indexOf("GET /climb/off") >= 0) {
              Serial.println("CLIMB OFF");
              climb_state = "off";
              climb_bool = false;
            }

             // Switch the CLIMB on and off
            if (header.indexOf("GET /turn/on") >= 0) {
              Serial.println("TURN ON");
              turn_state = "on";
              turn_bool = true;
            } else if (header.indexOf("GET /turn/off") >= 0) {
              Serial.println("TURN OFF");
              turn_state = "off";
              turn_bool = false;
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
       
            // CSS - Modify as desired
            client.println("<style>body { text-align: center; font-family: \"Trebuchet MS\", Arial; margin-left:auto; margin-right:auto; }");
            client.println(".slider { -webkit-appearance: none; width: 300px; height: 25px; border-radius: 10px; background: #ffffff; outline: none;  opacity: 0.7;-webkit-transition: .2s;  transition: opacity .2s;}");
            client.println(".slider::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 35px; height: 35px; border-radius: 50%; background: #ff3410; cursor: pointer; }</style>");
 
            // Web Page Heading
            client.println("<body><h1>Bem Vindo ao Controlador Via Internet.</h1>");
 
            // Display current state, and ON/OFF buttons for Onboard LED
            client.println("<p>Move Forward is " + move_forward_state + "</p>");
            
            // Set buttons
            if (move_forward_state == "off") {
              //picoLEDState is off, display the ON button
              client.println("<p><a href=\"/led/on\"><button class=\"button\">ON</button></a></p>");
            } else {
 
              //picoLEDState is on, display the OFF button
              client.println("<p><a href=\"/led/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for Onboard LED
            client.println("<p>Obstacle Turn Right is " + obstacle_state + "</p>");

            if (obstacle_state == "off") {
              //picoLEDState is off, display the ON button
              client.println("<p><a href=\"/teste/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              //picoLEDState is on, display the OFF button
              client.println("<p><a href=\"/teste/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for Onboard LED
            client.println("<p>Climb is " + climb_state + "</p>");

            if (climb_state == "off") {
              //picoLEDState is off, display the ON button
              client.println("<p><a href=\"/climb/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              //picoLEDState is on, display the OFF button
              client.println("<p><a href=\"/climb/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Get JQuery
            client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");
                     
            // Page title
            client.println("</head><body style=\"background-color:#3857f2;\"><h1 style=\"color:#f7e00a;\">Definir Angulo a Virar</h1>");
            
            // Position display
            client.println("<h2 style=\"color:#ffffff;\">Position: <span id=\"servoPos\"></span>&#176;</h2>"); 

            // Display current state, and ON/OFF buttons for Onboard LED
            client.println("<p>Turn is " + turn_state + "</p>");

            if (turn_state == "off") {
              //picoLEDState is off, display the ON button
              client.println("<p><a href=\"/turn/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              //picoLEDState is on, display the OFF button
              client.println("<p><a href=\"/turn/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            
                     
            // Slider control
            client.println("<input type=\"range\" min=\"-360\" max=\"360\" class=\"slider\" id=\"servoSlider\" onchange=\"servo(this.value)\" value=\""+valueString+"\"/>");
            
            // Javascript
            client.println("<script>var slider = document.getElementById(\"servoSlider\");");
            client.println("var servoP = document.getElementById(\"servoPos\"); servoP.innerHTML = slider.value;");
            client.println("slider.oninput = function() { slider.value = this.value; servoP.innerHTML = this.value; }");
            client.println("$.ajaxSetup({timeout:1000}); function servo(pos) { ");
            client.println("$.get(\"/?value=\" + pos + \"&\"); {Connection: close};}</script>");

            client.println("</body></html>");

            // GET data
            if(header.indexOf("GET /?value=")>=0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              
              // String with motor position
              valueString = header.substring(pos1+1, pos2);
              
              // Move servo into position
              AnguloDefinido=valueString.toInt();

            }    

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
