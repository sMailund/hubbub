#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //i tilfelle kommunikasjon med aruduino skal brukes
  pinMode(LED_BUILTIN, OUTPUT);

  delay(1000);
  WiFiMulti.addAP("hubbub", "hubbub17"); //SSID og passord
}

void loop() {
  // put your main code here, to run repeatedly:
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    //Koble til
    HTTPClient http;
    http.begin("http://95.85.58.5:8080/status"); //adresse for aa sjekke status
    int httpCode = http.GET(); //koble til og les av resultat

    //behandle svar
    if (httpCode > 0) {
      String svar = http.getString();
      if (svar.equals("1")) {
        //bussen er tilkalt
        digitalWrite(LED_BUILTIN, LOW); //HIGH og LOW er omvendt paa inbygd LED
        onTilkalt();
      } else if (svar.equals("0")) {
        //bussen er IKKE tilkalt
        digitalWrite(LED_BUILTIN, HIGH);
      } else {
        intervalBlink(500); //blink for serverside feil
      }
    } else {
      intervalBlink(500); //blink for serverside feil
    }

    http.end();
  } else {
    intervalBlink(100); //blink raskt for tilkoblingsfeil
  }

  //det er ikke noe poeng aa sjekke oftere enn en gang i sekundet
  //det bare bruker opp nettverk, saa vent litt
  delay(1000); 
}

void onTilkalt() {
  //placeholder
  //kalles naar bussen er tilkalt
  //her ville tingene for aa interface med systemet paa bussen vaert
}

//blink flere ganger i satt hastighet, betyr at noe er feil
void intervalBlink(int tid) {
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(tid);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(tid);
  }
}

