#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

#define CLOSE 0
#define OPEN 1

int read_sw = 18;
int is_open = 1;
int counter = 0;

char *ssid = "esp32_ap";
char *password = "";
const char *endpoint = "192.168.4.5";
const int port = 1883;
char *pubTopic = "myTopic";
char *subTopic = "myTopic";

IPAddress ip(192, 168, 4, 200);
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
    MqttClient.setServer(endpoint, 1883);
    MqttClient.setClient(netClient);
    
    while ( !MqttClient.connect("ESP32") ) {
        Serial.println(MqttClient.state());
        delay(2000);
    }
    // MqttClient.subscribe("m5stack/sub/#");
    
}

void setup()
{
  Serial.begin(115200);
  
  connect();
}

uint32_t state = 0;
/*
 * Loop Function
 */
void loop()
{
  state = digitalRead(read_sw);

  if ( state == CLOSE )
  {
    is_open = 1;
    Serial.println("Close");
  }
  else
  {
    if ( is_open == 1 )
    {
      counter++;
      Serial.println("open");
      MqttClient.publish("myTopic", "{\"no\":\"1\",\"count\":\"1\"}");
      Serial.println("Count:" + (String)counter + "  No:2");
      MqttClient.loop();

      if (!MqttClient.connect("ESP32")) {
        Serial.println(MqttClient.state());
        delay(2000);
      }
    }

    is_open = 0;
  }
  delay(100);

}
