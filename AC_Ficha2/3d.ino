#define LED_PIN_VERDE 10
#define LED_PIN_AMARELO 11
#define LED_PIN_VERMELHO 12

#define LED_PIN_VERDE_PEOES 8
#define LED_PIN_VERMELHO_PEOES 9

#define BOTAO_PIN 2

int pinosDisplay[7] = {A3, A2, A0, 4, 5, 6, 7}; // a, b, c, d, e, f, g

const byte digitos[10][7] = {
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,1,0,1,1}  // 9
};

volatile bool botaoPressionado = false;
volatile unsigned long ultimoTempoBotao = 0;

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

  for (int i = 0; i < 7; i++) {
    pinMode(pinosDisplay[i], OUTPUT);
    digitalWrite(pinosDisplay[i], LOW);
  }
}

void botaoISR() {
  unsigned long tempoAtual = millis();
  if (tempoAtual - ultimoTempoBotao > 200) {
    botaoPressionado = true;
    ultimoTempoBotao = tempoAtual;
  }
}

void mostrarDigito(int numero) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(pinosDisplay[i], digitos[numero][i]);
  }
}

void apagarDisplay() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(pinosDisplay[i], LOW);
  }
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
  apagarDisplay();
}

void ativarModoPeoes() {
  resetLEDs();
  piscaled(LED_PIN_VERDE, LED_PIN_VERMELHO_PEOES);
  resetLEDs();
  piscaledAmarelo();
  resetLEDs();

  digitalWrite(LED_PIN_VERMELHO, HIGH);
  digitalWrite(LED_PIN_VERDE_PEOES, HIGH);
  delay(4000);

  piscaled(LED_PIN_VERMELHO, LED_PIN_VERDE_PEOES);
  resetLEDs();
  delay(100);
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
      return;

    case NORMAL_PARTE1:
      apagarDisplay();           // <- primeiro, apaga o display
      resetLEDs();    
      digitalWrite(LED_PIN_VERDE, HIGH);
      digitalWrite(LED_PIN_VERMELHO_PEOES, HIGH);

      for (int i = 0; i < 70; i++) {
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
      digitalWrite(LED_PIN_VERDE_PEOES, HIGH);

      for (int i = 7; i >= 0; i--) {
        mostrarDigito(i);

        if (i > 1) {
          digitalWrite(LED_PIN_VERMELHO, HIGH);
          delay(1000);
        } else {
          digitalWrite(LED_PIN_VERMELHO, HIGH);
          delay(500);
          digitalWrite(LED_PIN_VERMELHO, LOW);
          delay(500);
        }

        if (botaoPressionado) {
          botaoPressionado = false;
          apagarDisplay();
          estadoAtual = MODO_PEOES;
          return;
        }
      }

      apagarDisplay();
      piscaled(LED_PIN_VERMELHO, LED_PIN_VERDE_PEOES);
      resetLEDs();
      estadoAtual = NORMAL_PARTE1;
      break;
  }
}
