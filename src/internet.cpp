#include <Arduino.h>
#include <EEPROM.h>
#include <RP2040_PWM.h>
#include <WiFi.h>

#include "internet.h"


//const char* ssid = "C:Virus.exe";
//const char* password = "Donald1Trump2";
const char* ssid = "MEO-F44E90";
const char* password = "de6ee7ea05";


// Set web server port number to 80
WiFiServer server(80);
 
// Variable to store the HTTP request
String header;

String Name ="";
String text ="";
String submit ="";

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
              Serial.println("Forward ON");
              move_forward_state = "on";
              move_forward_bool = true;
            } else if (header.indexOf("GET /led/off") >= 0) {
              Serial.println("Forward OFF");
              move_forward_state = "off";
              move_forward_bool = false;
            }

            // Switch the LED on and off
            if (header.indexOf("GET /teste/on") >= 0) {
              Serial.println("OBSTACLE ON");
              obstacle_state = "on";
              obstacle_bool = true;
            } else if (header.indexOf("GET /teste/off") >= 0) {
              Serial.println("OBSTACLE OFF");
              obstacle_state = "off";
              obstacle_bool = false;
            }

            // Switch the LED on and off
            if (header.indexOf("GET /climb/on") >= 0) {
              Serial.println("CLIMB ON");
              climb_state = "on";
              climb_bool = true;
            } else if (header.indexOf("GET /climb/off") >= 0) {
              Serial.println("CLIMB OFF");
              climb_state = "off";
              climb_bool = false;
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
            
            client.println("<label for=\"testname\">Ângulo Pretendido:</label><br>");
            client.println("<input type=\"text\" id=\"fname\" name=\"fname\" value=\"\"><br>");
            client.println("<input type=\"submit\" value=\"Submit\">");

            if (true){
              Serial.println( header.indexOf("GET /fname"));
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
