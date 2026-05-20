# Projekto aprašymas
Programa skirta studentų akademinių pasiekimų informacijos apdorojimui. Vartotojas gali rinktis, ar studentų informaciją įveda jis pats, ar informacija yra generuojama automatiškai. Programa leidžia generuoti, nuskaityti studentų failus bei atlikti skirtingus programos veikimo laiko testus. Programos veikimo spartos testavimui naudojami skirtingi konteineriai.

# Naudojimosi instrukcija
1. Nusiklonuokite repozitoriją:
   
   ```
   git clone https://github.com/RokasTverijonas/OOP-1.git
   ```

2. Įsidiekite CMake (Linux(Ubuntu/Debian))

   ```
   sudo apt update
   sudo apt install cmake
   ```

3. Projekto kompiliavimas su CMake
   
   ```
   cd OOP-1
   mkdir build
   cd build
   cmake ..
   make
   ```
4. Paleiskite programą
   
   ```
   ./programa1
   ```
5. Paleiskite testus

   ```
   ./gtestai
   ```

# Kompiuterio specifikacijos:

|       CPU      |  RAM |    SSD     | 
|----------------|------|------------| 
| Intel i5-8265U | 16GB | NVMe 256GB |      
--------------------------------------

# v3.0 rezultatai

## Funkcijos

## `push_back(const T& value)`
Prideda naują elementą į vektoriaus pabaigą.

## `pop_back()`
Pašalina paskutinį vektoriaus elementą.

## `resize(size_t newSize)`
Pakeičia vektoriaus dydį.

## `reserve(size_t new_cap)`
Rezervuoja papildomą atmintį būsimiems elementams.

## `shrink_to_fit()`
Sumažina rezervuotą atmintį iki esamo elementų kiekio.

## std::vector ir Vector Spartos analizė

Testas: tuščias konteineris užpildomas `int` elementais naudojant `push_back()`.

| Elementų sk. | std::vector| Vector   |
|--------------|-----------|-----------|
| 10000       | 0.000707s | 0.000441s | 
| 100000      | 0.006779s | 0.005101s |
| 1000000    | 0.024967s | 0.010072s |
| 10000000   | 0.138236s | 0.112662s |
| 100000000  | 1.276090s | 1.005180s |
----------------------------------------

## Atminties perskirstymų palyginimas
 
Testas: konteineris užpildomas 100,000,000 `int` elementų. Perskirstymas įvyksta kai `capacity() == size()`.
 
| Konteineris | Perskirstymų skaičius |
|-------------|-----------------------|
| std::vector | 28                    |
| Vector      | 28                    |
---------------------------------------

Išvada:

Abu konteineriai atliko **vienodą kiekį perskirstymų (28)**

## Sukurtos Vector klasės naudojimas vietoj std::vector

Testas: Atliekamas konteinerio tyrimas su įvariais studentų kiekiais, naudojant 3 strategiją ir rikiuojant studentus pagal galutinio balo vidurkį

| Studentų sk. | std::vector| Vector   |
|--------------|-----------|-----------|
| 1000         | 0.0196432s| 0.027766s | 
| 10000        | 0.1226442s| 0.155104s |
| 100000       | 0.751169s | 0.505198s |
| 1000000      | 7.61402s  | 5.00086s  |
| 10000000     | 94.8598s  | 57.5679s  |
----------------------------------------



# v2.0 rezultatai

Šioje versijoje atliekami testai naudojant **Google Test** framework'ą. Pridėta **Doxygen** dokumentacija. 

## Unit testai

Testams naudojamas **Google Test** framework'as.

|     Testas                     | Rezultatas|
|--------------------------------|-----------| 
|  `DefaultKonstruktorius`       |     ✅    |    
|  `CopyKonstruktorius `         |     ✅    |
|  `CopyAssignmentOperatorius`   |     ✅    |  
|  `MoveKonstruktorius`          |     ✅    |  
|  `MoveAssignmentOperatorius`   |     ✅    |  
|  `Destruktorius`               |     ✅    |  
|  `ĮvestiesIšvestiesOperatoriai`|     ✅    |  
|  `GalutinioBaloSkaičiavimasVid`|     ✅    |   
|  `GalutinioBaloSkaičiavimasMed`|     ✅    |
----------------------------------------------

## Nuotrauka
<img width="1122" height="697" alt="image" src="https://github.com/user-attachments/assets/1cca3b77-0199-46c6-a1a5-539c6f67ddc6" />


# v1.5 rezultatai

Šioje versijoje išlaikyta ta pati v1.2 versijos logika, tačiau pridėta abstrakti bazinė klasė `Zmogus` ir iš jos išvesta `Studentas` klasė.

|      Klasė     |  Tipas  |  Ką saugo                                      | 
|----------------|---------|------------------------------------------------| 
| `Zmogus`       | Abstract| vardą ir pavardę                               |   
| `Studentas`    | Derived | pažymius, egzamino balą, galutinius įvertinimus|
-----------------------------------------------------------------------------

Bandymas sukurti abstrakčios "Zmogus" klasės objektą

`Zmogus z("Vardenis", "Pavardenis")`

<img width="1113" height="358" alt="image" src="https://github.com/user-attachments/assets/28e4e9f8-01c2-468a-a56d-9eff1a9dd213" />


# "Rule of five"

|   Metodas                | Sintaksė                                  |Paskirtis                                     | 
| -------------------------|-------------------------------------------|----------------------------------------------| 
|Copy konstruktorius       |`studentas(const studentas& a)`            |Kuriama objekto kopija                        |
|Copy priskyrimo operatorius|`studentas& operator=(const studentas &a)`|objekto kopijos priskyrimas - b = a           |
|Move konstruktorius       |`studentas(studentas&& a)`                 |Objekto perėmimas - studentas b = std::move(a)|                                          |
|Move priskyrimo operatorius|`studentas& operator=(studentas&& a)`     |Objekto perėmimas - b = std::move(a)          |
|Destruktorius             |`~studentas()`                             |Objekto sunaikinimas (veikia automtiskai)     |
-----------------------------------------------------------------------------------------------------------------------

I/O operatoriai

|  Operatorius   |  Paskirtis                           | 
|----------------|--------------------------------------|
| `operator>>`     | nuskaito duomenis iš srauto į objektą|    
| `operator<<`    | Išveda objekto duomenis į srautą     |  
----------------------------------------------------------

Rezultatų nuotrauka

<img width="387" height="126" alt="image" src="https://github.com/user-attachments/assets/8cf09e6b-64d9-49ae-a405-f6eaa1b4422f" />

# v1.2 rezultatai

|   Metodas                | Sintaksė                                  |Paskirtis                                     | 
| -------------------------|-------------------------------------------|----------------------------------------------| 
|Copy konstruktorius       |`studentas(const studentas& a)`            |Kuriama objekto kopija                        |
|Copy priskyrimo operatorius|`studentas& operator=(const studentas &a)`|objekto kopijos priskyrimas - b = a           |
|Move konstruktorius       |`studentas(studentas&& a)`                 |Objekto perėmimas - studentas b = std::move(a)|                                          |
|Move priskyrimo operatorius|`studentas& operator=(studentas&& a)`     |Objekto perėmimas - b = std::move(a)          |
|Destruktorius             |`~studentas()`                             |Objekto sunaikinimas (veikia automtiskai)     |
-----------------------------------------------------------------------------------------------------------------------

I/O operatoriai

|  Operatorius   |  Paskirtis                           | 
|----------------|--------------------------------------|
| `operator>>`     | nuskaito duomenis iš srauto į objektą|    
| `operator<<`    | Išveda objekto duomenis į srautą     |  
----------------------------------------------------------

Nuotrauka

<img width="387" height="126" alt="image" src="https://github.com/user-attachments/assets/8cf09e6b-64d9-49ae-a405-f6eaa1b4422f" />

# v1.1 rezultatai:

- Tyrimas atliekamas su vector konteineriu, pannaudojant 3-ją strategiją, kuri buvo sukurta v1.0 versijoje.
- Tyrimo tkslas palyginti struct ir class efektyvumą, saugant studentų duomenis.


100000 studentų failas

|   Veikimo laikas (class) |  Veikimo laikas (struct)  | Vėliava | Vykdomojo failo dydis (class) | Vykdomojo failo dydis (struct)   |
| -------------------------|---------------------------| --------| ------------------------------| ---------------------------------| 
|     0.277439 s           |          0.241432 s       | -01     |             206.5 KB          |               210.1 KB           | 
|     0.305582 s           |          0.251457 s       | -O2     |             189.6 KB          |               183.8 KB           |
|     0.28994 s            |          0.239646 s       | -O3     |             191.2 KB          |               190.2 KB           |
-------------------------------------------------------------------------------------------------------------------------------------

1000000 studentų failas

|   Veikimo laikas (class) |  Veikimo laikas (struct)  | Vėliava | Vykdomojo failo dydis (class) | Vykdomojo failo dydis (struct)   |
| -------------------------|---------------------------| --------| ------------------------------| ---------------------------------| 
|     2.64364 s            |          2.25808 s        | -01     |             206.5 KB          |               210.1 KB           | 
|     2.75745 s            |          2.28378 s        | -O2     |             189.6 KB          |               183.8 KB           |
|     2.66723 s            |          2.14807 s        | -O3     |             191.2 KB          |               190.2 KB           |
-------------------------------------------------------------------------------------------------------------------------------------

