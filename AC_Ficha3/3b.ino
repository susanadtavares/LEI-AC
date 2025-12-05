const int trigPin = 5;
const int echoPin = 4;

const int buzzerPin = 9;
const int led1 = 6;
const int led2 = 8;
const int led3 = 7;

enum Proximidade {
  LONGE,
  MEDIA,
  PERTO
};

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(buzzerPin, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  float dist = medirDistancia();
  Proximidade estado = avaliarProximidade(dist);

  mostrarDistancia(dist);
  atualizarLeds(estado);
  ativarAlarme(estado);

  if (dist > 20) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
}

float medirDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracao = pulseIn(echoPin, HIGH, 30000); // timeout 30ms
  return duracao > 0 ? (duracao * 0.0343) / 2 : -1;
}

Proximidade avaliarProximidade(float d) {
  if (d < 0) return LONGE; // distância inválida
  if (d < 5) return PERTO;
  if (d < 20) return MEDIA;
  return LONGE;
}

void mostrarDistancia(float d) {
  Serial.print("Distância: ");
  if (d < 0) Serial.println("Sem leitura");
  else {
    Serial.print(d);
    Serial.println(" cm");
  }
}

void atualizarLeds(Proximidade estado) {
  digitalWrite(led1, estado >= LONGE);
  digitalWrite(led2, estado >= MEDIA);
  digitalWrite(led3, estado == PERTO);
}

void ativarAlarme(Proximidade estado) {
  switch (estado) {
    case PERTO:
      tone(buzzerPin, 1000); // som contínuo
      delay(100);
      break;
    case MEDIA:
      tone(buzzerPin, 1000);
      delay(100);
      noTone(buzzerPin);
      delay(300);
      break;
    case LONGE:
      noTone(buzzerPin);
      delay(500);
      break;
  }
}
