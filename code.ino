#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "MAX30105.h"
#include "heartRate.h"

MAX30105 particleSensor;
LiquidCrystal_I2C lcd(0x27, 16, 2); // Your LCD address

const byte RATE_SIZE = 4; // Increase this for more averaging
byte rates[RATE_SIZE];
byte rateSpot = 0;
long lastBeat = 0;
float beatsPerMinute;
int beatAvg;

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing...");

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Health Monitor");
  lcd.setCursor(0,1);
  lcd.print("Starting...");

  Wire.begin();

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    lcd.clear();
    lcd.print("MAX30102 NOT");
    lcd.setCursor(0,1);
    lcd.print("FOUND! Check 0x57");
    while (1);
  }

  // Setup for MAX30102 - tuned for finger
  byte ledBrightness = 60; // Options: 0=Off to 255=50mA. 60 is good for finger
  byte sampleAverage = 4; // Average 4 samples to reduce noise
  byte ledMode = 2; // 2 = Red + IR only
  int sampleRate = 400; // 400 samples/sec
  int pulseWidth = 411; // 411 us. 16-bit ADC
  int adcRange = 4096; // 4096 nA. Higher = more range

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange);
  particleSensor.setPulseAmplitudeRed(0x0A); // Turn Red LED low for finger
  particleSensor.setPulseAmplitudeGreen(0); // Green not used

  delay(1000);
  lcd.clear();
}

void loop() {
  long irValue = particleSensor.getIR();

  // If no finger, IR will be very low
  if (irValue < 50000) {
    lcd.clear();//Clear screen when no finger
    lcd.setCursor(0,0);
    lcd.print("Place Finger ");
    lcd.setCursor(0,1);
    lcd.print(" ");
    // Reset average when finger removed
    for(byte i=0; i<RATE_SIZE; i++) rates[i] = 0;
    rateSpot = 0;
    beatAvg = 0;
  }
  else {
    bool beatDetected=false;//Flag to check if a beat occured
    // Finger detected - check for heart beat
    if (checkForBeat(irValue) == true) {
      long delta = millis() - lastBeat;
      lastBeat = millis();

      beatsPerMinute = 60 / (delta / 1000.0);

      if (beatsPerMinute < 255 && beatsPerMinute > 20) {
        rates[rateSpot++] = (byte)beatsPerMinute;
        rateSpot %= RATE_SIZE;

        // Take average
        beatAvg = 0;
        for (byte x = 0 ; x < RATE_SIZE ; x++) beatAvg += rates[x];
        beatAvg /= RATE_SIZE;
      }
      beatDetected = true;
    }

    //clear LCD only when a new beat is detected to avoid flicker
    if(beatDetected){
      lcd.clear();
    }

    lcd.setCursor(0,0);
    lcd.print("Heart Rate: ");
    lcd.setCursor(0,1);
    if(beatAvg > 0) {
      lcd.print(beatAvg);
      lcd.print(" BPM "); //Extra spaces to overwrite old text
    } else {
      lcd.print("Calculating... ");
    }
  }

  Serial.print("IR=");
  Serial.print(irValue);
  Serial.print(", BPM=");
  Serial.print(beatsPerMinute);
  Serial.print(", Avg=");
  Serial.println(beatAvg);

  delay(10); // Small delay for I2C stability
}