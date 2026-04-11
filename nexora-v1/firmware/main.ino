#include <Matter.h>
#include <MatterDevice.h>
#include <WiFiManager.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include <Preferences.h>

#define LED_PIN       2     // Builtin LED indikator
#define RELAY_PIN     23    // Relay dipindah ke GPIO 23
#define SWITCH_PIN    4     // Tombol fisik

MatterDevice light_device;
Preferences prefs;

bool relayState = false;

// Anti Bounce Variables
bool lastButtonState = HIGH;
bool currentButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

// WiFi Reconnect Timer
unsigned long lastWifiCheck = 0;

void saveState(bool state) {
  prefs.begin("relay", false);
  prefs.putBool("state", state);
  prefs.end();
}

bool loadState() {
  prefs.begin("relay", true);
  bool state = prefs.getBool("state", false);
  prefs.end();
  return state;
}

void setRelay(bool state) {
  relayState = state;

  digitalWrite(RELAY_PIN, state ? HIGH : LOW);
  digitalWrite(LED_PIN, state ? HIGH : LOW);

  saveState(state);

  Serial.println(state ? "Relay ON" : "Relay OFF");
}

void setupOTA() {
  ArduinoOTA.setHostname("Mochi-SmartSwitch");

  ArduinoOTA.onStart([]() {
    Serial.println("OTA Start");
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("\nOTA End");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("OTA Progress: %u%%\r", (progress * 100) / total);
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("OTA Error[%u]\n", error);
  });

  ArduinoOTA.begin();
}

void connectWiFi() {
  WiFiManager wm;

  bool res = wm.autoConnect("Mochi-Smart-Switch");

  if (!res) {
    Serial.println("WiFi gagal, restart...");
    ESP.restart();
  }

  Serial.println("WiFi Connected!");
}

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  relayState = loadState();
  setRelay(relayState);

  connectWiFi();

  setupOTA();

  // Start Matter
  Matter.begin();

  light_device.begin(MatterDevice::ON_OFF_LIGHT, "Lampu Mochi");

  // QR / Pairing Info
  Serial.println("===== MATTER PAIRING READY =====");
  Serial.println("Scan QR pairing dari serial monitor/library Matter kamu");

  // Callback dari App/Home Assistant/Google Home
  light_device.onChange([](bool state) {
    setRelay(state);
  });
}

void loop() {

  // OTA Handler
  ArduinoOTA.handle();

  // Matter Loop (kalau library butuh)
  Matter.loop();

  // WiFi Auto Reconnect
  if (millis() - lastWifiCheck > 10000) {
    lastWifiCheck = millis();

    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi Disconnect! Reconnecting...");
      WiFi.reconnect();
    }
  }

  // Anti Bounce Button
  bool reading = digitalRead(SWITCH_PIN);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {

    if (reading != currentButtonState) {
      currentButtonState = reading;

      if (currentButtonState == LOW) {

        relayState = !relayState;

        setRelay(relayState);

        // Sync ke Matter App
        light_device.setState(relayState);
      }
    }
  }

  lastButtonState = reading;
}
