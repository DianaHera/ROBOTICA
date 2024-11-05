#include <Arduino.h>

// Pini pentru LED-uri si butoane
const int redPin = 6;
const int greenPin = 5;
const int bluePin = 4;
const int start_stopButton = 3;
const int difficultyButton = 2;

// Stare buton start/stop
bool startGame = false;
bool lastStartButtonState = HIGH;
bool buttonPressed = false;
unsigned long lastDebounceTimeStart = 0;
const unsigned long debounceDelayStart = 50;

// Dificultate si interval de cuvinte
enum Difficulty {EASY, MEDIUM, HARD};
Difficulty currentDifficulty = EASY;
unsigned long wordInterval = 10000;

// Dicționar cuvinte
const char* words[] = {"apple", "banana", "orange", "grape", "lemon", "pear", "peach", "cherry", "mango", "melon"};
const int wordCount = sizeof(words) / sizeof(words[0]);

// Variabile pentru joc
unsigned long lastWordChangeTime = 0;
unsigned long startTime = 0;
const unsigned long roundDuration = 30000;
String userInput = "";
String currentWord = "";
int correctWordCount = 0;
bool allowNewInput = true;

void setup() {
    // Configurare pini
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    pinMode(start_stopButton, INPUT_PULLUP);
    pinMode(difficultyButton, INPUT_PULLUP);
    Serial.begin(9600);

    // RandomSeed pe un pin analogic
    randomSeed(analogRead(A0));

    // LED in alb (repau)
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, HIGH);
}

void startRound() {
    Serial.println("Incepem runda in:");
    for (int i = 3; i > 0; i--) {
        digitalWrite(redPin, HIGH);
        digitalWrite(greenPin, HIGH);
        digitalWrite(bluePin, HIGH);
        delay(500);
        digitalWrite(redPin, LOW);
        digitalWrite(greenPin, LOW);
        digitalWrite(bluePin, LOW);
        delay(500);
        Serial.println(i);
    }

    // Initializare runda
    startTime = millis();
    lastWordChangeTime = millis();
    correctWordCount = 0;
    allowNewInput = true;
    currentWord = words[random(wordCount)];
    Serial.print("Cuvant: ");
    Serial.println(currentWord);

    // LED verde (inceput runda)
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
}

void stopGame() {
    Serial.println("Joc oprit.");
    Serial.print("Cuvinte corecte: ");
    Serial.println(correctWordCount);
    startGame = false;
    userInput = "";
    allowNewInput = false;

    // LED alb (repau)
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, HIGH);
}

void handleStartButton() {
    int readingStartButton = digitalRead(start_stopButton);

    // Debounce pentru start/stop
    if (readingStartButton != lastStartButtonState) {
        lastDebounceTimeStart = millis();
    }

    if ((millis() - lastDebounceTimeStart) > debounceDelayStart) {
        if (readingStartButton == LOW && !buttonPressed) {
            buttonPressed = true;

            if (!startGame) {
                startGame = true;
                startRound();
            } else {
                stopGame();
            }
        } else if (readingStartButton == HIGH) {
            buttonPressed = false;
        }
    }

    lastStartButtonState = readingStartButton;
}

void changeDifficulty() {
    switch (currentDifficulty) {
        case EASY:
            currentDifficulty = MEDIUM;
            wordInterval = 7000;
            Serial.println("Dificultate MEDIE");
            break;
        case MEDIUM:
            currentDifficulty = HARD;
            wordInterval = 5000;
            Serial.println("Dificultate GREU");
            break;
        case HARD:
            currentDifficulty = EASY;
            wordInterval = 10000;
            Serial.println("Dificultate USOR");
            break;
    }
}

void handleDifficultyButton() {
    if (!startGame) {
        int readingDifficultyButton = digitalRead(difficultyButton);
        static bool lastDifficultyButtonState = HIGH;

        // Debounce pentru dificultate
        if (readingDifficultyButton == LOW && lastDifficultyButtonState == HIGH) {
            changeDifficulty();
        }
        lastDifficultyButtonState = readingDifficultyButton;
    }
}

void generateNewWord() {
    currentWord = words[random(wordCount)];
    Serial.print("Cuvant: ");
    Serial.println(currentWord);
    lastWordChangeTime = millis();
    allowNewInput = true;
}

void loop() {
    // Gestionare butoane
    handleStartButton();
    handleDifficultyButton();

    // Opreste jocul daca timpul s-a terminat
    if (startGame && (millis() - startTime >= roundDuration)) {
        Serial.println("Timpul a expirat! Runda s-a incheiat.");
        stopGame();
    }

    // Citire input utilizator
    if (startGame && allowNewInput && Serial.available() > 0) {
        char incomingChar = Serial.read();
        
        if (incomingChar == '\n' || incomingChar == '\r') {
            userInput.trim();

            if (userInput.equalsIgnoreCase(currentWord)) {
                Serial.println("Corect!");
                correctWordCount++;
                digitalWrite(redPin, LOW);
                digitalWrite(greenPin, HIGH);
                digitalWrite(bluePin, LOW);
                userInput = "";
                allowNewInput = false;
                generateNewWord();
            } else if (userInput != "") {
                Serial.println("Gresit! Incearca din nou.");
                digitalWrite(redPin, HIGH);
                digitalWrite(greenPin, LOW);
                digitalWrite(bluePin, LOW);
            }
            
            userInput = "";
        } else {
            userInput += incomingChar;
        }
    }

    // Generare cuvant nou daca intervalul a expirat
    if (startGame && (millis() - lastWordChangeTime >= wordInterval)) {
        generateNewWord();
        digitalWrite(redPin, LOW);
        digitalWrite(greenPin, HIGH);
        digitalWrite(bluePin, LOW);
    }
}

