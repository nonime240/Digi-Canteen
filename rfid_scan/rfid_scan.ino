/*
PINOUT:
RC522 MODULE    Uno/Nano     MEGA
SDA             D10          D9
SCK             D13          D52
MOSI            D11          D51
MISO            D12          D50
IRQ             N/A          N/A
GND             GND          GND
RST             D9           D8
3.3V            3.3V         3.3V
*/
/* Include the standard Arduino SPI library */
#include <SPI.h>
/* Include the RFID library */
#include <RFID.h>

/* Define the DIO used for the SDA (SS) and RST (reset) pins. */
#define SDA_DIO 2
#define RESET_DIO 0
/* Create an instance of the RFID library */
RFID RC522(SDA_DIO, RESET_DIO); 

void setup()
{ 
  Serial.begin(115200);
  /* Enable the SPI interface */
  SPI.begin(); 
  /* Initialise the RFID reader */
  RC522.init();
}

void loop()
{
  /* Has a card been detected? */
  if (RC522.isCard())
  {
    String rfidId[5], rfidID;
    /* If so then get its serial number */
    RC522.readCardSerial();
    Serial.println("Card detected:");
    for(int i=0;i<6;i++)
    {
      rfidId[i] = RC522.serNum[i];
      Serial.print(rfidId[i]);
    } 
    rfidID = rfidId[0] + rfidId[1] + rfidId[2] + rfidId[3] + rfidId[4];
    Serial.println();
    Serial.println(rfidID);
//    Serial.print(rfidID[4]);
//    Serial.print(rfidID[2]);
//    Serial.print(rfidID[3]);
    Serial.println("\n");
  }
  delay(500);
}
