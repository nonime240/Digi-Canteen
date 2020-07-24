/*include necessary libraries*/
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <RFID.h>
#include <SPI.h>

//configure Firebase connection
#define FIREBASE_HOST "nodemcu-test-6a3fc.firebaseio.com"
#define FIREBASE_AUTH "1gFcr16y3dI3CHinRhshjLDLUoZpUTBkUhuPmX0c"

//configure WiFi connection
#define WIFI_SSID "limanto"
#define WIFI_PASS "220422101509"

//configure RFID scanner pins
#define SDA 2
#define RST 0
RFID RC522(SDA, RST);

void setup() {
  Serial.begin(115200);

  //start RFID scanner
  SPI.begin();
  RC522.init();
  
  //start WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected : ");
  Serial.println(WiFi.localIP());

  //start Firebase connection
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  //declare a firebase object on a spesific path
  String path = "/Tb_rfid";
  FirebaseObject object = Firebase.get(path);

  //check for card availability
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
    path = "/Tb_rfid/" + rfidID;
    Firebase.pushString(path, "User");
    if (Firebase.failed()){
      Serial.print("setting RFID ID failed : ");
      Serial.println(Firebase.error());
    }

    
  }
  delay(500);
}
  
