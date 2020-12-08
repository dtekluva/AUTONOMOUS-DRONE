//Original source code : http://enrique.latorres.org/2017/10/17/testing-lolin-nodemcu-v3-esp8266/
//Download LoLin NodeMCU V3 ESP8266 Board for Arduino IDE (json) : http://arduino.esp8266.com/stable/package_esp8266com_index.json

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
ESP8266WiFiMulti WiFiMulti;

////////////// VARIABLES BEGIN ////////////////

const char* ssid     = "Spectranet-LT";
const char* password = "123456780125";

String ip_address = "192.168.8.101:8000";
String device_code = "003";

///////////////////////////////////

String base_url = "http://" + ip_address + "/main/update/";
String url = base_url + device_code;

///////////////////////////////////
//          DO NOT TAMPER        //
int Buzzer = 12;  // Digital pin D6
int sensor = 13;  // Digital pin D7
///////////////////////////////////

///////////// VARIABLES ENDING ///////////////


void setup() {
  Serial.begin(115200);
  pinMode(sensor, INPUT);   // declare sensor as input
  pinMode(Buzzer, OUTPUT);  // declare LED as output

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(500);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);
};

void loop() {

  long state = digitalRead(sensor);
    if(state == HIGH) {
      digitalWrite (Buzzer, HIGH);
      Serial.println("Motion detected!");
      Serial.println("1!");
      send_alert();
      delay(500);
    }
    else {
      digitalWrite (Buzzer, LOW);
      Serial.println("Motion absent!");
      Serial.println("0!");
      delay(500);
      }
}



void send_alert() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, url)) {  // HTTP


      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }

  delay(500);
}










////Original source code : http://enrique.latorres.org/2017/10/17/testing-lolin-nodemcu-v3-esp8266/
////Download LoLin NodeMCU V3 ESP8266 Board for Arduino IDE (json) : http://arduino.esp8266.com/stable/package_esp8266com_index.json
//#include <ESP8266WiFi.h>
////const char* ssid = "Spectranet-LT";
////const char* password = "123456780124";
////int ledPin = 2; // Arduino standard is GPIO13 but lolin nodeMCU is 2 http://www.esp8266.com/viewtopic.php?f=26&t=13410#p61332
////WiFiServer server(80);
//
////
////
//int Status = 12;  // Digital pin D6
//int sensor = 13;  // Digital pin D7
//void setup() {
//  Serial.begin(115200);
//  pinMode(sensor, INPUT);   // declare sensor as input
//  pinMode(Status, OUTPUT);  // declare LED as output
//}
//void loop() {
//
//  long state = digitalRead(sensor);
//    if(state == HIGH) {
//      digitalWrite (Status, HIGH);
//      Serial.println("Motion detected!");
//      Serial.println("1!");
//      delay(500);
//    }
//    else {
//      digitalWrite (Status, LOW);
//      Serial.println("Motion absent!");
//      Serial.println("0!");
//      delay(500);
//      }
//}
////
