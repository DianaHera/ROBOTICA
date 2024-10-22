# Cerinte:
În această temă, trebuie simulata o stație de încărcare pentru un vehicul electric folosind LED-uri și butoane. Scopul este coordonarea tuturor componentele așa cum ar funcționa într-o situație reală.

- LED-ul RGB arată dacă stația este disponibilă. Verde înseamnă că stația este liberă, iar roșu indică că este ocupată.
- LED-urile simple simulează încărcarea bateriei, cu patru niveluri: 25% (L1), 50% (L2), 75% (L3) și 100% (L4). Pe măsură ce bateria se încarcă, aceste LED-uri se aprind progresiv la fiecare 3 secunde.
  - LED-ul care arată nivelul curent de încărcare va clipi, cele de dinainte vor rămâne aprinse, iar cele după el vor fi stinse.
  
Funcționalitatea butoanelor:
- Un click scurt pe butonul de start începe încărcarea.
- Dacă apeși butonul de start în timpul încărcării, nu se va întâmpla nimic.
- O apăsare lungă pe butonul de stop (minim 1 secundă) va opri încărcarea și va reseta stația la starea inițială. Dacă butonul de stop este apăsat când stația este liberă, nu va avea niciun efect.

Cum funcționează:
1. Stația pornește în starea "liberă": LED-ul de disponibilitate este verde și niciun LED nu este aprins.
2. Dacă apeși butonul de start, LED-ul de disponibilitate devine roșu, iar încărcarea începe cu LED-ul L1, care va clipi timp de 3 secunde.
3. După ce L1 se aprinde complet, LED-ul L2 începe să clipească pentru a semnala trecerea la 50% și așa mai departe până la 100%.
4. La finalul încărcării, toate LED-urile vor clipi de 3 ori simultan pentru a semnala că s-a terminat procesul, apoi se vor stinge, iar LED-ul de disponibilitate revine la verde.

Dacă apeși butonul de stop pentru mai mult de o secundă în timpul încărcării, procesul se va opri imediat, iar toate LED-urile vor clipi de 3 ori pentru a semnala oprirea. LED-ul de disponibilitate va reveni la verde.

# Componente:
-4x LED-uri (pentru a simula procentul de încărcare)
-1x LED RGB (pentru starea de liber sau ocupat)
-2x Butoane (pentru start încărcare și stop încărcare)
-9x Rezistoare (7x 220/330ohm, 2x 1K)
-Breadboard
-Fire de legătură
# Schema electrica:

![Captură de ecran 2024-10-22 122005](https://github.com/user-attachments/assets/4eb210e0-0b15-4708-bcf4-642c9b8d387a)



# Montaj:
![Imagine WhatsApp 2024-10-22 la 18 31 00_33b1f797](https://github.com/user-attachments/assets/0c007d90-8d95-4e81-9582-f0b667eb04e5)
![Imagine WhatsApp 2024-10-22 la 18 30 59_7184dfd8](https://github.com/user-attachments/assets/72a6a723-836d-4368-8b8b-aca822d157cd)
![Imagine WhatsApp 2024-10-22 la 18 30 59_527df550](https://github.com/user-attachments/assets/8f6e730b-c835-4894-b239-61cd45686b3c)
![Imagine WhatsApp 2024-10-22 la 18 30 58_40746e20](https://github.com/user-attachments/assets/167dc5cd-2b2f-4f64-9754-c538dc17facf)
![Imagine WhatsApp 2024-10-22 la 18 31 00_ae6fb745](https://github.com/user-attachments/assets/e84ea7b7-55ff-46d4-ada6-32c717872ca7)



# Video:
https://youtube.com/watch/oXaNaPBI01Y?feature=share
