#define LED 13   // LED interno do Arduino

void setup() {
  pinMode(LED, OUTPUT); // Define o LED como saída
}

void loop() {
  digitalWrite(LED, HIGH);  // Acende o LED
  delay(5000);              // Espera 5 segundos

  digitalWrite(LED, LOW);   // Apaga o LED
  delay(5000);              // Espera 5 segundos
}
