#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <SPI.h>
#include <RFID.h>

#define SDA_DIO 2
#define RESET_DIO 0
RFID RC522(SDA_DIO, RESET_DIO);

const char* ssid = "limanto";
const char* password = "220422101509";
const char* host = "192.168.100.10";

void setup(){
  delay(1000);
  Serial.begin(115200);
  SPI.begin();
  RC522.init();
  
  WiFi.mode(WIFI_OFF); //mematikan mode WiFi NODE
  delay(1000);
  WiFi.mode(WIFI_STA); //set mode NODE menjadi Station
  WiFi.begin(ssid, password); //menghubungkan NODE ke AP

  Serial.print("\nConnecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nConnected to ");
  Serial.print(ssid);
  Serial.print("\nIp Address = ");
  Serial.print(WiFi.localIP());
  Serial.println(); 
}

void loop(){
  if (RC522.isCard())
  {
    String rfidId[5], rfidID, stationId, postData;
    RC522.readCardSerial();
    Serial.println("Card detected:");
    for(int i = 0; i < 6; i++)
    {
      rfidId[i] = RC522.serNum[i];
      Serial.print(rfidId[i]); 
    }
    Serial.println();
    Serial.println();
    
    HTTPClient http; //deklarasi obeject dari class HTTPClient

    rfidID = rfidId[0] + rfidId[1] + rfidId[2] + rfidId[3] + rfidId[4];
    stationId = "A1"; //Id untuk NodeMCU
    postData = "&station=" + stationId + "&rfid_id=" + rfidID; 

    http.begin("http://192.168.100.10/ESP_Save_Post_Data/post.php"); //tentukan destinasi POST
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //tentukan tipe konten header

    int httpCode = http.POST(postData); //mengirim POST
    String payload = http.getString(); //menyimpan isi respon

    Serial.println(httpCode); //print kode Return HTTP
    Serial.println(payload); //print isi respon

    http.end();
    delay(500);
  }
}
