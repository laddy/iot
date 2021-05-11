#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <M5Stack.h>

#define CLOSE 0
#define OPEN 1
#define __VERSION__   "1.0.0"
#define LOOP_INTERVAL (6000)

int read_sw = 5;
int is_open = 1;
int counter = 0;

char *ssid = "NTGR-82BC";
char *password = "38925206";
const char *endpoint = "192.168.1.10";
const int port = 1883;
char *THING_NAME = "M5Stack";
char *pubTopic = "myTopick";
char *subTopic = "myTopick";


WiFiClient netClient;
PubSubClient MqttClient;



void setup_network() {

    M5.Lcd.print("Connecting WiFi");
    Serial.print("Connecting to ");
    Serial.println(ssid);
    
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("WiFi Connected.");
}

void connect() {
    setup_network();
    Serial.print("ThingName(mqtt_id): ");
    Serial.println(THING_NAME);
    MqttClient.setServer(endpoint, 1883);
    MqttClient.setClient(netClient);
    
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(20, 20); //文字表示の左上位置を設定
    M5.Lcd.setTextColor(WHITE); 
    M5.Lcd.print("Connecting mqtt");

    while ( !MqttClient.connect(THING_NAME) ) {
        Serial.println(MqttClient.state());
        delay(1000);
        M5.Lcd.print(".");
    }
    // MqttClient.subscribe("m5stack/sub/#");
    
}

void setup()
{
  Serial.begin(115200);

  // Display Setup
  M5.begin();
  M5.Lcd.setBrightness(200);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(20, 20); //文字表示の左上位置を設定
  M5.Lcd.setTextColor(WHITE); 
  
  connect();


  M5.Lcd.setBrightness(200);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(20, 20); //文字表示の左上位置を設定
  M5.Lcd.setTextColor(WHITE); 
  M5.Lcd.setTextSize(7);//文字の大きさを設定（1～7）
  M5.Lcd.print("press wait...");
}


/*
 * Loop Function
 */
void loop()
{
  int state;
  state = digitalRead(read_sw);
  //Serial.println(state);

  if ( state == CLOSE )
  {
    is_open = 0;
    //Serial.println("Close");
  }
  else
  {
    if ( is_open == 0 )
    {
      counter++;

      //char *send = counter + "\}"; 
      MqttClient.publish("myTopic", "1");
      // char send[100];
      // sprintf(send, "%s%s%s", "{count: ", (String)counter, "}");
      // MqttClient.publish("myTopic",send );
      // 文字描画
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(20, 20); //文字表示の左上位置を設定
      M5.Lcd.setTextColor(WHITE); 
      M5.Lcd.setTextSize(7);//文字の大きさを設定（1～7）
      M5.Lcd.print(counter);

      Serial.println("Count:" + (String)counter);
      MqttClient.loop();

      if (!MqttClient.connect(THING_NAME)) {
        Serial.println(MqttClient.state());
      }
    }

    is_open = 1;
  }
  delay(50);

}
