#define LED_PIN_VERDE 10
#define LED_PIN_AMARELO 11
#define LED_PIN_VERMELHO 12

#define LED_PIN_VERDE_PEOES 8
#define LED_PIN_VERMELHO_PEOES 9

void setup()
{
  pinMode(LED_PIN_VERDE, OUTPUT);
  pinMode(LED_PIN_AMARELO, OUTPUT);
  pinMode(LED_PIN_VERMELHO, OUTPUT);

  pinMode(LED_PIN_VERDE_PEOES, OUTPUT);
  pinMode(LED_PIN_VERMELHO_PEOES, OUTPUT);
}

// Função para piscar os LEDs
void piscaled(int led, int ledp) {
  for (int i = 0; i < 3; i++) {
    digitalWrite(led, HIGH);
    digitalWrite(ledp, HIGH);
    delay(200);
    digitalWrite(led, LOW);
    digitalWrite(ledp, LOW);
    delay(200);
  }
}

//Função para piscar o LED amarelo (tempo diferente dos restantes)
void piscaledAmarelo() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_PIN_AMARELO, HIGH);
    digitalWrite(LED_PIN_VERMELHO_PEOES, HIGH);
    delay(200);
    digitalWrite(LED_PIN_AMARELO, LOW);
    digitalWrite(LED_PIN_VERMELHO_PEOES, LOW);
    delay(200);
  }
}
void loop()
{
  // Liga LED verde e LED vermelho dos peões
  digitalWrite(LED_PIN_VERDE, HIGH);
  digitalWrite(LED_PIN_VERMELHO_PEOES, HIGH);
  delay(7000);
  
  // Desliga LED verde
  piscaled(LED_PIN_VERDE, LED_PIN_VERMELHO_PEOES);
  digitalWrite(LED_PIN_VERDE, LOW);

  // Desliga LED vermelho peões
  piscaledAmarelo();
  digitalWrite(LED_PIN_VERMELHO_PEOES, LOW);

  // Liga LED vermelho e LED verde dos peões
  digitalWrite(LED_PIN_VERMELHO, HIGH);
  digitalWrite(LED_PIN_VERDE_PEOES, HIGH);
  delay(4000);
  
  // Desliga LED Vermelho e LED verde peões
  piscaled(LED_PIN_VERMELHO, LED_PIN_VERDE_PEOES);
  digitalWrite(LED_PIN_VERMELHO, LOW);
  digitalWrite(LED_PIN_VERDE_PEOES, LOW);
}
