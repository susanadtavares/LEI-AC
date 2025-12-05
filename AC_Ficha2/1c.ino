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
void loop()
{
  // Liga LED verde e LED vermelho dos peões
  digitalWrite(LED_PIN_VERDE, HIGH);
  digitalWrite(LED_PIN_VERMELHO_PEOES, HIGH);
  delay(8000);

  // Desliga LED verde
  digitalWrite(LED_PIN_VERDE, LOW);

  // Liga LED amarelo
  digitalWrite(LED_PIN_AMARELO, HIGH);
  delay(2000);

  //Desliga LED Amarelo e LED Vermelho peões
  digitalWrite(LED_PIN_AMARELO, LOW);
  digitalWrite(LED_PIN_VERMELHO_PEOES, LOW);

  // Liga LED vermelho e LED verde dos peões
  digitalWrite(LED_PIN_VERMELHO, HIGH);
  digitalWrite(LED_PIN_VERDE_PEOES, HIGH);
  delay(5000);

  // Desliga LED vermelho e LED verde dos peões
  digitalWrite(LED_PIN_VERMELHO, LOW);
  digitalWrite(LED_PIN_VERDE_PEOES, LOW);
}
