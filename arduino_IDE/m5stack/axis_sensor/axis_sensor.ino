
#include <Wire.h>
#include "MMA7660.h"
#include <M5Stack.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

MMA7660 accelemeter;

char *ssid = "esp32_ap";
char *password = "";
const char *endpoint1 = "192.168.4.5";
const char *endpoint2 = "192.168.4.10";

// const int port = 1883;
// char *pubTopic = "axis";
// char *subTopic = "axis";
char *axis_data = "";

int led = 18;
float az_old = 0;

IPAddress ip(192, 168, 4, 111);
IPAddress gateway(192,168, 4, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress DNS(192, 168, 4, 1);
WiFiClient netClient;
PubSubClient MqttClient;


void setup_network() {

    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.config(ip, gateway, subnet, DNS);
    WiFi.begin(ssid, password);
    delay(2000);

    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        delay(2000);
        WiFi.begin(ssid, password);
        Serial.println(".");
    }
    Serial.println("WiFi Connected.");
    Serial.println(WiFi.localIP()); 

}

void connect() {
  
    setup_network();

    MqttClient.setClient(netClient);

    Serial.println("ThingName: ESP32");
    Serial.println("before....");
    MqttClient.setServer(endpoint1, 1883);
    MqttClient.connect("axisaa");
    Serial.println("After....");
    
    while ( !MqttClient.connected() ) {
        Serial.println("MQTT : Re connect...");
        MqttClient.setServer(endpoint2, 1883);
        MqttClient.connect("axis1");
        delay(2000);
        MqttClient.setServer(endpoint1, 1883);
        MqttClient.connect("axis1");
        delay(2000);
    }
    
}

void reconnect() {
    Serial.println("ThingName: ESP32");
    Serial.println("before....");
    MqttClient.setServer(endpoint1, 1883);
    MqttClient.connect("axis");
    Serial.println("After....");
    // MqttClient.setClient(netClient);
    
    while ( !MqttClient.connected() ) {
        Serial.println("MQTT : Re connect...");
        MqttClient.setServer(endpoint2, 1883);
        MqttClient.connect("axis");
        delay(2000);
        MqttClient.setServer(endpoint1, 1883);
        MqttClient.connect("axis1");
        delay(2000);
    }
}

void setup()
{
  pinMode(led, OUTPUT);
  
  Serial.begin(115200);
  accelemeter.init();

  connect();
}



void loop() {

  float ax, ay, az;

  accelemeter.getAcceleration(&ax, &ay, &az);

  Serial.println(az_old);
 
  
//    Serial.print(ax);
  char aax[10];
  char aay[10];
  char aaz[10];
  char pubchar[100];

  dtostrf(ax,0,1,aax);
  dtostrf(ay,0,1,aay);
  dtostrf(az, 0, 1, aaz);
  sprintf(pubchar, "{\"x\":%s,\"y\":%s,\"z\":%s}", aax, aay, aaz);
//  Serial.println(pubchar);
  
  MqttClient.publish("axis", pubchar);
  MqttClient.loop();

  if ( az_old != 0 && 0.3 < abs((abs(az) - abs(az_old))) ) {
    digitalWrite(led, HIGH);
    delay(5000);
    digitalWrite(led, LOW);
    az_old = 0;
  }
  else {
    az_old = az;
  }

  if (!MqttClient.connected()) {
    reconnect();
  }

  delay(300);
}
