#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "Your_Blynk_Auth_Token";

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int moisturePin = A0;
const int pumpPin = 8;
const int threshold = 400; // Adjust this threshold based on calibration

void setup() {
  Blynk.begin(auth, "Your_SSID", "Your_Password");
  lcd.init();
  lcd.backlight();
  pinMode(pumpPin, OUTPUT);
  lcd.print("Smart Irrigation");
  lcd.setCursor(0, 1);
  lcd.print("System Initialized");
  delay(2000);
  lcd.clear();
}

void loop() {
  Blynk.run();
  int moistureLevel = analogRead(moisturePin);
  
  if (moistureLevel < threshold) {
    lcd.print("Soil Dry");
    digitalWrite(pumpPin, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Watering...");
    delay(5000); // Watering time, adjust as needed
    digitalWrite(pumpPin, LOW);
    lcd.clear();
  } else {
    lcd.print("Soil Moist");
    lcd.setCursor(0, 1);
    lcd.print("No Water Needed");
    delay(2000);
    lcd.clear();
  }
  
  Blynk.virtualWrite(V1, moistureLevel);
}



