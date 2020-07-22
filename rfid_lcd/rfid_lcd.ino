#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <RFID.h>

#define SDA 36
#define RESET 8

int id[5];
int Slave= 53;
int CS= 37;;

// Search the I2C Addressz with an I2C address scanner
LiquidCrystal_I2C lcd(0x3F, 16, 2);
RFID RC522(SDA, RESET);

void setup()
{
  pinMode(Slave, OUTPUT);
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);
  Serial.begin(57600);
  SPI.begin();
  //begin RC522
  RC522.init();
  // initialize the LCD
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
}

void loop()
{
  //detect card
  if (RC522.isCard())
  {
    RC522.readCardSerial();//read RFID Card Serial Number
    lcd.setCursor(0,0);//set lcd cursor to row zero
    lcd.print("Card detected:");//show something to lcd
    lcd.setCursor(0,1);//set lcd cursor to row 1
    
    for(int i=0;i<5;i++)
    {
      id[i] = RC522.serNum[i],HEX;//save serial number to an integer
      lcd.print(id[i]);//show serial number to lcd
      Serial.print(id[i]);
    }
    Serial.println();
    delay(2000);//show id for 3 seconds
    lcd.clear();//clear lcd
  }
}
