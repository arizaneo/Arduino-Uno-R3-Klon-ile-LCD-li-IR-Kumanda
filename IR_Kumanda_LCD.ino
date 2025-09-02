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

  // IR alıcıyı başlat
  IrReceiver.begin(IR_RECV_PIN, ENABLE_LED_FEEDBACK);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("IR Kumanda Test");
  delay(1000);
  lcd.clear();
}

// HEX kodu buton ismine çeviren fonksiyon
String getButtonName(unsigned long code) {
  switch (code) {
    case 0xBA45FF00: return "1";
    case 0xB946FF00: return "2";
    case 0xB847FF00: return "3";
    case 0xBB44FF00: return "4";
    case 0xBF40FF00: return "5";
    case 0xBC43FF00: return "6";
    case 0xF807FF00: return "7";
    case 0xEA15FF00: return "8";
    case 0xF609FF00: return "9";
    case 0xE619FF00: return "0";
    case 0xE916FF00: return "*";
    case 0xF20DFF00: return "#";
    case 0xE718FF00: return "YUKARI";
    case 0xAD52FF00: return "ASAGI";
    case 0xF708FF00: return "SOL";
    case 0xA55AFF00: return "SAG";
    case 0xE31CFF00: return "OK";
    default: return "Bilinmeyen";
  }
}

void loop() {
  if (IrReceiver.decode()) {
    unsigned long kod = IrReceiver.decodedIRData.decodedRawData;

    Serial.print("Kod: 0x");
    Serial.println(kod, HEX);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tus:");
    lcd.setCursor(0, 1);
    lcd.print(getButtonName(kod));

    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);

    IrReceiver.resume(); // yeni veri için hazırla
  }
}
