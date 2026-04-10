<h1 align="center">
⚡ Kapaksitor Nexora V1<br>
    <sub>Premium Matter-Enabled Smart Switch dengan ESP32-C3</sub>
</h1>

<p align="center">
  <img src="/assets/nexora-banner.png?height=400&width=700" alt="Kapaksitor Nexora V1" width="700"/>
</p>

<p align="center">
  <em>DIY Smart Home Module dengan AC-DC Integrated, Native Matter Protocol, ESP32-C3 Super Mini, State Memory, dan OTA-Ready untuk ekosistem Apple Home, Google Home & Alexa.</em>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/standard-Matter-7B68EE?style=for-the-badge&logo=matter&logoColor=white" />
  <img src="https://img.shields.io/badge/platform-ESP32--C3-00ADD8?style=for-the-badge&logo=espressif&logoColor=white" />
  <img src="https://img.shields.io/badge/power-220V_AC-FF0000?style=for-the-badge" />
  <img src="https://img.shields.io/badge/firmware-Arduino_Matter-00979D?style=for-the-badge&logo=arduino&logoColor=white" />
  <img src="https://img.shields.io/badge/design-Modular-FF6B6B?style=for-the-badge" />
</p>

---

## 📋 Daftar Isi
- [Mengapa Nexora V1?](#-mengapa-nexora-v1)
- [Demo & Fitur](#-demo--fitur-utama)
- [Komponen & Hardware](#-komponen--hardware)
- [Arsitektur Sistem](#-arsitektur-sistem)
- [Alur Kerja](#-alur-kerja-sistem)
- [Instalasi & Setup](#-instalasi--setup)
- [Panduan Pairing](#-panduan-pairing)
- [Skema Wiring](#-skema-wiring)
- [Troubleshooting](#-troubleshooting)
- [Struktur Proyek](#-struktur-proyek)
- [Lisensi](#-lisensi)

---

## 🚀 Mengapa Nexora V1?

### Keunggulan Nexora V1 dibanding Smart Switch Komersial
| Fitur | Smart Switch Komersial | Nexora V1 | Keuntungan |
|-------|------------------------|-----------|-----------|
| **Harga** | $30-50 | $8-12 BOM | 💰 4x lebih murah untuk DIY |
| **Protokol** | Proprietary | Native Matter | 📡 Kompatibel semua ekosistem |
| **AC-DC** | Modul terpisah | Hi-Link Integrated | 🔌 Lebih compact & reliable |
| **State Memory** | Flash (prone error) | Preferences.h | 💾 Reliabilitas state saat mati listrik |
| **OTA Update** | Berbayar | Free via WiFi | 🔄 Update fitur tanpa bongkar |
| **Customizable** | Terbatas | Full source code | 🛠️ Develop fitur custom sendiri |
| **Komunitas** | Closed | Open Source | 🤝 Library & support besar |

### Keunggulan Sistem Nexora V1
✅ **Matter Native** - Terdeteksi langsung di Apple Home, Google Home, Alexa tanpa app tambahan  
✅ **AC-DC Integrated** - Hi-Link PM01 tertanam, hemat space & cost  
✅ **State Persistent** - Status relay terjaga via Preferences.h saat mati listrik  
✅ **OTA Ready** - Update firmware jarak jauh via WiFi  
✅ **Manual Control** - Tombol fisik untuk on/off & factory reset  
✅ **Smart LED Indicator** - Status WiFi & Matter pairing via GPIO 2  
✅ **Terminal Sekrup** - Konektor kokoh untuk instalasi permanent  
✅ **Modular Design** - Casing 3D print tersedia, mudah modifikasi  

---

## 📸 Demo & Fitur Utama

<p align="center">
  <em>Nexora V1 hadir sebagai solusi pintar untuk mengotomasi beban listrik rumah dengan protokol Matter standar industri.</em>
</p>

---

<p align="center">
  <img src="/assets/nexora-demo.gif?height=400&width=700" alt="Nexora V1 Demo" width="700"/><br/>
  <em>Demo: Pairing Matter, WiFi Auto-Connect & Manual Control</em>
</p>

---

### <p align="center">✨ Fitur & State Flows</p>

<p align="center">
  <strong>State 1:</strong> Relay OFF (Beban mati)<br/>
  <strong>State 2:</strong> Relay ON (Beban hidup)<br/>
  <strong>State 3:</strong> Factory Reset (Clear WiFi & Matter data)<br/>
  <strong>State 4:</strong> OTA Update (Firmware upload)
</p>

---

### <p align="center">🖼️ Preview Hardware</p>

<p align="center">
  <img src="/assets/nexora-front.png?height=100&width=100" width="100" alt="Front View"/>&nbsp;&nbsp;
  <img src="/assets/nexora-side.png?height=100&width=100" width="100" alt="Side View"/>&nbsp;&nbsp;
  <img src="/assets/nexora-internal.png?height=100&width=100" width="100" alt="Internal"/>&nbsp;&nbsp;
  <img src="/assets/nexora-wiring.png?height=100&width=100" width="100" alt="Wiring"/><br/>
  <em>Hardware views: Front, Side, Internal PCB & Wiring</em>
</p>

---

## 🧩 Komponen & Hardware

| Komponen | Fungsi | Spesifikasi |
|----------|--------|-------------|
| **ESP32-C3 Super Mini** | Kontroler utama | Matter Stack, WiFi, 160 MHz, 400KB SRAM |
| **Hi-Link HLK-PM01** | Power supply internal | AC 220V → DC 5V, 30W, noise filter built-in |
| **Relay Module (5V)** | Saklar pemutus arus | NO contact, 10A @ 250VAC, coil 5V |
| **Terminal Block 2-Pin (2x)** | Konektor I/O | INPUT (PLN), OUTPUT (Beban) |
| **Tactile Switch** | Tombol manual | GPIO 4, On/Off & Factory Reset |
| **LED Built-in** | Indikator status | GPIO 2, WiFi & Matter pairing |
| **Capacitor 1000µF** | Stabilisasi tegangan | Proteksi relay click power drop |
| **Resistor Pull-up 10kΩ** | Stabilisasi GPIO | Untuk GPIO 4 & OLED jika ada |

<p align="center">
  <img src="/assets/nexora-schematic.png?height=400&width=700" alt="Nexora Schematic Diagram" width="700"/><br/>
  <em>Schematic Diagram Nexora V1 (Hi-Link Integrated)</em><br/>
  ⚙️ <strong>Hardware Notes:</strong><br/>
  🔹 Hi-Link input: Live (220V) → Pin 1, Neutral → Pin 2.  
  🔹 Relay output: Coil+ (GPIO 23) & Coil- (GND).  
  🔹 LED GPIO 2 untuk WiFi status (built-in pada ESP32-C3).  
  🔹 Terminal sekrup output: Fasa switched & Netral pass-through.  
</p>

---

## 💻 Software & Library

### Pada ESP32 (Firmware Arduino Matter)
| Library | Fungsi |
|---------|--------|
| **WiFi.h** | Koneksi jaringan WiFi native |
| **WiFiManager.h** | Auto-setup WiFi via captive portal |
| **Preferences.h** | Store state relay saat mati listrik |
| **matter.h** (Arduino Matter) | Matter protocol stack & device definition |
| **Arduino_OTA.h** | Over-the-Air firmware update |
| **Relay Control** | digitalWrite(GPIO 23) untuk relay |

### Matter Device Definition
```
Device Type: "OnOff Light Switch"
Endpoints:
  - Endpoint 0: Root (Descriptor, Identify)
  - Endpoint 1: Dimmer (OnOff Cluster, LevelControl optional)
QR Code: Auto-generated via ESP32 Matter library
PIN: 20202021 (configurable di firmware)
```

---

## 🏗️ Arsitektur Sistem

### Diagram Blok Sistem
```
         ┌─────────────────────────┐
         │  220V AC PLN Input      │
         └────────────┬────────────┘
                      │
         ┌────────────▼────────────┐
         │  Hi-Link HLK-PM01       │
         │  (AC-DC Converter)      │
         └────────────┬────────────┘
                      │ 5V DC
         ┌────────────▼────────────┐
         │   ESP32-C3 Core         │
         │ Matter Protocol Stack   │
         │ WiFi & GPIO Control     │
         └────────────┬────────────┘
                      │ GPIO 23
         ┌────────────▼────────────┐
         │  Relay Module (5V)      │
         │  NO Contact Switch      │
         └────────────┬────────────┘
                      │ Switched AC
         ┌────────────▼────────────┐
         │  Beban (Lampu/Kipas)    │
         └─────────────────────────┘

         WiFi/Matter Cloud:
         ┌─────────────────────────┐
         │ Apple Home / Google Home│
         │ / Alexa Ecosystem       │
         └─────────────────────────┘
```

### Diagram Alur Data
```
┌──────────────────────────────┐
│ Power ON & Initialization    │
├──────────────────────────────┤
│ 1. Boot ESP32-C3             │
│ 2. Load state dari Pref      │
│ 3. Setup WiFi (WiFiManager)  │
│ 4. Init Matter Stack         │
└──────────────────┬───────────┘
                   │
┌──────────────────▼───────────┐
│ Main Loop (Non-Blocking)     │
├──────────────────────────────┤
│ - Listen WiFi events         │
│ - Check GPIO 4 (button)      │
│ - Process Matter commands    │
│ - Toggle Relay GPIO 23       │
│ - Save state → Preferences   │
│ - Handle OTA update          │
└──────────────────┬───────────┘
                   │
┌──────────────────▼───────────┐
│ Matter Protocol Integration  │
├──────────────────────────────┤
│ - Device appear di home app  │
│ - Cloud sync (optional)      │
│ - Native voice control ready │
└──────────────────────────────┘
```

---

## 🔄 Alur Kerja Sistem

### 1. Inisialisasi Sistem
```
Power ON
  ├─ Boot ESP32-C3
  ├─ Load relay state dari Preferences
  ├─ Inisialisasi GPIO 2 (LED), GPIO 4 (button), GPIO 23 (relay)
  ├─ Setup WiFi via WiFiManager (Captive Portal)
  ├─ Initialize Matter stack
  └─ Pairing ready → LED blink blue slow
```

### 2. Kontrol Relay (3 Metode)
**A. Manual via Tombol (GPIO 4)**
```
Press button (GPIO 4)
  ├─ If relayState == ON → turn OFF
  ├─ If relayState == OFF → turn ON
  ├─ digitalWrite(GPIO 23, newState)
  ├─ Save ke Preferences
  └─ Notify Matter cloud (jika terhubung)
```

**B. Remote via Matter Protocol**
```
Apple Home / Google Home / Alexa
  ├─ Send "OnOff" command
  ├─ Matter stack → GPIO 23
  ├─ Update relay state
  ├─ Save Preferences
  └─ Instant feedback di app
```

**C. Factory Reset (Long Press GPIO 4)**
```
Long press button ≥ 10 detik
  ├─ LED blink fast (3 per second)
  ├─ Clear WiFi credentials
  ├─ Clear Matter pairing data
  ├─ Reset relay ke OFF
  ├─ Reboot
  └─ Kembali ke WiFiManager setup mode
```

### 3. State Persistence (Preferences.h)
```
Setiap toggle relay:
  └─ preferences.putBool("relayState", newState)
  
Saat mati listrik → PLN kembali:
  └─ Load relayState dari Preferences
  └─ Relay otomatis set sesuai last state
```

### 4. OTA Update
```
Arduino IDE: Sketch → Export Compiled Binary
  ├─ Ambil binary dari /build folder
  ├─ Di app: Tools → OTA Upload → Pilih binary
  ├─ Upload → Reboot
  └─ Firmware updated tanpa colokkan USB
```

---

## ⚙️ Instalasi & Setup

### 1. Clone Repository
```bash
git clone https://github.com/yourusername/kapaksitor-nexora-v1.git
cd kapaksitor-nexora-v1
```

### 2. Setup Arduino IDE

#### Install ESP32 Board Package
1. Buka Arduino IDE
2. File → Preferences
3. Tambahkan URL di "Additional Boards Manager URLs":
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Tools → Board Manager → Cari "ESP32" → Install (versi 3.0+ untuk C3 support)

#### Install Matter Support
1. Sketch → Include Library → Manage Libraries
2. Cari & install:
   - **Arduino Matter** (by Arduino)
   - **WiFiManager** by tzapu
   - Atau gunakan: https://github.com/espressif/esp-matter

### 3. Konfigurasi Firmware
Edit file `main.ino`:
```cpp
// Matter Device Configuration
#define MATTER_DEVICE_NAME "Nexora V1"
#define MATTER_VENDOR_ID 0x1234 // Ganti dengan vendor ID
#define MATTER_PRODUCT_ID 0x5678

// GPIO Pins
#define RELAY_PIN 23
#define BUTTON_PIN 4
#define LED_STATUS_PIN 2

// WiFi Setup
const char* ssid_default = "";
const char* password_default = "";
```

### 4. Upload ke ESP32-C3
```
1. Hubungkan ESP32-C3 Super Mini ke PC via USB-C
2. Tools → Board → ESP32C3 Dev Module
3. Tools → Port → Pilih port ESP32-C3
4. Sketch → Upload
5. Monitor Serial (Baud: 115200) untuk melihat log
```

Expected Output:
```
[WiFi] WiFiManager starting...
[WiFi] Waiting for connection...
[Matter] Initializing Matter stack...
[Matter] Device pairing code: XXXX XXXX XXXX
[Status] Ready for pairing!
```

---

## 📱 Panduan Pairing

### Step 1: Power & WiFi Setup
1. Hubungkan Nexora ke listrik (LED GPIO 2 berkedip biru pelan)
2. Tunggu ~3 detik, esp32 akan buat hotspot: `Nexora-Setup`
3. Buka WiFi di phone, connect ke `Nexora-Setup`
4. Browser otomatis buka portal WiFiManager
5. Pilih WiFi rumah → Masukkan password → Save

### Step 2: Matter Pairing
1. Buka aplikasi home (Apple Home / Google Home / Alexa)
2. Tap **Add Device** atau **+ Add**
3. Tap **Scan Code** atau **Add Matter Device**
4. Scan QR code yang tertempel di unit (atau input PIN: `20202021`)
5. Tunggu proses pairing (~30 detik)
6. Device muncul sebagai "Light" dengan nama "Nexora V1"

### Step 3: Test Kontrol
- Tap on/off di app → Relay menyala/mati
- Tekan button fisik → Status app update
- Voice command: "Hey Siri, turn on Nexora" (Apple Home)

---

## 🔌 Skema Wiring

> **⚠️ PERINGATAN KESELAMATAN:** Matikan MCB utama sebelum menyambungkan kabel. Nexora V1 bekerja dengan tegangan tinggi 220V AC!

### Wiring Checklist
- [ ] Hi-Link INPUT: Live (L, 220V) → Terminal L, Neutral (N) → Terminal N
- [ ] Relay OUTPUT: Fasa switched ke beban, Netral pass-through
- [ ] Button GPIO 4: One end → GND, other end → GPIO 4
- [ ] LED GPIO 2: Built-in pada ESP32-C3 (no external setup)
- [ ] Terminal GND: Common ground untuk semua komponen

### Diagram Pengkabelan Detail
```
┌─────────────────────────────────────┐
│         220V AC PLN Input           │
│     (Dari MCB Rumah)                │
├─────────────────────────────────────┤
│  Live (L)  ──→  Hi-Link L input     │
│  Neutral   ──→  Hi-Link N input     │
└─────────────────────────────────────┘
                    │
         ┌──────────▼──────────┐
         │  Hi-Link HLK-PM01   │
         │  +5V DC output      │
         └──────────┬──────────┘
                    │
         ┌──────────▼──────────┐
         │   ESP32-C3          │
         │  GND, VCC           │
         │  GPIO 23 → Relay    │
         │  GPIO 4  ← Button   │
         │  GPIO 2  → LED      │
         └──────────┬──────────┘
                    │ Relay coil
         ┌──────────▼──────────┐
         │  Relay Module       │
         │  NO Contact         │
         └──────────┬──────────┘
                    │
              Fasa Switched
                    │
         ┌──────────▼──────────┐
         │  Beban (Lampu/Kipas)│
         │  Netral (Pass-thru) │
         └─────────────────────┘
```

---

## 🐞 Troubleshooting

### Alat Tidak Merespon (Lampu Mati Saat Relay Hidup)
**Gejala:** Tombol hidup tapi lampu tidak menyala, relay tidak berbunyi.

**Solusi:**
- Cek kabel input Hi-Link terpasang kencang (L & N)
- Verifikasi arus PLN aktif (gunakan multimeter)
- Cek relay coil supply 5V dari Hi-Link
- Test relay manual dengan jumper 5V

### Gagal Pairing Matter
**Gejala:** App menampilkan "Cannot add device" atau timeout.

**Solusi:**
- Pastikan HP & ESP32 di WiFi yang sama
- Lakukan **Factory Reset**: Tekan tombol GPIO 4 selama 10 detik (LED cepat)
- Ulangi WiFi setup via WiFiManager
- Coba pairing ulang dengan QR code atau PIN manual

### WiFi Disconnect Terus-menerus
**Gejala:** LED status blink cepat, relay sering reset.

**Solusi:**
- Cek signal WiFi di lokasi (ganti lokasi atau pindahkan router)
- Pastikan password WiFi benar di WiFiManager portal
- Restart ESP32: Tekan RESET button atau colok ulang

### Status di App Tidak Update
**Gejala:** Relay menyala tapi app masih OFF.

**Solusi:**
- Refresh app / close & reopen
- Check WiFi connection (LED status)
- Coba force Matter reconnect: Hapus device dari app, pair ulang

### OTA Update Gagal
**Gejala:** Upload terputus atau boot loop setelah update.

**Solusi:**
- Dekatkan laptop dengan ESP32 (signal WiFi kuat)
- Download binary compiled terbaru dari IDE
- Retry OTA dengan koneksi stabil
- Jika boot loop: Tekan RESET button, lakukan factory reset, upload ulang

---

## 📁 Struktur Proyek

```
kapaksitor-nexora-v1/
├── firmware/
│   ├── main.ino                # Logic Matter + Relay control + OTA
│   ├── config.h                # Pin definition & Matter params
│   └── preferences.h           # State persistence config
├── hardware/
│   ├── casing-v1.stl           # 3D Print file (modular box)
│   ├── schematic.pdf           # Wiring diagram internal
│   └── pcb-layout.pdf          # PCB design reference
├── assets/
│   ├── nexora-banner.png       # Header image
│   ├── nexora-demo.gif         # Demo animation
│   ├── nexora-front.png        # Hardware front view
│   ├── nexora-side.png         # Hardware side view
│   ├── nexora-internal.png     # PCB internal view
│   ├── nexora-wiring.png       # Wiring detail
│   └── nexora-schematic.png    # Full schematic
├── docs/
│   ├── manual-book.pdf         # Panduan lengkap (printable)
│   ├── matter-pairing.md       # Detailed pairing steps
│   └── faq.md                  # FAQ & tips
├── README.md                   # File ini
└── LICENSE                     # MIT License

```

---

## 📄 Lisensi

MIT License © 2026 Kapaksitor Labs

Kode ini bebas digunakan untuk tujuan komersial maupun personal dengan attribution.

---

<div align="center">

**⚡ Nexora V1 - Smart Switch Berbasis Matter untuk Rumah Pintar**

Dibuat dengan ❤️ untuk komunitas DIY & IoT Indonesia

[GitHub](https://github.com/yourusername/kapaksitor-nexora-v1) • [Issues](https://github.com/yourusername/kapaksitor-nexora-v1/issues) • [Discussions](https://github.com/yourusername/kapaksitor-nexora-v1/discussions)

</div>
