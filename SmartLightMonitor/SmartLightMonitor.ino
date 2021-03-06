#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
//-------- Customise these values -----------
const char* ssid = "YOU";
const char* password = "sbvizag2019";
//String command;
#define ORG "64s7zs"
#define DEVICE_TYPE "ASH"
#define DEVICE_ID "ash8080"
#define TOKEN "VIP12345"
//-------- Customise the above values --------
 
char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[] = "iot-2/evt/Data/fmt/json";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;
 
WiFiClient wifiClient;
PubSubClient client(server, 1883,wifiClient);

void setup() {
 Serial.begin(9600);
 Serial.println();
 Serial.print("Connecting to ");
 Serial.print(ssid);
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 } 
 Serial.println("");
 
 Serial.print("WiFi connected, IP address: ");
 Serial.println(WiFi.localIP());
}
 
void loop() {
float l = analogRead(A0);

PublishData(l);
 if (!client.loop()) {
    mqttConnect();
  }
delay(100);
}
void mqttConnect() {
  if (!client.connected()) {
    Serial.print("Reconnecting MQTT client to "); Serial.println(server);
    while (!client.connect(clientId, authMethod, token)) {
      Serial.print(".");
      delay(500);
    }
    initManagedDevice();
    Serial.println();
  }
}
void initManagedDevice() {
  if (client.subscribe(topic)) {
    Serial.println("subscribe to cmd OK");
  } else {
    Serial.println("subscribe to cmd FAILED");
  }
}

void PublishData(float light){
 if (!client.connected()) {
 Serial.print("Reconnecting client to ");
 Serial.println(server);
 while (!client.connect(clientId, authMethod, token)) {
 Serial.print(".");
 delay(500);
 }
 Serial.println();
 }
  String payload = "{\"d\":{\"Light\":";
  payload += light;
 Serial.print("Sending payload: ");
 Serial.println(payload);
 delay(500);
  
 if (client.publish(topic, (char*) payload.c_str())) {
 Serial.println("Publish ok");
 delay(100);
 } else {
 Serial.println("Publish failed");
 delay(2000);
 }
}
