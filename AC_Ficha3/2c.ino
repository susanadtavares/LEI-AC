#include <LiquidCrystal.h>

#define LDRpin A0

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int amostras[15];
int index = 0;
unsigned long ultimaLeitura = 0;
unsigned long tempoInicioMostrar = 0;
bool mostrarEstatisticas = false;

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  unsigned long agora = millis();

  if (!mostrarEstatisticas) {
    if (agora - ultimaLeitura >= 667) {
      int leitura = analogRead(LDRpin);
      amostras[index] = leitura;
      index++;

      lcd.setCursor(0, 0);
      lcd.print("Luz: ");
      lcd.print(leitura);
      lcd.print("    ");

      ultimaLeitura = agora;
    }

    if (index >= 15) {
      int minVal = amostras[0];
      int maxVal = amostras[0];
      int soma = 0;

      for (int i = 0; i < 15; i++) {
        if (amostras[i] < minVal) minVal = amostras[i];
        if (amostras[i] > maxVal) maxVal = amostras[i];
        soma += amostras[i];
      }

      int media = soma / 15;

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Min:");
      lcd.print(minVal);
      lcd.setCursor(8, 0);
      lcd.print("Max:");
      lcd.print(maxVal);

      lcd.setCursor(0, 1);
      lcd.print("Media:");
      lcd.print(media);

      tempoInicioMostrar = agora;
      mostrarEstatisticas = true;
      index = 0;
    }
  } else {
    if (agora - tempoInicioMostrar >= 5000) {
      mostrarEstatisticas = false;
      lcd.clear();
    }
  }
}
