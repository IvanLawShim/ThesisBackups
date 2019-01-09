#include <ESP8266HTTPClient.h>
#include <FirebaseArduino.h>
#include <Firebase.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "test-fap.firebaseio.com"
#define FIREBASE_AUTH "pQuEvebLvW150ylIDZKPX4HhOltV1e3LdUQHwo1K"
#define WIFI_SSID "OPPO A3s"
#define WIFI_PASSWORD "12345678"

#define G1 D0
#define G2 D2
#define G3 D4
#define S1 D1
#define S2 D3

void setup() {
  // put your setup code here, to run once:
  pinMode(G1, OUTPUT);
  pinMode(G2, OUTPUT);
  pinMode(G3, OUTPUT);
  pinMode(S1, INPUT_PULLUP);
  pinMode(S2, INPUT_PULLUP);
//  digitalWrite(LED,0);
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(5000);
  }
  Serial.println();
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setInt("LEDStatus",0);
  Firebase.setString("WaterStatus", "Loading.");
}

void loop() {
  // put your main code here, to run repeatedly:
  int x,y;
  x = digitalRead(S1);
  y = digitalRead(S2);

  if (x==HIGH && y==HIGH){
    digitalWrite(G1, LOW);
    digitalWrite(G2, LOW);
    digitalWrite(G3, HIGH);
    Firebase.pushString("WaterStatus", "Filling in with water.");
  }
  if (x==LOW && y==HIGH){
    digitalWrite(G1, LOW);
    digitalWrite(G2, HIGH);
    digitalWrite(G3, LOW);
    Firebase.pushString("WaterStatus", "Stable Water Level.");
  }
  if (x==LOW && y==LOW){
    digitalWrite(G1, HIGH);
    digitalWrite(G2, LOW);
    digitalWrite(G3, LOW);
    Firebase.pushString("WaterStatus", "Removing water.");
  }
  
//  if(Firebase.getInt("LEDStatus")){
//    digitalWrite(LED,HIGH);
//  }
//  else{
//    digitalWrite(LED,LOW);
//  }
//
//  if(Firebase.failed()){
//    Serial.print("setting /number failed:");
//    Serial.println(Firebase.error());
//    return;
//  }

  delay(30000);
}
