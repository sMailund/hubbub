#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>

MFRC522 rfid(9, 8); // instans av RFID-klasse i driver. Parametre er pins.
SoftwareSerial esp8266(5, 6); //instans av ESP8266-kommunikator (RX TX)

int WIFI_turnOn = 10;
int WIFI_turnOff = 11;
int piezo = 3;

boolean kortAktivert = false;

void setup() {
  // put your setup code here, to run once:
  esp8266.begin(115200);
  Serial.begin(9600);
  
  //init RFID
  SPI.begin(); // Init SPI bus
  pinMode(9, OUTPUT);
  rfid.PCD_Init(); // Init MFRC522 
  
  //init ESP8266
  pinMode(WIFI_turnOn, INPUT);
  pinMode(WIFI_turnOff, INPUT);
  esp8266.write(1); //Modulen oppfører seg mer stabilt hvis den faar en byte naar programmet starter
  
  pinMode (piezo, OUTPUT);
  Serial.println("startet");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  sjekkKort(); //sjekk om kort er paa plass
  
  if (kortAktivert) {
    lyttTilKnapper();
  }
  
}

void lyttTilKnapper() {
  if (digitalRead(WIFI_turnOn) == HIGH) {
    kortAktivert = false; //deaktiver knappene igjen
    esp8266.write(100); //send byte med verdi 100 til ESP8266 (leses av modulen)
    Serial.println("trykket 1");
    tone(piezo, 880); //spill av tone
    delay(1000); //vent paa at brukeren slipper knappen (her trengs debounce)
    noTone(piezo); //skru av tone
  } else if (digitalRead(WIFI_turnOff) == HIGH) {
    kortAktivert = false; //deaktiver knappene
    esp8266.write(200); //send byte med verdi 200 til ESP8266 (leses av modulen)
    Serial.println("trykket 2");
    tone(piezo, 417); //spill av tone
    delay(1000); //vent paa at brukeren slipper knappen (her trengs debounce)
    noTone(piezo); //skru av tone
  } 
}

void sjekkKort(){
  //kortet sjekker ikke ID som leses i denne iterasjonen, men aksepterer alle RFID-kort
  
  //se etter kort:
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;

  //koden som skjer naar kort brukes
  kortAktivert = true; //aktiver knappene
  
  //"debounce" paa kort. du kan holde kortet på så lenge du vil
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  rfid.PICC_HaltA();
}

