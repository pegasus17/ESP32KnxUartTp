#include <Arduino.h>
#include "wifi_config.h"
#include <WiFi.h>

static void connectToWiFi();
static void WiFiEvent(WiFiEvent_t event);

void setup() {
  Serial.begin(115200);
  Serial.println("Starting ..");

  connectToWiFi();
} 

void loop() {
  // put your main code here, to run repeatedly:
}

/**
 * @brief Establish connection to the network
 * 
 */
static void connectToWiFi() {
  // close existing connection if there is one
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true, true);
  delay(100);
  // register event handler
  WiFi.onEvent(WiFiEvent);

  Serial.println("ESP Board MAC Address:  " + WiFi.macAddress());

  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);
}

/**
 * @brief wifi event handler
 * 
 * @param event  [in]
 */
static void WiFiEvent(WiFiEvent_t event)
{
  switch (event)
  {
  case SYSTEM_EVENT_STA_GOT_IP:
    Serial.print("WiFi connected: RRSI=");
    Serial.print(WiFi.RSSI());
    Serial.print(", IP=");
    Serial.println(WiFi.localIP());
    break;

  case SYSTEM_EVENT_STA_DISCONNECTED:
    Serial.println("WiFi lost connection");
    break;

  default:
    break;
  }
}
