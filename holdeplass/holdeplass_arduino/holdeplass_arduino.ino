int turnOn = 4;
int turnOff = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(turnOn, INPUT);
  pinMode(turnOff, INPUT);
  Serial.write(0); //Av en eller anne grunn er ting mer stabilt når man starter med å sende en byte
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(turnOn) == HIGH) {
    Serial.write(100);
    delay(1000); //vent paa at brukeren slipper knappen (her trengs debounce)
  } else if (digitalRead(turnOff) == HIGH) {
    Serial.write(200); 
    delay(1000); //vent paa at brukeren slipper knappen (her trengs debounce)
  } 
}
