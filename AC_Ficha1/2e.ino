#define LED_PIN 12

int count = 0;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  while(count <= 2) {
    delay(500);
    digitalWrite(LED_PIN, HIGH);
    delay(300);
    digitalWrite(LED_PIN, LOW);
    count++;
  }
  count = 0;
  while(count <= 2) {
    delay(1500);
    digitalWrite(LED_PIN, HIGH);
    delay(300);
    digitalWrite(LED_PIN, LOW);
    count++;
  }
  while(count <= 2) {
    delay(500);
    digitalWrite(LED_PIN, HIGH);
    delay(300);
    digitalWrite(LED_PIN, LOW);
    count++;
  }
  count = 0;
}