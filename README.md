# SensorBase
[PL] Aplikacja do zarządzania czujnikami i wynikami pomiarów, zapisanymi w plikach TXT
[EN] Application to manage sensors and measurement results stored in TXT files

# Zasada działania / Working principle

[PL] W pliku urzadzenia.txt zawarto przykładową bazę czujników. Można wyróżnić kolejno kolumny ID, Adres IP, Wartość minimalna, Wartość maksymalna, Jednostka, Precyzja bitowa oraz Status (t-aktywny, n-wyłączony).

Plik pomiary.txt zawiera dwie kolumny: ID oraz wynik. Wynik jest liczbą z zakresu od 0 do maksymalnej wartości binarnej czujnika (2 do potęgi Precyzja bitowa minus 1).

Po uruchomieniu aplikacji i podaniu danych pozwala ona na:
1. Odczyt bazy i wygnerowanie listy aktywnych i nieaktywnych czujników
2. Dodanie czujnika, bądź nadpisanie istniejącego
3. Przeliczenie danych z pliku w oparciu o bazę czujników - weryfikowana jest obecność czujnika, jego aktywność, a także czy był on nadpisany.

[EN] Example sensor database is stored in urzadzenia.txt file. Columns have meaning as follows: ID, IP Address, MinValue, MaxValue, Measurement unit, Bit precision and State (t-active, n-disabled).

File pomiary.txt has two columns: ID and Result. Result is a number in range 0 to max binary value of sensor (possible to store on given number of bits).

Application after startup and setup lets user to:
1. Read the database and show active or disabled sensors.
2. Add sensor or overwrite existing one.
3. Calculate values stored in measurement file based on sensor database - presence of sensor, status and override are werified.
