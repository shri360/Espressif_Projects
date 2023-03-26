#include <ESP8266WiFi.h>
#include <PubSubClient.h>

int LED = D5; //Assign LED pin
 
//Enter your wifi credentials
const char* ssid = "MQTT";  
const char* password =  "asdfghjk";

//Enter your mqtt server configurations
const char* mqttServer = "192.168.4.1";    //Enter Your mqttServer address
const int mqttPort = 1883;       //Port number
//const char* mqttUser = "asdkrtevaoq"; //User
//const char* mqttPassword = "sfCJ8Rafbzd"; //Password
 
WiFiClient espClient;
PubSubClient client(espClient);
 //void callback(char* topic, byte* payload, unsigned int length) 
//{
  
//}
void MQTTcallback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");

  String message;
  for (int i = 0; i < length; i++) {
   message = message + (char)payload[i];  //Conver *byte to String
  }
   Serial.print(message);
  if(message == "Button status: 0")
  {digitalWrite(LED,LOW);} //LED off  
  else if (message == "Button status: 1")
  {digitalWrite(LED,HIGH);} //LED on
 
  Serial.println();
  Serial.println("-----------------------");  
}
void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.print("Connected to WiFi :");
  Serial.println(WiFi.SSID());
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(MQTTcallback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

String clientId = "ESP8266Client-01";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    //if you MQTT broker has clientID,username and password
    //please change following line to    if (client.connect(clientId,userName,passWord))
    if (client.connect(clientId.c_str())){
      Serial.println("connected"); 
      client.subscribe("LED_TOGGLE"); 
 
    } else {
 
      Serial.print("failed with state ");
      Serial.println(client.state());  //If you get state 5: mismatch in configuration
      delay(2000);
 
    }
  }
 
  //client.publish("esp/test", "Hello from ESP8266");
  //client.subscribe("OsoyooData");
 
}
 
void loop() {
  client.loop();
}
