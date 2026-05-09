# Smart Lab Security and Environmental Monitoring System

An IoT-based smart laboratory security system using Arduino/ESP8266 that combines:

- 🌡️ Environmental Monitoring  
- 💨 Gas Leakage Detection  
- 👤 Motion Detection  
- 🌬️ Pressure Monitoring  
- 📶 WiFi Web Monitoring  
- 🔐 RFID + Password Based Access Control  
- 🚪 Automatic Servo Door Lock System  

---

# 📌 Features

## Environmental Monitoring

- Real-time temperature monitoring using **LM35**
- Gas leakage/smoke detection using **MQ2**
- Human motion detection using **PIR Sensor**
- Atmospheric pressure monitoring using **BMP280**
- Live sensor values displayed on **16x2 LCD**
- Data accessible through **WiFi webpage**

---

## Security System

- RFID card authentication using **RC522**
- Password verification using **4x4 Keypad**
- Two-step authentication for enhanced security
- Servo motor controlled automatic door lock

---

# 🛠️ Components Used

| Component | Quantity |
|---|---|
| Arduino UNO / ESP8266 | 1 |
| RC522 RFID Module | 1 |
| RFID Card/Tag | 1 |
| 4x4 Keypad | 1 |
| Servo Motor | 1 |
| LM35 Temperature Sensor | 1 |
| MQ2 Gas Sensor | 1 |
| PIR Motion Sensor | 1 |
| BMP280 Pressure Sensor | 1 |
| 16x2 LCD Display | 1 |
| Jumper Wires | As required |
| Breadboard | 1 |

---

# ⚙️ Technologies Used
- Arduino IDE
- Embedded C/C++
- IoT Web Server
- SPI Communication
- I2C Communication

---

# 🔌 Pin Connections

## RFID RC522 Connections
| RC522 Pin | Arduino Pin |
|---|---|
| SDA | D10 |
| SCK | D13 |
| MOSI | D11 |
| MISO | D12 |
| RST | A0 |
| GND | GND |
| 3.3V | 3.3V |

---

## LCD Connections
| LCD Pin | Arduino Pin |
|---|---|
| RS | 12 |
| EN | 11 |
| D4 | 5 |
| D5 | 4 |
| D6 | 3 |
| D7 | 2 |

---

## Sensor Connections
| Sensor | Pin |
|---|---|
| LM35 | A0 |
| MQ2 | A1 |
| PIR | D8 |
| Servo | A1 |

---

# 🚀 Working Principle
## Step 1: Environment Monitoring
The system continuously reads:

- Temperature
- Gas concentration
- Motion status
- Atmospheric pressure

Values are displayed on LCD and webpage.
---
## Step 2: Alert Generation

Alerts are generated if:
- Temperature > 40°C
- Gas level exceeds threshold
- Motion detected

The webpage displays:

```text
🚨 ALERT ACTIVE 🚨
```
Otherwise:

```text
ALL SAFE ✅
```

---

## Step 3: RFID Authentication

User scans RFID card.

System compares scanned UID with stored authorized UID.

If matched:

```text
RFID Verified ✅
```
---
## Step 4: Password Verification
User enters password through keypad.
If password is correct:

```text
Access Granted ✅
```
Servo motor unlocks door temporarily.

---
# 📡 Web Interface

The ESP8266 hosts a webpage displaying:

- Temperature
- Gas Status
- Motion Detection
- Pressure Reading
- Alert Messages

The webpage refreshes automatically every 2 seconds.

---
# 📂 Project Structure
```text
├── smart_lab_security.ino
├── README.md
├── circuit_diagram.png
├── images/
└── report/
```

---

# ▶️ How to Run

1. Install Arduino IDE
2. Install required libraries:
   - MFRC522
   - Servo
   - Keypad
   - LiquidCrystal
   - Adafruit BMP280
   - ESP8266WiFi
3. Connect hardware properly
4. Upload code to Arduino/ESP8266
5. Open Serial Monitor
6. Access webpage using device IP address

---

# 📷 Future Improvements
- Mobile app integration
- Cloud data storage
- Face recognition
- Buzzer alarm system
- SMS/Email alerts
- Camera surveillance
---

# 📚 Applications
- Smart Laboratories
- Server Rooms
- Industrial Safety Systems
- Smart Offices
- Restricted Area Security

---

# 👨‍💻 Author

Sachidanand Mahapatra  
BTech ECE – IIT Bhilai

---

# 📄 License
This project is for educational and academic purposes.
