#include <SPI.h>           // SPI library
#include <SdFat.h>         // SDFat Library
#include <SdFatUtil.h>     // SDFat Util Library
#include <SFEMP3Shield.h>  // Mp3 Shield Library

SdFat sd; //Objekt for aa haandtere sd-kort
SFEMP3Shield MP3player; //Objekt for MP3-spiller

//Konfigurasjon for mp3-spiller
const uint8_t volume = 50; //volum 0=max, 255=lowest (off)
const uint16_t monoMode = 1;  //Mono setting 0=off, 3=max

/* Pin setup */
#define TRIGGER_COUNT 2
const int ledPin = 5; //knapp for LED
const int lydKnapp = 4;  //knapp for aa spille av lyd

//konstanter for lesbarhet
const int ON = 100;
const int OFF = 200;

//variabler for deBounce av knappetrykk;
int clickCount = 0;
unsigned long lastButtonPush = 0;
int debounceDelay = 200;


void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(lydKnapp, INPUT);

  //initialiser sd og mp3
  initSD();
  initMP3Player();
}

void loop() {
  snakkESP(); //kommunikasjon med ESP8266
  snakkMP3(); //kommunikasjon med MP3
}

void snakkESP() {
  //hvis det er noe aa lese
  if (Serial.available() > 0) {
      int incomingByte = Serial.read(); //les av meldingen

      //behandle meldingen
      if (incomingByte == ON) {
        digitalWrite(ledPin, HIGH); //skru LEDen paa hvis bestilt
      } else if (incomingByte == OFF) {
        digitalWrite(ledPin, LOW); //skru av hvis ikke
      }
  }
}

void snakkMP3() {
  //sjekk hvilken knapp som trykkes inn
  if (isClicked(btn1)){
    //hvis det ikke allerede spilles av opplesning, begynn avspilling
    if (!MP3player.isPlaying()){
      MP3player.playTrack(1); //spill av
    }
  }
}

//hentet fra eksempelkode --->
//metode som sjekker om knappen er trykket
boolean isClicked(int pin){
  //sjekker om det har gaatt over debounceDelay med tid siden siste trykk
  if ((millis() - lastButtonPush) >= debounceDelay){
    //hvis ja > sjekk om knapp er trykket inn
    if (digitalRead(pin)){
      //oppdater siste knappetrykk og returner true
      lastButtonPush = millis();
      return true;
    }
  }
  
  //hvis ikke det har gaatt lenge nok eller knappen ikke er trykket inn
  return false;
}

// initSD() initializes the SD card and checks for an error.
void initSD()
{
  //Initialize the SdCard.
  if(!sd.begin(SD_SEL, SPI_HALF_SPEED)) 
    sd.initErrorHalt();
  if(!sd.chdir("/")) 
    sd.errorHalt("sd.chdir");
}

// initMP3Player() sets up all of the initialization for the
// MP3 Player Shield. It runs the begin() function, checks
// for errors, applies a patch if found, and sets the volume/
// stero mode.
void initMP3Player()
{
  uint8_t result = MP3player.begin(); // init the mp3 player shield
  if(result != 0) // check result, see readme for error codes.
  {
    // Error checking can go here!
  }
  MP3player.setVolume(volume, volume);
  MP3player.setMonoMode(monoMode);
}
