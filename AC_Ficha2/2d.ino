#define LED_PIN_VERDE 10
#define LED_PIN_AMARELO 11
#define LED_PIN_VERMELHO 12

#define LED_PIN_VERDE_PEOES 8
#define LED_PIN_VERMELHO_PEOES 9

#define BOTAO_PIN 2

volatile bool botaoPressionado = false;

enum Estado {
  NORMAL_PARTE1,
  NORMAL_PARTE2,
  MODO_PEOES
};

Estado estadoAtual = NORMAL_PARTE1;

void setup() {
  pinMode(LED_PIN_VERDE, OUTPUT);
  pinMode(LED_PIN_AMARELO, OUTPUT);
  pinMode(LED_PIN_VERMELHO, OUTPUT);

  pinMode(LED_PIN_VERDE_PEOES, OUTPUT);
  pinMode(LED_PIN_VERMELHO_PEOES, OUTPUT);

  pinMode(BOTAO_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BOTAO_PIN), botaoISR, FALLING);
}

void botaoISR() {
  botaoPressionado = true;
}

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

void resetLEDs() {
  digitalWrite(LED_PIN_VERDE, LOW);
  digitalWrite(LED_PIN_AMARELO, LOW);
  digitalWrite(LED_PIN_VERMELHO, LOW);
  digitalWrite(LED_PIN_VERDE_PEOES, LOW);
  digitalWrite(LED_PIN_VERMELHO_PEOES, LOW);
}

void ativarModoPeoes() {
  resetLEDs();

  // Piscar LED verde dos carros e vermelho dos peões
  piscaled(LED_PIN_VERDE, LED_PIN_VERMELHO_PEOES);
  resetLEDs();

  // Piscar LED amarelo + vermelho dos peões
  piscaledAmarelo();
  resetLEDs();

  // Vermelho carros e verde peões
  digitalWrite(LED_PIN_VERMELHO, HIGH);
  digitalWrite(LED_PIN_VERDE_PEOES, HIGH);
  delay(4000);

  // Piscar vermelho dos carros e verde dos peões
  piscaled(LED_PIN_VERMELHO, LED_PIN_VERDE_PEOES);
  resetLEDs();

  delay(100); // pequena pausa para evitar transições imediatas
}

void loop() {
  if (botaoPressionado) {
    botaoPressionado = false;
    estadoAtual = MODO_PEOES;
  }

  switch (estadoAtual) {
    case MODO_PEOES:
      ativarModoPeoes();
      estadoAtual = NORMAL_PARTE1;
      return; // evita continuar o loop no mesmo ciclo
      break;

    case NORMAL_PARTE1:
      resetLEDs();
      digitalWrite(LED_PIN_VERDE, HIGH);
      digitalWrite(LED_PIN_VERMELHO_PEOES, HIGH);
      for (int i = 0; i < 70; i++) {  // 70 x 100ms = 7 segundos
        delay(100);
        if (botaoPressionado) {
          botaoPressionado = false;
          estadoAtual = MODO_PEOES;
          return;
        }
      }

      piscaled(LED_PIN_VERDE, LED_PIN_VERMELHO_PEOES);
      piscaledAmarelo();
      estadoAtual = NORMAL_PARTE2;
      break;

    case NORMAL_PARTE2:
      resetLEDs();
      digitalWrite(LED_PIN_VERMELHO, HIGH);
      digitalWrite(LED_PIN_VERDE_PEOES, HIGH);
      for (int i = 0; i < 40; i++) {  // 40 x 100ms = 4 segundos
        delay(100);
        if (botaoPressionado) {
          botaoPressionado = false;
          estadoAtual = MODO_PEOES;
          return;
        }
      }

      piscaled(LED_PIN_VERMELHO, LED_PIN_VERDE_PEOES);
      resetLEDs();
      estadoAtual = NORMAL_PARTE1;
      break;
  }
}
