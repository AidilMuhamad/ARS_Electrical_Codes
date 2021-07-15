#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>

#define SS_PIN 21
#define RST_PIN 22
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.ll

void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( !mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  
  Serial.println("\t|-----------|------------------------|");
  Serial.print("\t| UID tag : | ");
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  content.toUpperCase();
  if (content.substring(1) == "3A 43 6B 81")
  {
    Serial.println("           |");
    Serial.println("\t|-----------|------------------------|");
    Serial.println("\t| Message : | Akses Di Terima        |");
    Serial.println("\t|-----------|------------------------|");
    Serial.println("\t| Name    : |                        |");
    Serial.println("\t|-----------|------------------------|\n\n");
    delay(1000);
  }
 else{
    Serial.println("           |");
    Serial.println("\t|-----------|------------------------|");
    Serial.println("\t| Message : | Akses Di Tolak         |");
    Serial.println("\t|-----------|------------------------|");
    Serial.println("\t| Name    : | ******                 |");
    Serial.println("\t|-----------|------------------------|\n\n");
    delay(1000);
  }
}
