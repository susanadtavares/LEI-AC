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
  int brightness = map(LDRValue, 50, 180, 0, 255);
  brightness = constrain(brightness, 0, 255);
  analogWrite(LEDpin, brightness);
  Serial.print("LDR: ");
  Serial.print(LDRValue);
  Serial.print(" | Brilho: ");
  Serial.println(brightness);
  delay(10);
}
