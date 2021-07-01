#define M5STACK_MPU6886
#define MQTT_MAX_PACKET_SIZE 12048
#define RAD_TO_DEG 57.324

#include <M5Stack.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>



float gyroX, gyroY, gyroZ;

char *ssid = "esp32_ap";
char *password = "";
const char *endpoint = "192.168.4.5";
// const int port = 1883;
// char *pubTopic = "axis";
// char *subTopic = "axis";
char *axis_data = "";


IPAddress ip(192, 168, 4, 180);
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
    
    Serial.println("ThingName: ESP32");
    Serial.println("before....");
    MqttClient.setServer(endpoint, 1883);
    MqttClient.connect("axis");
    Serial.println("After....");
    // MqttClient.setClient(netClient);
    
    while ( !MqttClient.connected() ) {
        Serial.println("MQTT : Re connect...");
        MqttClient.setServer(endpoint, 1883);
        MqttClient.connect("axis1");
        delay(2000);
    }
    // MqttClient.subscribe("m5stack/sub/#");
    
}

void reconnect() {
    Serial.println("ThingName: ESP32");
    Serial.println("before....");
    MqttClient.setServer(endpoint, 1883);
    MqttClient.connect("axis");
    Serial.println("After....");
    // MqttClient.setClient(netClient);
    
    while ( !MqttClient.connected() ) {
        Serial.println("MQTT : Re connect...");
        MqttClient.setServer(endpoint, 1883);
        MqttClient.connect("axis");
        delay(2000);
    }
}

void setup()
{
  Serial.begin(115200);

  M5.begin();
  M5.Power.begin();
    
  M5.IMU.Init();
  M5.Lcd.fillScreen(WHITE);
  M5.Lcd.setTextColor(GREEN , BLACK);
  M5.Lcd.setTextSize(4);
  Serial.println("End: M5 Setup");

  connect();

  Serial.println("End: Connect");

}

void loop() {
  M5.IMU.getGyroData(&gyroX,&gyroY,&gyroZ);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("gyro=(%0.f, %0.1f, %0.1f)", gyroX, gyroY, gyroZ);
  
//  Serial.println(printf("axis_data", "{\"x\":\"%0.1f\",\"y\":\"%0.1f\",\"z\":\"%0.1f\"}", gyroX, gyroY, gyroZ));
//  sprintf(axis_data, "{\"x\":\"%0.1f\",\"y\":\"%0.1f\",\"z\":\"%0.1f\"}", gyroX, gyroY, gyroZ);
//  Serial.println(axis_data);
  // Serial.println("aaa: " + (char)gyroX);
  Serial.println("{\"x\":\""+ String(gyroX,1) +"\",\"y\":\""+ String(gyroY,1) +"\",\"z\":\""+ String(gyroZ,1) +"\"}");
  //MqttClient.publish("axis", "{\"x\":\""+ String(gyroX,1) +"\",\"y\":\""+ String(gyroY,1) +"\",\"z\":\""+ String(gyroZ,1) +"\"}");
  // MqttClient.loop();


  if (!MqttClient.connected()) {
    reconnect();
  }

  delay(500);
}
