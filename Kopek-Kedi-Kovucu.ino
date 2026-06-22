                                                       // Proje Tarafından Yazılmıştır : MuratAlpTR // 

#include <Arduino.h>

// Pin tanımlamaları
const uint8_t PIR_PIN = 2;        // PIR sensör çıkış pini
const uint8_t ULTRASONIC_PIN = 3; // Ultrasonik hoparlör/buzzer pini (PWM destekli)
const uint8_t LED_PIN = 13;       // Durum LED'i (opsiyonel)

// Parametreler
const uint16_t FREQUENCY_START = 15000;  // Hz - başlangıç frekansı (köpek/kedi aralığı)
const uint16_t FREQUENCY_END = 25000;    // Hz - bitiş frekansı
const uint16_t SWEEP_DURATION = 2000;    // ms - bir tarama süresi
const uint16_t ACTIVE_DURATION = 10000;  // ms - tetiklenince ne kadar çalışsın
const uint16_t COOLDOWN = 5000;          // ms - iki tetikleme arası bekleme

// Değişkenler
volatile bool motionDetected = false;
unsigned long lastTrigger = 0;
unsigned long activeStart = 0;
bool isActive = false;

void IRAM_ATTR pirISR() {
  motionDetected = true;
}

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(ULTRASONIC_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), pirISR, RISING);
  
  // ESP32 için PWM kanalı ayarla (Arduino Uno/Nano için gerekmez)
  #ifdef ESP32
  ledcSetup(0, FREQUENCY_START, 8);
  ledcAttachPin(ULTRASONIC_PIN, 0);
  #endif
  
  digitalWrite(LED_PIN, LOW);
  Serial.begin(115200);
  Serial.println("Pet Repellent Hazir");
}

void loop() {
  unsigned long now = millis();
  
  // Hareket algılandığında ve cooldown dolduysa aktif et
  if (motionDetected && !isActive && (now - lastTrigger > COOLDOWN)) {
    isActive = true;
    activeStart = now;
    lastTrigger = now;
    motionDetected = false;
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Hareket algilandi - Ultrasonik basladi");
  }
  
  // Aktif süresi dolduysa kapat
  if (isActive && (now - activeStart > ACTIVE_DURATION)) {
    isActive = false;
    stopUltrasonic();
    digitalWrite(LED_PIN, LOW);
    Serial.println("Ultrasonik durduruldu");
  }
  
  // Aktifse frekans tarama yap
  if (isActive) {
    sweepUltrasonic();
  }
}

void sweepUltrasonic() {
  unsigned long elapsed = millis() - activeStart;
  uint16_t progress = (elapsed % SWEEP_DURATION) * 100 / SWEEP_DURATION;
  uint16_t freq = FREQUENCY_START + (FREQUENCY_END - FREQUENCY_START) * progress / 100;
  
  #ifdef ESP32
  ledcWriteTone(0, freq);
  ledcWrite(0, 128); // %50 duty cycle
  #else
  tone(ULTRASONIC_PIN, freq);
  #endif
}

void stopUltrasonic() {
  #ifdef ESP32
  ledcWrite(0, 0);
  #else
  noTone(ULTRASONIC_PIN);
  #endif
}

                                                       // Proje Tarafından Yazılmıştır : MuratAlpTR // 
