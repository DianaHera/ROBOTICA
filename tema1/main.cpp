#include <Arduino.h>

//definire pini RGB (6 și 4), pini încărcare și butoane
const int redPin = 6;  
const int greenPin = 5; 
const int led1 = 10;  
const int led2 = 9;  
const int led3 = 8; 
const int led4 = 7; 
const int startButtonPin = 3;
const int stopButtonPin = 2;

//variabila pentru starea statie
bool isStationAvailable = true;
bool isCharging = false;  //variabila pentru a verifica incarcarea

//incarcare
int currentLevel = 0; //nivelul de incarcare(merge de la 0 la 4)
unsigned long lastUpdate = 0; //ultima actualizare
const unsigned long interval = 3000; 

//variabile buton stop
unsigned long stopButtonPressTime = 0; //momentul la care este apasat
const unsigned long longPressDuration = 1000; //durata de 1 sec pentru o apasare lunga

//variabile animare leduri
unsigned long blinkStartTime = 0; //inceput blink
const unsigned long blinkInterval = 500; //interval blink
int blinkCount[4] = {0, 0, 0, 0}; //contor pentru fiecare led
bool ledFinished[4] = {false, false, false, false}; //verificare daca ledurile sunt aprinse
bool isBlinking = false; //verif daca ledurile sunt in starea blink

int getLEDFromIndex(int index) {
  switch (index) {
    case 0: return led1;
    case 1: return led2;
    case 2: return led3;
    case 3: return led4;
  }
  return led1; 
}
void updateLED(bool available) {
  if (available) {
    //statia e libera
    digitalWrite(redPin, LOW);  
    digitalWrite(greenPin, HIGH); 
  } else {
    //statia e ocupata
    digitalWrite(redPin, HIGH);  
    digitalWrite(greenPin, LOW); 
  }
}
void setup() {
  //setare pinuri pe iesire
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  //setare pinuri butoane
  pinMode(startButtonPin, INPUT_PULLUP);  
  pinMode(stopButtonPin, INPUT_PULLUP);

  //statie e libera la inceput
  updateLED(isStationAvailable);
  
}
//functia pentru animatia finala cu cele 3 clipiri
void animatie() {
  for (int i = 0; i < 3; i++) {  
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    delay(500);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    delay(500);
  }
}
void updateBlinkingLEDs() {
  unsigned long currentMillis = millis();
  if (currentMillis - blinkStartTime >= blinkInterval) {
    blinkStartTime = currentMillis; //resetam timpul de inceput pentru blink

    //led urile fac blink in functie de starea lor
    for (int i = 0; i < 4; i++) {
      if (!ledFinished[i] && (i == 0 || ledFinished[i - 1])) { //verificam starea ledului anterior
        blinkCount[i]++;
        if (blinkCount[i] < 4) {
          //blink
          digitalWrite(getLEDFromIndex(i), blinkCount[i] % 2 == 0 ? HIGH : LOW);
        } else {
          digitalWrite(getLEDFromIndex(i), HIGH);
          ledFinished[i] = true;
        }
      }
    }

    //verificam daca toate ledurile sunt aprinse
    if (ledFinished[0] && ledFinished[1] && ledFinished[2] && ledFinished[3]) {
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      delay(1000); //pauza scurta de 1sec

      //rulam animatia finala
      animatie();

      //se opreste incarcarea
      isCharging = false;
      isStationAvailable = true; //statia e libera
      updateLED(isStationAvailable); //actualizam indicatorul statiei
    }
  }
}

void resetBlinkData() {
  for (int i = 0; i < 4; i++) {
    blinkCount[i] = 0;
    ledFinished[i] = false;
  }
  blinkStartTime = millis();
}
void forceStopCharging() {
  //oprim incarcarea
  isCharging = false;

  //stingem ledurile
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);

  animatie();

  //resetam statia
  isStationAvailable = true;
  updateLED(isStationAvailable);
}
void loop() {
  //verificam daca a fost butonul de start apasat
  if (digitalRead(startButtonPin) == LOW && isStationAvailable && !isCharging) {
    delay(50);  //debounce simplu
    if (digitalRead(startButtonPin) == LOW) {  
      //incepem incarcarea
      isCharging = true;
      isStationAvailable = false;
      currentLevel = 0; //resetam nivelul de incarcare
      resetBlinkData(); //resetam datele de blink
      updateLED(isStationAvailable);
    }
  }
  
  //verificam apasarea lunga a butonului de stop
  if (isCharging && digitalRead(stopButtonPin) == LOW) {
    if (stopButtonPressTime == 0) {
      stopButtonPressTime = millis(); //tinem minte momentul apasarii
    }
    //verif daca a fost apasat mai mult de 1 sec
    if (millis() - stopButtonPressTime >= longPressDuration) {
      //oprim incarcarea si afis animatia
      forceStopCharging();
    }
  } else {
    stopButtonPressTime = 0; //resetam timpul
  }

  // daca incarcare a inceput o continuam
  if (isCharging) {
    updateBlinkingLEDs(); //actualizam starea ledurilor
  }
}




