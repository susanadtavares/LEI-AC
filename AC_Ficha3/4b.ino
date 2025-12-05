#include <Servo.h>

const int SERVO = 9;
const int BOTAO1 = 2;
const int BOTAO2 = 3;

int tempo = 10;
int buttonStateA = LOW; // Estado atual do botão A
int lastButtonStateA = LOW; // Último estado do botão A

Servo s1; // Variável Servo1
int posicaoS; // Posição Servo

void setup()
{
  s1.attach(SERVO);
  Serial.begin(9600);

  s1.write(0);
  delay(1000);

  pinMode(BOTAO1, INPUT_PULLUP);
  pinMode(BOTAO2, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(BOTAO1), acelerar, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BOTAO2), desacelerar, CHANGE);
}

void acelerar()
{
  if (tempo > 1) {
    tempo--;
    Serial.print(tempo);
  }
}

void desacelerar()
{
  if (tempo < 40) {
    tempo++;
    Serial.print(tempo);
  }
}

void servoGirar(int tempo)
{
  for (posicaoS = 0; posicaoS <= 180; posicaoS++) {
    s1.write(posicaoS);
    delay(tempo);
  }
}

void delayGiro(int tempo)
{
  for (posicaoS = 180; posicaoS >= 0; posicaoS--) {
    s1.write(posicaoS);
    delay(tempo);
  }
}

void loop()
{
  while (true) {
    servoGirar(tempo);
    delayGiro(tempo);
  }
}
