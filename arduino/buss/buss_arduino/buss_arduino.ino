#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  delay(1000);
  WiFiMulti.addAP("Kokiri Forest", "mjaumjau");
}

void loop() {
  // put your main code here, to run repeatedly:
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    //Koble til
    HTTPClient http;
    http.begin("http://95.85.58.5:8080/status");
    int httpCode = http.GET();

    if (httpCode > 0) {
      String svar = http.getString();
      if (svar.equals("1")) {
        digitalWrite(LED_BUILTIN, LOW);
      } else if (svar.equals("0")) {
        digitalWrite(LED_BUILTIN, HIGH);
      } else {
        intervalBlink(500);
      }
    } else {
      intervalBlink(500);
    }

    http.end();
  } else {
    intervalBlink(100);
  }

  delay(1000);
}

void intervalBlink(int tid) {
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(tid);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(tid);
  }
}

