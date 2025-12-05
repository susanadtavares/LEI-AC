#include <LiquidCrystal.h>

#define LDRpin A0

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  lcd.print("Luminosidade:");
}

void loop() {
  int leitura = analogRead(LDRpin);
  lcd.setCursor(0, 1);
  lcd.print("Valor: ");
  lcd.print(leitura);
  lcd.print("    ");
  delay(500);
}
