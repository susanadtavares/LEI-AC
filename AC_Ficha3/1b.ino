#define LDRpin A0
#define LEDpin 11
int LDRValue = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(LEDpin, OUTPUT);
}

void loop()
{
  LDRValue = analogRead(LDRpin);
  Serial.println(LDRValue);

  if (LDRValue > 150) {
    digitalWrite(LEDpin, HIGH);
  } else {
    digitalWrite(LEDpin, LOW);
  }
  
  delay(5000);
}
