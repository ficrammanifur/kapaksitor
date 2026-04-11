#include <Matter.h>
#include <MatterDevice.h>
#include <WiFiManager.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include <Preferences.h>

#include "config.h"

// =======================
// OBJECTS
// =======================
MatterDevice light_device;
Preferences prefs;

// =======================
// VARIABLES
// =======================
bool relayState = false;

bool lastButtonState = HIGH;
bool currentButtonState = HIGH;
unsigned long lastDebounceTime = 0;

unsigned long lastWifiCheck = 0;

// =======================
// SAVE STATE
// =======================
void saveState(bool state) {
  prefs.begin("relay", false);
  prefs.putBool("state", state);
  prefs.end();
}

// =======================
// LOAD STATE
// =======================
bool loadState() {
  prefs.begin("relay", true);
  bool state = prefs.getBool("state", false);
  prefs.end();
  return state;
}

// =======================
// SET RELAY
// =======================
void setRelay(bool state) {
  relayState = state;

  digitalWrite(RELAY_PIN, state ? HIGH : LOW);
  digitalWrite(LED_PIN, state ? HIGH : LOW);

  saveState(state);

  Serial.println(state ? "Relay ON" : "Relay OFF");
}

// =======================
// OTA
// =======================
void setupOTA() {
  ArduinoOTA.setHostname(OTA_HOSTNAME);

  ArduinoOTA.begin();
}

// =======================
// WIFI
// =======================
void connectWiFi() {
  WiFiManager wm;

  bool res = wm.autoConnect(WIFI_AP_NAME);

  if (!res) {
    Serial.println("WiFi gagal, restart...");
    ESP.restart();
  }

  Serial.println("WiFi Connected!");
}

// =======================
// SETUP
// =======================
void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  relayState = loadState();
  setRelay(relayState);

  connectWiFi();
  setupOTA();

  // Matter Start
  Matter.begin();
  light_device.begin(MatterDevice::ON_OFF_LIGHT, DEVICE_NAME);

  Serial.println("===== NEXORA READY =====");
  Serial.print("Device: "); Serial.println(DEVICE_NAME);
  Serial.print("Firmware: "); Serial.println(FIRMWARE_VERSION);

  // Callback dari Matter
  light_device.onChange([](bool state) {
    setRelay(state);
  });
}

// =======================
// LOOP
// =======================
void loop() {

  ArduinoOTA.handle();
  Matter.loop();

  // WiFi Reconnect
  if (millis() - lastWifiCheck > WIFI_CHECK_INTERVAL) {
    lastWifiCheck = millis();

    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi reconnect...");
      WiFi.reconnect();
    }
  }

  // BUTTON
  bool reading = digitalRead(SWITCH_PIN);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {

    if (reading != currentButtonState) {
      currentButtonState = reading;

      if (currentButtonState == LOW) {

        relayState = !relayState;

        setRelay(relayState);

        // Sync ke Matter
        light_device.setState(relayState);
      }
    }
  }

  lastButtonState = reading;
}
