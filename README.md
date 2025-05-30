# Arduino Bluetooth Car 

Acest proiect constă într-o mașinuță controlată prin Bluetooth, folosind un Arduino Uno și un shield L293D pentru controlul a 4 motoare DC. Utilizatorul poate comanda direcția și mișcarea vehiculului de pe telefonul mobil printr-o aplicație compatibilă cu HC-05.

##  Componente hardware

- **Arduino Uno** – unitatea de control principală
- **Shield motoare L293D** – controlează 4 motoare DC
- **4x Motoare DC + roți** – pentru mișcare
- **Modul Bluetooth HC-05** – comunicare serială cu telefonul
- **LED** – semnalizare vizuală în mers înapoi/lateral
- **Buzzer activ** – semnal sonor sincronizat cu LED-ul
- **Baterii 18650 (x4)** – sursa de alimentare portabilă

##  Funcționalitate

- Control complet prin Bluetooth folosind comenzi:
  - `F` – înainte
  - `B` – înapoi
  - `L` – stânga
  - `R` – dreapta
  - `I`, `J`, `K`, `M` – diagonale
  - `S` – stop
  - `T` – test buzzer

- Feedback sonor și vizual:
  - LED + buzzer activat în mers înapoi și la viraje

- Acces direct la registre pentru I/O, PWM, UART
- Fără librării Arduino – programare low-level în C/C++

## Mediu de dezvoltare

- **IDE**: [Visual Studio Code](https://code.visualstudio.com/) + PlatformIO
- **Toolchain**: AVR-GCC
- **Programare și upload**: USB via bootloader Arduino Uno
