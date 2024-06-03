# Objektinio Programavimo Projektas
Ši programa skirta studentų duomenų nuskaitymui - vardas, pavardė, namų darbų rezultatai ir egzamino rezultatas, ir galutinio balo apskaičiavimas pagal nurodytus kriterijus.

## Įdiegimas (Windows)
1. Atsisiųskite ir įdiekite Git (https://git-scm.com/downloads)
2. Atsisiųskite ir įdiekite Msys2 (https://www.msys2.org/)
3. Atidarykite Msys2 terminalą
4. Įdiekite paketus, įvesdami "pacman -S mingw-w64-x86_64-gcc" ir "pacman -S mingw-w64-x86_64-ninja"
5. Atsisiųskite ir įdiekite CMake (https://cmake.org/download/) pasirinkus "Add CMake to the system PATH for all users"
6. Eikite į “code” katalogą
7. Programą paleisktie paleidus run.bat failą
## Naudojimas
1. Paleiskite programą.
2. Pasirinkite programos eigos būdą įvesdami atitinkamus skaitmenys
3. Mielo naudojimosi!
## Autorius
Šį programinį produktą sukūrė Edvin Olenkovič
## MyVector apžvalga
### push_back()
Prideda nurodytą elemento reikšmę prie konteinerio galo.
```cpp
MyVector<int> vec;
vec.push_back(1);
vec.push_back(2);
vec.push_back(3);

std::cout << "MyVector reiksmes:";
for (unsigned int i = 0; i < vec.size(); i++)
    std::cout << ' ' << vec[i];
std::cout << '\n';
```
Rezultatas
```cpp
MyVector reiksmes: 1 2 3
```
### capacity()
Nurodo dabartinę konteinerio talpą.
```cpp
MyVector<int> vec;
vec.push_back(1);
vec.push_back(2);
vec.push_back(3);

std::cout << "MyVector talpa: " << vec.capacity() << std::endl;
```
Rezultatas
```cpp
MyVector talpa: 4
```
### pop_back()
Pašalina paskutinį konteinerio elementą.
```cpp
MyVector<int> vec;
vec.push_back(1);
vec.push_back(2);
vec.push_back(3);
vec.pop_back();

std::cout << "MyVector reiksmes:";
for (unsigned int i = 0; i < vec.size(); i++)
    std::cout << ' ' << vec[i];
std::cout << '\n';
```
Rezultatas
```cpp
MyVector reiksmes: 1 2
```
### shrink_to_fit()
Sumažina atminties naudojimą atlaisvindamas nenaudojamą atmintį.
```cpp
MyVector<int> vec;
for (unsigned int i = 0; i < 10; i++)
    vec.push_back(i);
    std::cout << "Talpa pries shrink_to_fit: " << vec.capacity() << "\n";
vec.shrink_to_fit();
std::cout << "Talpa po shrink_to_fit: " << vec.capacity() << "\n";
```
Rezultatas
```cpp
Talpa pries shrink_to_fit: 16
Talpa po shrink_to_fit: 10
```
### empty()
Patikrina ar konteineris yra tuščias.
```cpp
MyVector<int> vec;
std::cout << "Ar MyVector tuscias? " << (vec.empty() ? "Taip" : "Ne") << "\n";
```
Rezultatas
```cpp
Ar MyVector tuscias? Taip
```
## Testavimai
- Intel(R) Core(TM) i7-9700K CPU @ 3.60GHz
- RAM(16,0 GB)
- Samsung SSD 970 EVO Plus 500GB
### Konteinerių užpildymas (v3.0)
| Elementu skaicius | std::vector laikas | MyVector laikas | std::vector atminties perskirstymai | MyVector atminties perskirstymai |
|-------------------|--------------------|-----------------|-------------------------------------|----------------------------------|
| 10000             | 0.000068s           | 0.000041s        | 14                                  | 14                               |
| 100000            | 0.000384s           | 0.000293s        | 17                                  | 17                               |
| 1000000           | 0.002038s           | 0.001965s        | 20                                  | 20                               |
| 10000000          | 0.024393s           | 0.024126s        | 24                                  | 24                               |
| 100000000         | 0.233874s           | 0.227221s        | 27                                  | 27                               |

### Class (nuo v1.1)
                                                 100000 Studentų

|                       | -O1                           | -O2                           | -O3                           |
|-----------------------|-------------------------------|-------------------------------|-------------------------------|
| Skaitymas iš failo =  | 0,3567s                       | 0,372s                        | 0,3472s                       |
| Studentų skirstymas = | 0,0748s                       | 0,0606s                       | 0,065s                        |
| .exe failo dydis =    | 203Kb                         | 197Kb                         | 207Kb                         |

                                                 1000000 Studentų

|                       | -O1                           | -O2                           | -O3                           |
|-----------------------|-------------------------------|-------------------------------|-------------------------------|
| Skaitymas iš failo =  | 3,2986s                       | 3,554667s                     | 3,3614s                       |
| Studentų skirstymas = | 0,7604s                       | 0,861333s                     | 0,8094s                       |
| .exe failo dydis =    | 203Kb                         | 197Kb                         | 207Kb                         |

## Aprašymas apie perdengtus metodus
### Įvesties perdengimo metodai
- Duomenų įvestis rankiniu ir automatinių būdu įvyksta, kai duomenų skaitymui yra naudojamas `istream` objektas (šios programos atveju `std::cin`) t.y. programos eigos pasirinkimas - `"1" - Įvedimas ranka` ir `"2" - Generavimas`
- Duomenų įvestis iš failo įvyksta, kai duomenų skaitymui naudojamas `istringstream` objektas. t.y. programos eigos pasirinkimas - `"3" - Skaitymas iš failo`

### Išvesties perdengimo metodai
- Duomenų išvedimas per konsolę įvyksta, kai duomenų išvedimui yra naudojamas `ostream` objektas (šios programos atveju `std::cout`) t.y. programos eigos pasirinkimas - `"6" - Rezultatu išvedimas`
- Duomenų išvedimas į failą įvyksta, kai duomenų išvedimui yra naudojamas `ofstream` objektas t.y. programos eigos pasirinkimas - `"5" - Atrinkti studentus`

## Changelog
- Pirmasis pre-release v.pradinė (2024-02-16)
Vartotojas gali įvesti duomenys pagal kuriuos atliekami galutinio balo skaičiavimai ir išvedami ant ekrano.
- Pre-release v0.1 (2024-02-16)
Namų darbų ir įrašų skaičiai neturi būti žinomi, tik įvedimo metu vartotojas nusprendžia kuomet jis jau įvedė visų namų darbų rezultatus ir kada jis baigią žmonių įvedimą.
- Pre-release v0.2 (2024-02-23)
Duomenys galima nuskaityti iš failo, bei įvesti ranka.
- Pre-release v0.3 (2024-02-29)
Atliktas kodo reorganizavimas (refactoring). Programa tikrina duomenų tikslumą, valdo išimtis.
- Pre-release v0.4 (2024-03-08)
Pridėtos failų generavimo, bei studentų paskirstymo ir rušiavimo funkcijos.
- Release v1.0 (2024-03-22)
Pridėtas konteinerio (vector, list, deque) pasirinkimas duomenų apdorojimui.
- Release v1.1 (2024-04-12)
Pilnas kodo peržiūrėjimas. Perėjimas nuo struct į class strukturą.
- Release v1.2 (2024-04-19)
Realizuotas "Rule of five" ir aprašyti įvesties ir išvesties operatoriai paprastesniam kodo rašymui
- Release v1.5 (2024-04-19)
Pridėta bendra abstrakti "Person" klasė, kurios išvestinė dabar yra "Student"
- Release v2.0 (2024-05-03)
Sukurta HTML dokumentacija. Realizuoti Unit Test'ai su GoogleTest.
- Release v3.0 (2024-05-24)
Sukurtas naujas konteineris MyVector. Pridėtas setup failas.
