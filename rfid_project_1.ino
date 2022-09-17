#include <SPI.h>
#include <MFRC522.h>

#define P_PIN 10
#define D_PIN 9
    
MFRC522 rfid(P_PIN, D_PIN); 

byte uidbadge[4];

void setup() 
{ 
  Serial.begin(9600);
  SPI.begin(); 
  rfid.PCD_Init(); 
}
 
void loop() 
{
  if ( !rfid.PICC_IsNewCardPresent())
    return;  // Initialisé la boucle en absence de badge 
 
  if ( !rfid.PICC_ReadCardSerial())
    return; // Vérification de la présence de badge
 
  for (byte i = 0; i < 4; i++) 
  {
    uidbadge[i] = rfid.uid.uidByte[i];
  }   // Enregistrer l'ID du badge
  
  Serial.println(" L'UID du badge est:"); // Affichage de l'ID du badge
  for (byte i = 0; i < 4; i++) 
  {
    Serial.print(uidbadge[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
