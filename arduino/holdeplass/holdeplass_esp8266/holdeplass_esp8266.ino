#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

const int ON = 100;
const int OFF = 200;

int incomingByte = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  delay(1000);
  WiFiMulti.addAP("hubbub", "hubbub17"); //sett inn SSID og passord her
}

void loop() {
  // put your main code here, to run repeatedly:
  if (WiFiMulti.run() == WL_CONNECTED) {

    if (Serial.available() > 0) {
      incomingByte = Serial.read();

      switch (incomingByte) {
        case ON:
          sendOn();
          break;
        case OFF:
          sendOff();
          break;
        default:
          blink1();
          blink1();
          blink1();
      }
    }
    
  } else {
    errorBlink();
  }

}

void sendOn() {
  //Blink 1 gang
  blink1();
  connectHTTP("http://95.85.58.5:8080/call");

}

void sendOff() {
  //Blink 2 ganger
  blink1();
  blink1();
  connectHTTP("http://95.85.58.5:8080/reset");

}

void connectHTTP(String adresse) {
  HTTPClient http;
  http.begin(adresse);
  http.GET();
  http.end();
  blink1();

}

void errorBlink() {
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
}

void blink1() {
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
}

