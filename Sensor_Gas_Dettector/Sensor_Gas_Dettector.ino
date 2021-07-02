#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int redLed = 12;
int greenLed = 11;
int buzzer = 10;
int smokeA0 = A0;
// Your threshold value
int sensorThres = 400;
int analogSensor = 0;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  lcd.begin();
  Serial.begin(9600);
}

void loop() {
  analogSensor = analogRead(smokeA0);
  lcd.setCursor(2,0);
  lcd.print("Nilai : " + String(analogSensor));
  
  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    tone(buzzer, 1000, 200);
    lcd.setCursor(0,1);
    lcd.print("Udara Tidak Aman");
  }
  else
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    noTone(buzzer);
    lcd.setCursor(2,1);
    lcd.print("Udara Aman");
  }
  delay(100);
  lcd.clear();
}