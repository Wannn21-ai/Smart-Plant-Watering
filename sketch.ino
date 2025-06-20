#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT22
#define LED_POMPA 7
#define SOIL_PIN A0

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); // Ganti ke 0x3F jika LCD tidak tampil

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
  lcd.backlight();

  pinMode(LED_POMPA, OUTPUT);
  digitalWrite(LED_POMPA, LOW);
}

void loop() {
  float suhu = dht.readTemperature();
  int analogSoil = analogRead(SOIL_PIN);
  float kelembaban = map(analogSoil, 1023, 0, 0, 100); // simulasi 0-100%

  lcd.setCursor(0, 0);
  lcd.print("Suhu: ");
  lcd.print(suhu);
  lcd.print("C ");

  lcd.setCursor(0, 1);
  lcd.print("Lembab: ");
  lcd.print(kelembaban);
  lcd.print("% ");

  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.print("C | Lembab: ");
  Serial.print(kelembaban);
  Serial.print("%");

  if (suhu <= 30 && kelembaban < 60) {
    digitalWrite(LED_POMPA, HIGH); // Pompa nyala
    Serial.println(" | Pompa: ON");
  } else {
    digitalWrite(LED_POMPA, LOW); // Pompa mati
    Serial.println(" | Pompa: OFF");
  }

  delay(2000);
}
