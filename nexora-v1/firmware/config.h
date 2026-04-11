#ifndef CONFIG_H
#define CONFIG_H

// =======================
// PIN CONFIGURATION
// =======================
#define LED_PIN        2
#define RELAY_PIN      23
#define SWITCH_PIN     4

// =======================
// DEVICE INFO
// =======================
#define DEVICE_NAME        "Nexora Smart Switch"
#define DEVICE_MODEL       "Kapaksitor Nexora V1"
#define DEVICE_ID          "kapaksitor-nexora-v1"
#define FIRMWARE_VERSION   "1.0.0"

// =======================
// NETWORK
// =======================
#define WIFI_AP_NAME       "Nexora-Setup"
#define OTA_HOSTNAME       "nexora-switch"

// =======================
// TIMING
// =======================
#define DEBOUNCE_DELAY     50
#define WIFI_CHECK_INTERVAL 10000

#endif
