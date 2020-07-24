#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 0
#define SS_PIN 2

MFRC522 mfrc522(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

void dump_byte_array(byte *buffer, byte bufferSize){
  for (byte i = 0; i < bufferSize; i++){
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

void setup(){
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();

  for (byte i = 0; i < 6; i++){
    key.keyByte[i] = 0xFF;
  }

  Serial.println(F("Put the RFID infront off the scanner"));
  dump_byte_array(key.keyByte, MFRC522::MF_KEY_SIZE);
  Serial.println();
}

void loop(){
  if ( ! mfrc522.PICC_IsNewCardPresent())
    return;

  if (mfrc522.PICC_ReadCardSerial()){
    Serial.print(F("Card ID: "));
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size); 
    Serial.println();
  }
  
  
  
}
