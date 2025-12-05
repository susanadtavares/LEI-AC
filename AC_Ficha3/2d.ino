const int trigPin = 5;
const int echoPin = 4;
const int buzzerPin = 9;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  int distance = duration > 0 ? duration * 0.034 / 2 : -1;

  if (distance == -1) {;
    noTone(buzzerPin);
  } else {
    if (distance < 5) {
      tone(buzzerPin, 1000);
    } else if (distance < 15) {
      tone(buzzerPin, 1000);
      delay(100);
      noTone(buzzerPin);
      delay(100);
    } else if (distance < 30) {
      tone(buzzerPin, 1000);
      delay(200);
      noTone(buzzerPin);
      delay(200);
    } else if (distance < 50) {
      tone(buzzerPin, 1000);
      delay(400);
      noTone(buzzerPin);
      delay(400);
    } else {
      noTone(buzzerPin);
    }
  }

  delay(50);
}
