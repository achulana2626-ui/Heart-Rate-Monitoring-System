# Heart-Rate-Monitoring-System
Heart rate monitoring system using Arduino Uno and MAX30102
# ❤️ IoT-based Heart Rate Monitoring System

IoT-based Heart Rate Monitoring System using Arduino UNO, MAX30102 & 16x2 I2C LCD | Real-time BPM Display | Internship Project at Arunachala NextGen Solutions (11/08/2026 - 22/08/2026)

## 📋 Project Overview
This project is a real-time heart rate monitoring system designed to measure and display human heart rate (BPM) using the MAX30102 pulse oximeter sensor. The system uses Arduino UNO as the microcontroller and displays the BPM on a 16x2 I2C LCD. When no finger is detected, it shows "Place Finger" and when finger is placed, it calculates and displays the heart rate.

Developed as part of the IoT Internship at Arunachala NextGen Solutions.

## 🛠️ Components Required
- Arduino UNO
- MAX30102 Heart Rate Sensor (0x57)
- 16x2 I2C LCD Display (0x27)
- Jumper Wires
- Breadboard
- USB Cable

## 🔌 Circuit Connections

### MAX30102 to Arduino UNO:
- VIN -> 3.3V
- GND -> GND
- SDA -> A4
- SCL -> A5

### I2C LCD to Arduino UNO:
- VCC -> 5V
- GND -> GND
- SDA -> A4
- SCL -> A5

## ⚙️ How It Works
1.  The MAX30102 sensor uses IR LED to detect blood flow in the finger.
2.  Arduino reads the IR value. If IR < 50000, it means no finger is present.
3.  If finger is detected, the `checkForBeat()` function detects heartbeats and calculates BPM.
4.  The average of last 4 BPM values is displayed on the LCD to give a stable reading.
5.  Serial monitor also prints IR value and BPM for debugging.

## ✨ Features
- Real-time BPM monitoring
- Finger detection (Place Finger alert)
- Average BPM calculation for stable output
- Low-cost and portable
- Serial monitor debugging support
- LCD flicker-free display

## 💻 Software Requirements
- Arduino IDE
- Libraries:
    - Wire.h
    - LiquidCrystal_I2C.h
    - MAX30105.h (works for MAX30102)
    - heartRate.h

Install libraries from Library Manager in Arduino IDE.

## 🚀 How to Run
1. Connect the hardware as per circuit diagram.
2. Open `heart_rate_monitor.ino` in Arduino IDE.
3. Install required libraries.
4. Select Board: Arduino UNO and correct COM Port.
5. Upload the code.
6. Open Serial Monitor (115200 baud) and place finger on sensor.

## 📸 Output
- LCD Shows: "Place Finger" when idle
- LCD Shows: "Heart Rate: 72 BPM" when measuring

## 👩‍💻 Developed By
**Dhanushya & A.P.Akshaya** - IoT Internship (11/08/2026 - 22/08/2026)
Arunachala NextGen Solutions

## 📄 License
This project is open source for educational purpose.
