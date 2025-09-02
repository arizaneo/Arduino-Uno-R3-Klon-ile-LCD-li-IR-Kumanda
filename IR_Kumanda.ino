#include <IRremote.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define IR_RECV_PIN 2   // IR alıcı pini
#define LED_PIN 7       // LED pini

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(9600);

  // Yeni IRremote başlatma
  IrReceiver.begin(IR_RECV_PIN, ENABLE_LED_FEEDBACK);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("IR Kumanda Test");
  delay(1000);
  lcd.clear();
}

void loop() {
  if (IrReceiver.decode()) {
    unsigned long kod = IrReceiver.decodedIRData.decodedRawData;

    Serial.print("Kod: ");
    Serial.println(kod, HEX);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tusa Basildi:");
    lcd.setCursor(0, 1);
    lcd.print(kod, HEX);

    digitalWrite(LED_PIN, HIGH);
    delay(300);
    digitalWrite(LED_PIN, LOW);

    IrReceiver.resume(); // Yeni veri için hazırla
  }
}
