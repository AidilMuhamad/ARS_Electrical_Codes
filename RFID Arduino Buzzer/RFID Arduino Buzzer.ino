#include "SPI.h"
#include "MFRC522.h"

#define SS_PIN 10
#define RST_PIN 5
#define LED_PIN1 8
#define LED_PIN2 4
#define buzzer 2

MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.println("I am waiting for card...");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  // Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }
  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
      (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
      String(rfid.uid.uidByte[i], HEX) +
      (i != 3 ? ":" : "");
  }

  strID.toUpperCase();
  Serial.print("Tap card key: ");
  Serial.println(strID);
  delay(1000);

  if (strID.indexOf("7A:74:AB:1A") >= 0) {  //put your own tap card key;
    Serial.println("********");
    Serial.println("*Authorised acces*");
    Serial.println("********");
    digitalWrite(LED_PIN1, HIGH);
    delay(1000);
    digitalWrite(LED_PIN1, LOW);
    digitalWrite(LED_PIN2, LOW);
    return;
  }
  else {
    Serial.println("******");
    Serial.println("*Acces denied*");
    Serial.println("******");
    digitalWrite(LED_PIN2, HIGH);
    delay(1000);
    digitalWrite(LED_PIN2, LOW);
    digitalWrite(LED_PIN1, LOW);
    tone(buzzer,1000);
    delay(1000);
    noTone(buzzer);
    delay(1000);
    return;
  }
  
}
