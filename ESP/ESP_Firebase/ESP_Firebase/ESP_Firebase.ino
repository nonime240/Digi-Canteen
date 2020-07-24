#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <RFID.h>
#include <SPI.h>

//firebase configuration
#define FIREBASE_HOST "nodemcu-test-6a3fc.firebaseio.com"
#define FIREBASE_AUTH "1gFcr16y3dI3CHinRhshjLDLUoZpUTBkUhuPmX0c"

//WiFi configuration
#define WIFI_SSID "limanto"
#define WIFI_PASS "220422101509"

//RFID-Scanner configuration
#define SDA 2
#define RST 0
RFID RC522(SDA, RST);

void setup() {
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected : ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  SPI.begin();
  RC522.init();
}

void loop() {
  if (RC522.isCard())
  {
    String rfidId[5], rfidID;
    /* If so then get its serial number */
    RC522.readCardSerial();
    Serial.print("Card detected : ");
    for(int i=0;i<6;i++)
    {
      rfidId[i] = RC522.serNum[i];
    } 
    rfidID = rfidId[0] + rfidId[1] + rfidId[2] + rfidId[3] + rfidId[4];
    Serial.println(rfidID);
    Serial.println("\n");

    Firebase.pushString("RFID ID", user);
    if (Firebase.failed()){
      Serial.print("setting RFID ID failed : ");
      Serial.println(Firebase.error());
    }
  }
  delay(500);
}
