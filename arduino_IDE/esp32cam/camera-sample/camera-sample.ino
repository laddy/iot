/********************************************************
 * Independent Access-Point - ESP32 simple example  
 *        Initial version V.00 Sept.26 2020
 *                                   by Akira Tominaga
********************************************************/
#include "WiFi.h"
const char ssid[]  = "HOGEHOGE-00X";   // *** set any ssid ***
const char pass[] = "hoge00xpw";  // *** set any pw   ***
const IPAddress ip(192, 168, 32, 2);  // *** set any addr ***
const IPAddress subnet(255, 255, 255, 0); 
WiFiServer server(80);
// ESP32 GPIO pin definitions (should not be #define)
gpio_num_t Red = GPIO_NUM_21;               // Red LED
gpio_num_t Green = GPIO_NUM_22;             // Green LED
gpio_num_t Blue = GPIO_NUM_23;              // Blue LED

void setup() { // ***** Arduino (ESP32) Setup *****
  Serial.begin(9600);
  pinMode(Red, OUTPUT);                     // Red pin as output
  digitalWrite(Red, LOW);
  pinMode(Green, OUTPUT);                   // Green pin as output
  digitalWrite(Green, LOW);
  pinMode(Blue, OUTPUT);                    // Blue pin as output
  digitalWrite(Blue, LOW);
  delay(100);

  WiFi.softAP(ssid, pass);
  delay(100);
  WiFi.softAPConfig(ip, ip, subnet);
  IPAddress myIP = WiFi.softAPIP();
  server.begin();
  Serial.print("SSID= ");
  Serial.println(ssid);
  Serial.print("Fixed IP addr= ");
  Serial.println(myIP);
  Serial.println("Server starting!");
}

void loop() { // ***** Arduino (ESP32) Loop *****
  WiFiClient client = server.available();
  if (client) {                             // if accessed
    Serial.println("Accessed");
    String inMsg = "";
    while (client.connected()) {            // loop while client connected
      if (client.available()) {             // if a message,
        char c = client.read();             // read each byte, and
        Serial.write(c);                    // write to Serial
        if (c == '\n') {                    // if  LF and
          if (inMsg.length() == 0) {        //  if new, send response
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();               // send NewLine
            client.print("-  Touch to switch LED on/off  -");
            client.print("Switch Red-on");
            client.print("Switch Green-on");
            client.print("Switch Blue-on");
            client.print("Switch Off");
            client.println();               // send another NewLine
            break;                          // go out of while loop
          } else {                          // if not new
            inMsg = "";                     // initialize inMsg
          }
        } else if (c != '\r') {             // when not (c == '\n') ,too
          inMsg += c;                       // add to inMsg
        }

        if (inMsg.endsWith("GET /R")) {
          digitalWrite(Red, HIGH);          // Red on
        }
        if (inMsg.endsWith("GET /G")) {
          digitalWrite(Green, HIGH);        // Green on
        }
        if (inMsg.endsWith("GET /B")) {
          digitalWrite(Blue, HIGH);         // Blue on
        }
        if (inMsg.endsWith("GET /F")) {
          digitalWrite(Red, LOW);           // Red off
          digitalWrite(Green, LOW);         // Green off
          digitalWrite(Blue, LOW);          // Blue off
        }
      } // end of (client.available())
    }  // end of (client.connected())
    client.stop();
    Serial.println("Client Disconnected.");
  } // end of (client)
}
// end of program
