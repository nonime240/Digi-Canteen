#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <RFID.h>
#include <SPI.h>

#define FIREBASE_HOST "nodemcu-test-6a3fc.firebaseio.com"
#define FIREBASE_AUTH "1gFcr16y3dI3CHinRhshjLDLUoZpUTBkUhuPmX0c"
 
#define WIFI_SSID "limanto"
#define WIFI_PASS "220422101509"

#define SDA 2
#define RST 0
RFID RC522(SDA, RST);

FirebaseData RFID;

FirebaseJson json;

void setup() {
  Serial.begin(115200);

  SPI.begin();
  RC522.init();

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("\n connecting ");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected : ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}

void loop() {
  String path = "/Tb_rfid";

  if (RC522.isCard())
  {
    //prepare string for card ID
    String rfidId[5], rfidID;
    
    //reads the ID
    RC522.readCardSerial();
    Serial.print("Card detected : ");
    
    //save the ID on an array 
    for(int i=0;i<6;i++)
    {
      rfidId[i] = RC522.serNum[i];
    } 

    //combine the array and print card's ID
    rfidID = rfidId[0] + rfidId[1] + rfidId[2] + rfidId[3] + rfidId[4];
    Serial.println(rfidID);
    Serial.println("\n");
    
    //upload the ID to Firebase real-time DB
    path = "/Tb_rfid/" + rfidID + "/nama";
    if (!Firebase.setString(RFID, path, "User")){
      Serial.print("setting RFID ID failed : ");
      Serial.println(RFID.fileTransferError());
    }

    
  }
  delay(500);
  
}
