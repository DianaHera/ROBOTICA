# Quick Time Game
- Coechipier: Stefan Ana-Maria -

## Descriere
Această temă constă în dezvoltarea unui joc competitiv de reflex pentru doi jucători, în care participanții concurează pentru a obține cel mai mare scor, testându-și viteza de reacție. Proiectul trebuie realizat de echipe formate din două persoane.

Fiecare jucător are un set propriu de butoane și LED-uri, iar jocul se desfășoară pe parcursul mai multor runde. Scopul fiecărui jucător este să apese cât mai rapid butonul care corespunde culorii afișate de LED-ul RGB alocat echipei sale. Punctajul fiecărui jucător va fi afișat și actualizat în timp real pe un ecran LCD, iar la sfârșitul jocului jucătorul cu cel mai mare punctaj va fi declarat câștigător.

## Componente Necesare
- **6x LED-uri** (două grupuri de câte 3 LED-uri, fiecare grup având LED-uri de culori diferite)
- **2x LED RGB** (câte unul pentru fiecare jucător)
- **7x butoane** (câte 3 pentru fiecare jucător)
- **1x ecran LCD**
- **1x servomotor**
- **2x breadboard**
- **Fire de legătură**
- **2x Arduino Uno**
- **1x buzzer**
- **1x potentiometru**
- **Rezistoare**

## Flow-ul Jocului
### 1. Inițializare
La pornire, ecranul LCD afișează un mesaj de bun venit. Jocul poate fi început prin apăsarea unui buton. Există flexibilitate în alegerea modului de start, astfel:

- **Orice buton poate porni jocul.**
- **Un buton specific desemnat** – un buton clar marcat pe breadboard pornește jocul.
- **Buton dedicat suplimentar** – se poate adăuga un buton special pentru pornirea jocului.

### 2. Desfășurarea Rundelor
- Fiecare jucător are trei butoane, fiecare asociat unui LED de o culoare distinctă, și un LED RGB.
- În fiecare rundă, jucătorul activ va vedea LED-ul RGB aprins într-o culoare corespunzătoare unuia dintre butoanele sale. Jucătorul trebuie să apese cât mai rapid butonul corect pentru a câștiga puncte. Cu cât reacționează mai repede, cu atât scorul este mai mare.
- După fiecare rundă, LCD-ul afișează punctajul actualizat al ambilor jucători.
- Pe parcursul jocului, ecranul LCD continuă să afișeze scorurile jucătorilor.

### 3. Finalizarea Jocului
- Servomotorul se rotește în timpul jocului pentru a indica progresul. O rotație completă marchează sfârșitul jocului, iar viteza rotației este determinată de echipă.
- La final, LCD-ul afișează câștigătorul și scorul final pentru câteva secunde, după care revine la mesajul de bun venit.

## Detalii Tehnice
### 1. Comunicare SPI (2.5 puncte)
- Din cauza numărului mare de legături necesare, două plăci Arduino Uno sunt necesare pentru acest proiect, comunicând între ele prin SPI.
- Arduino-ul master controlează ecranul LCD, servomotorul și gestionează logica jocului, inclusiv scorul și starea LED-urilor.
- Arduino-ul slave gestionează butoanele și LED-urile, primind instrucțiuni de la master și trimițând înapoi informații despre butoanele apăsate.

### 2. Butoane (2 puncte)
- Modul de pornire al jocului poate fi ales din următoarele variante:
  - Orice buton începe jocul.
  - Un buton specific începe jocul (trebuie să fie clar marcat pe breadboard).
  - Un buton dedicat suplimentar poate fi utilizat exclusiv pentru pornirea jocului.
- Pe durata jocului, butoanele trebuie să funcționeze doar pentru controlul jocului, fără a reseta progresul.
- Doar butoanele jucătorului activ vor avea efect în rundă.
- Deoarece chiar și cu două plăci Arduino numărul de pini este limitat, butoanele vor fi multiplexate folosind rezistențe (consultați [tutorialul de multiplexare](https://www.youtube.com/watch?v=Y23vMfynUJ0)).

### 3. LED-uri (1 punct)
- Fiecare buton este asociat cu un LED de culoare distinctă, care va fi aprins pentru a indica butonul corespunzător.
- LED-ul RGB se va aprinde într-una dintre cele trei culori corespunzătoare butoanelor.
- LED-ul RGB va rămâne stins când nu este runda jucătorului.

### 4. LCD (1 punct)
- Pentru a controla LCD-ul, folosiți biblioteca `LiquidCrystal`.
- Setarea luminozității și contrastului trebuie să permită o vizibilitate bună a textului afișat.
- Liniile de date ale LCD-ului vor fi conectate la pinii D4-D7.
- LCD-ul va afișa permanent scorurile jucătorilor pe durata jocului.

### 5. Servomotor (1 punct)
- Servomotorul începe de la poziția de 0 grade și se rotește în sens antiorar pentru a indica progresul timpului.
- Valoarea trimisă către servomotor este absolută, deci nu este relativă la poziția curentă. Biblioteca `Servo.h` poate fi utilizată pentru acest control.

## Elemente Personalizabile
- **Punctaj:** Echipelor le este permis să stabilească cum variază punctajul în funcție de viteza de reacție.
- **Timp între runde:** Poate fi introdus un interval de pregătire între runde sau acestea pot avea loc una după alta pentru a crește dificultatea.
- **Durata jocului:** Echipelor le revine sarcina de a decide cât timp durează fiecare joc, controlând viteza de rotație a servomotorului.

