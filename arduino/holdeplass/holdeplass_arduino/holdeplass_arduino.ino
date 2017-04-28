#include <SoftwareSerial.h>

int WIFI_turnOn = 10;
int WIFI_turnOff = 11;

int piezo = 3;

SoftwareSerial esp8266(5, 6); //RX TX

void setup() {
  // put your setup code here, to run once:
  esp8266.begin(115200);
  Serial.begin(9600);
  pinMode(WIFI_turnOn, INPUT);
  pinMode(WIFI_turnOff, INPUT);
  pinMode (piezo, OUTPUT);
  Serial.println("startet");
  esp8266.write(1); //Av en eller anne grunn er ting mer stabilt når man starter med å sende en byte
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(WIFI_turnOn) == HIGH) {
    esp8266.write(100);
    Serial.println("trykket 1");
    tone(piezo, 880);
    delay(1000); //vent paa at brukeren slipper knappen (her trengs debounce)
    noTone(piezo);
  } else if (digitalRead(WIFI_turnOff) == HIGH) {
    esp8266.write(200); 
    Serial.println("trykket 2");
    tone(piezo, 417);
    delay(1000); //vent paa at brukeren slipper knappen (her trengs debounce)
    noTone(piezo);
  } 
}
