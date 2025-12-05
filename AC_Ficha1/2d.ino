#define LED 13

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  int ciclos = 3;                 // Número de repetições do processo completo
  int delayAtual = 5000;          // Começa em 5 segundos
  int passo = 500;                // Variação de 500 ms

  // Repetir todo o processo 3 vezes
  for(int c = 0; c < ciclos; c++) {

    // Parte 1: reduzir de 5000 ms até 500 ms
    for (delayAtual = 5000; delayAtual >= 500; delayAtual -= passo) {
      digitalWrite(LED, HIGH);
      delay(delayAtual);
      digitalWrite(LED, LOW);
      delay(delayAtual);
    }

    // Parte 2: aumentar de 500 ms até 5000 ms
    for (delayAtual = 500; delayAtual <= 5000; delayAtual += passo) {
      digitalWrite(LED, HIGH);
      delay(delayAtual);
      digitalWrite(LED, LOW);
      delay(delayAtual);
    }
  }

  // Depois de 3 ciclos, volta ao estado inicial (piscar a 5 s)
  digitalWrite(LED, HIGH);
  delay(5000);
  digitalWrite(LED, LOW);
  delay(5000);

  // E depois repete tudo novamente (loop reinicia)
}
