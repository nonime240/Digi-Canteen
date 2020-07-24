#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "nodemcu-test-6a3fc.firebaseio.com"
#define FIREBASE_AUTH "1gFcr16y3dI3CHinRhshjLDLUoZpUTBkUhuPmX0c"
 
#define WIFI_SSID "limanto"
#define WIFI_PASS "220422101509"

FirebaseData RFID;

FirebaseJson json;

String path;

void setup() {
  Serial.begin(115200);

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

String n = "user";
int i =0; 

void loop() {
  
//  if (Firebase.getInt(RFID, path)){
//    Serial.println(RFID.intData());
//  } 
//  else{
//    Serial.println(RFID.errorReason());
//  }
//  delay(5000);
//  
  path = "/test/int/" + i;
  RFID.pushName("nama");
  Firebase.pushString(RFID, path, n);
  delay(2000);

  Serial.print(RFID.pushName());
  Serial.print(" : ");
  path = path + "/" + RFID.pushName();
  if (Firebase.getString(RFID, path)){
    Serial.println(RFID.stringData());
  } 
  else{
    Serial.println(RFID.errorReason());
  }
  delay(5000);
  i++;
}
