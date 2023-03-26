#include "WiFi.h"

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.print("Setting AP (Access Point)…");
  WiFi.mode(WIFI_AP_STA);  // AP + STA required because of wifi scan during AP
  const char* ssid = "ESP32_AP01";
  const char* password = "asdfghjk";
  if (!WiFi.softAP(ssid, password)) {
    Serial.println("AP Failed");
    return;
  }
  delay(2000);
  // Set static IP
  IPAddress AP_LOCAL_IP(192, 168, 1, 160);
  IPAddress AP_GATEWAY_IP(192, 168, 1, 4);
  IPAddress AP_NETWORK_MASK(255, 255, 255, 0);
  if (!WiFi.softAPConfig(AP_LOCAL_IP, AP_GATEWAY_IP, AP_NETWORK_MASK)) {
    Serial.println("AP Config Failed");
    return;
  }
  // Show the local IP
  Serial.print("AP IP address: ");
  IPAddress IP = WiFi.softAPIP();
  Serial.println(IP);
}

void loop() {
  // put your main code here, to run repeatedly:

}
