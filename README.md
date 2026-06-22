				###	Köpeğim mi, kedi mi? (Eğer köpeklerden ve Kedilerden korkuyorsanız)	###


DOSYALAR:
- Kopek-Kedi-Kovucu.ino   -> Ana kod (Arduino IDE ile yukle)
- README.txt          -> Bu dosya

BAĞLANTI SEMASI:
----------------

PIR HAREKET SENSORU (HC-SR501):
  VCC  -> 5V (veya 3V3)
  GND  -> GND
  OUT  -> D2 (Arduino/ESP32)

ULTRASONIK HOPARLOR / PIEZO BUZZER (15-25 kHz calisan):
  + (Kirmizi)  -> D3 (PWM pini)
  - (Siyah)    -> GND

DURUM LED'I (OPSIYONEL):
  Anot (+) -> 220 ohm direnc -> D13
  Katot (-) -> GND

ÖZELLIKLER:
-----------
✓ PIR kesmesi ile aninda tetiklenme (guch tasarrufu)
✓ 15-25 kHz arasi frekans tarama (hayvanlar alismaz)
✓ Her tetiklemede 10 saniye calisir
✓ Iki tetikleme arasi 5 saniye bekleme (cooldown)
✓ LED ile durum gosterimi
✓ Arduino Uno, Nano, ESP32, ESP8266 ile uyumlu


YÜKLEME:
--------
1. Arduino IDE acin
2. Dosya > Ac > pet_repellent.ino secin
3. Araclar > Kart > (Kartinizi secin: Arduino Uno, ESP32 Dev Module, vb.)
4. Araclar > Port > (COM portunuzu secin)
5. Yukle (Ok butonu)


KULLANIM:
---------
- Cihaz guc aldiginda PIR 30-60 sn ısınır (normal)
- LED yanik = ultraseonic aktif
- LED sonuk = bekleme modu
- Serial Monitor (115200 baud) acarsaniz loglari gorursunuz


PIL ILE CALISTIRMA (ESP32 ICIN):
--------------------------------
Daha dusuk guc icin setup() icine asagidaki satirlari ekleyin:

  esp_sleep_enable_ext0_wakeup(GPIO_NUM_2, 1); // PIR pini ile uyan
  // ... kodun sonuna, loop() bitisinden once:
  if (!isActive && (millis() - lastTrigger > 30000)) {
    Serial.println("Deep sleep...");
    esp_deep_sleep_start();
  }


SORUN GIDERME:
--------------
- Hoparlor ses cikarmiyorsa: Farkli bir piezo/ultrasonik model deneyin (15-25 kHz)
- PIR sürekli tetikleniyorsa: Jumper'i "L" (single trigger) moduna cekin
- Hassasiyet: PIR üzerindeki potansiyometrelerle ayarlanir


GELISTIRME FIKIRLERI:
---------------------
- HC-SR04 mesafe sensoru ekleyerek "yaklasinca calistir"
- Fotodirenç (LDR) ile gece/gündüz modu
- Bluetooth/WiFi ile uzaktan ac/kapa
- Solar panel + LiPo sarj modulu (TP4056) ile off-grid
- Ses seviyesi ayari (potansiyometre ile)


GÜVENLIK UYARISI:
-----------------
- Ultrasonik ses insan duymasa da uzun sure yakininda rahatsizlik verebilir
- Hayvanlara zarar vermez, sadece rahatsız edip uzaklastirir
- Yasal duzenlemelere uygunluk kontrol edin


LISANS:
-------
MIT License - Serbest kullanım, degistirme, dagitim.




## DİKKAT OKU ##


Bu kod, ultrasonik sensörün mesafe ölçümünü kullanarak hayvanların yaklaşmasını algılar ve buzzer ile uyarı verir. Ayrıca, köpek ve kedi butonlarına basıldığında ilgili mesajları seri ekrana yazdırır. Sensörün trig ve echo pinlerini doğru şekilde bağladığınızdan emin olun. Ayrıca, kodu kendi ihtiyaçlarınıza göre özelleştirebilirsiniz.

Dikkat: Lütfen bu cihazı insanlara veya hayvanlara zarar vermek amacıyla kullanmayın. Sadece hayvanları uzaklaştırmak için kullanın. 
