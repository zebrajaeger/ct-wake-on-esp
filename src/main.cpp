#include <Arduino.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <FS.h>

#include "config.h"
#include "hextools.h"
#include "mqtt.h"
#include "pin.h"
#include "wifi.h"
#include "wol.h"

void setup() {
  Serial.begin(115200);
  Serial.println("===Wake-on-ESP===");
  loadConfig();

  wifiSetup();

  if (shouldSaveConfig) {
    saveConfig();
  }

  pinSetup();
  wolSetup();
  mqttSetup();
}

void loop() {
  if (action_power == 1) {
    Serial.println("action_power");
    pinToggle(POWER_PIN, 200);
    action_power = 0;
  }

  if (action_power_force == 1) {
    Serial.println("action_power_force");
    pinToggle(POWER_PIN, 5000);
    action_power_force = 0;
  }

  if (action_reset == 1) {
    Serial.println("action_reset");
    pinToggle(RESET_PIN, 200);
    action_reset = 0;
  }

  // is configuration portal requested?
  if (digitalRead(CONFIG_PIN) == LOW) {
    Serial.println("wifiSetup");
    wifiSetup(true);
  }

  if (shouldSaveConfig) {
    Serial.println("saveConfig");
    saveConfig();
  }
}
