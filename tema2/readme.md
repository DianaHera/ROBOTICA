 ## Tema aceasca simuleaza un joc de tipul TypeRacer

  # LED RGB - Indicator de stare:
        Stare de repaus: LED-ul va afișa culoarea albă.
        Numărătoare inversă: La apăsarea butonului de start, LED-ul va clipi timp de 3 secunde, indicând numărătoarea inversă până la începerea rundei.
        Desfășurarea rundei: Dacă textul introdus este corect, LED-ul se aprinde verde.
                             Dacă există o greșeală, LED-ul se aprinde roșu.

  # Butonul Start/Stop:
        Modul de repaus: Dacă jocul este oprit, apăsarea butonului inițiază o nouă rundă, după o numărătoare inversă de 3 secunde.
        În timpul unei runde: Dacă runda este activă, apăsarea butonului o va opri imediat.

  # Butonul de dificultate:
        Schimbarea dificultății: Acest buton ajustează viteza de apariție a cuvintelor și poate fi folosit doar în modul de repaus.
        Ciclare dificultate: La fiecare apăsare, nivelul de dificultate se schimbă între „Easy”, „Medium” și „Hard”.
        Mesaj serial: La schimbarea dificultății, se trimite un mesaj prin portul serial cu textul „Easy/Medium/Hard mode on!” pentru a indica nivelul selectat.
        Tehnică de implementare:
                   Folosiți debouncing și întreruperi pentru gestionarea apăsării butoanelor.
                   Utilizați timere pentru a seta frecvența apariției cuvintelor, în funcție de dificultate.
  # Generarea cuvintelor:
        Dicționar de cuvinte: Se va crea un dicționar pentru selecția cuvintelor.
        Afișare în terminal: În timpul rundei, cuvintele sunt afișate într-o ordine aleatorie în terminal.
        Corectitudine răspuns:
        Dacă utilizatorul introduce corect un cuvânt, un cuvânt nou va apărea imediat.
        Dacă răspunsul este incorect, un nou cuvânt va fi afișat conform intervalului de timp stabilit de nivelul de dificultate.
        Detalii tehnice: Pentru generarea ordinii aleatorii a cuvintelor, folosiți funcția random().

  # Observații generale:
        Durata rundei: O rundă durează 30 de secunde.
        Finalul rundei: La sfârșitul fiecărei runde, în terminal se va afișa numărul total de cuvinte scrise corect de utilizator.

   # Video
       https://youtu.be/wPO5p46tqiE

   # Poze
![Imagine WhatsApp 2024-11-05 la 16 38 47_ecf07d66](https://github.com/user-attachments/assets/6cefc8e3-d56f-4657-a958-8c3707ba7496)

![Imagine WhatsApp 2024-11-05 la 16 38 47_78e281f5](https://github.com/user-attachments/assets/faf0ac05-b4d7-4c1c-93b8-a40944b2af7d)

![Imagine WhatsApp 2024-11-05 la 16 38 47_06971042](https://github.com/user-attachments/assets/1810d0ff-2307-4718-9d2c-33420bc31a8b)
