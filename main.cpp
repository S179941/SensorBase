//POP 2019-01-13 projekt 2 Ostrowski Michal EIT 1 179941 Code::Blocks 17.12 GCC-6.3.0-1
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

//Funkcja do przeliczania wynikow (z tresci zadania)

float przelicznik(int pomiar, int rozdz, int w_min, int w_max)
{
    float wynik;
    wynik = (pomiar / pow(2,rozdz)) * (w_max-w_min) + w_min;
    return wynik;
}

//Funkcja do znalezienia interesujacych statusow

void wypisz_status(fstream &zrodlo, char status_szuk)
{
    //Dane wczytywane do bufora
    int ID;
    string IP;
    int w_min;
    int w_max;
    string jedn;
    int rozdz;
    char status;

    //Wypisanie naglowka

    cout << "ID" << '\t' << setw(15) << "IP" << '\t' << "w_min" << '\t' << "w_max" <<  '\t' << "jedn" << '\t' << "rozdz" << endl << endl;

    //Petla wczytujaca linijki ze strumienia

    while(zrodlo >> ID >> IP >> w_min >> w_max >> jedn >> rozdz >> status)
    {
        if(status == status_szuk){
            cout << ID << '\t' << setw(15) << IP << '\t' << w_min << '\t' << w_max <<  '\t' << jedn << '\t' << rozdz << endl;
        }
    }
    cout << endl;
}

//Menu do wyswietlenia czujnikow

void wypisz_czujniki(string baza_n)
{

    fstream zrodlo;
    zrodlo.open(baza_n, ios::in);

    system("cls");
    cout << "Jesli podac aktywne wybierz 1. Jesli podac nieaktywne wybierz 2." << endl;
    int wybor;
    cin >> wybor;
    switch(wybor)
    {
    case 1:
        wypisz_status(zrodlo, 't');
        break;
    case 2:
        wypisz_status(zrodlo, 'n');
        break;
    default:
        break;
    }
    zrodlo.close();
    system("pause");
}

//Dodawanie nowego czujnika z ID automatycznym

void dodaj_nowy(string baza_n)
{
    //Otwarcie w trybie do odczytu, aby ustalic najwyzsze ID na liscie

    fstream baza_in;
    baza_in.open(baza_n, ios::in);

    //Zmienne jako bufor na dane z pliku

    int ID_buf;
    string IP_buf;
    int w_min_buf;
    int w_max_buf;
    string jedn_buf;
    int rozdz_buf;
    char status_buf;
    int HH_ID = -1; //Na wypadek pustego pliku

    //Petla szukajaca najwyzszego

    while(baza_in >> ID_buf >> IP_buf >> w_min_buf >> w_max_buf >> jedn_buf >> rozdz_buf >> status_buf)
    {
        if(ID_buf>HH_ID){
            HH_ID=ID_buf;
        }
    }

    baza_in.close();

    //Dopisywanie czujnikow do listy z ID nadanym automatycznie

    fstream baza_out;
    baza_out.open(baza_n, ios::app);

    system("cls");
    cout << "Podaj ilosc czujnikow do dopisania." << endl;
    int ilosc = 0;
    cin >> ilosc;

    for(int i=0; i<ilosc; i++)
    {
        //Zmienne wczytywane z klawiatury
        int ID;
        string IP;
        int w_min;
        int w_max;
        string jedn;
        int rozdz;
        char status;

        ID = HH_ID+1+i; //Wyliczenie ID z ostatniego i iteracji

        system("cls");
        cout << "IP:";
        cin >> IP;
        cout << "Wartosc minimalna:";
        cin >> w_min;
        cout << "Wartosc maksymalna:";
        cin >> w_max;
        cout << "Jednostka:";
        cin >> jedn;
        cout << "Rozdzielczosc:";
        cin >> rozdz;
        cout << "Status:";
        cin >> status;

        baza_out << ID << '\t' << IP << '\t' << w_min << '\t' << w_max << '\t' << jedn << '\t' << rozdz << '\t' << status << endl;
    }

    baza_out.close();


}

//Rowniez dodanie czujnika, ale ID manualne

void nadpisz(string baza_n)
{
    fstream baza_out;
    baza_out.open(baza_n, ios::app);

    system("cls");
    cout << "Podaj ilosc czujnikow do dopisania." << endl;
    int ilosc = 0;
    cin >> ilosc;

    for(int i=0; i<ilosc; i++)
    {
        int ID;
        string IP;
        int w_min;
        int w_max;
        string jedn;
        int rozdz;
        char status;

        system("cls");
        cout << "Podaj ID czujnika. Uwaga! Moze on juz istniec:";
        cin >> ID;
        cout << "IP:";
        cin >> IP;
        cout << "Wartosc minimalna:";
        cin >> w_min;
        cout << "Wartosc maksymalna:";
        cin >> w_max;
        cout << "Jednostka:";
        cin >> jedn;
        cout << "Rozdzielczosc:";
        cin >> rozdz;
        cout << "Status:";
        cin >> status;

        baza_out << ID << '\t' << IP << '\t' << w_min << '\t' << w_max << '\t' << jedn << '\t' << rozdz << '\t' << status << endl;
    }

    baza_out.close();
}

//Menu do dopisywania czujnikow

void edytuj_czujniki(string baza_n)
{
    system("cls");
    cout << "Aby dopisac nowy czujnik wybierz 1." << endl << "Aby uzyc numeru istniejacego czujnika wybierz 2." << endl;
    int wybor;
    cin >> wybor;
    switch(wybor)
    {
    case 1:
        dodaj_nowy(baza_n);
        break;
    case 2:
        nadpisz(baza_n);
        break;
    default:
        break;
    }
}

//Funkcja do przeliczenia pomiarow, dwie petle plikowe

void przelicz_dane(string baza_n)
{
    string pomiary_n;
    system("cls");
    cout << "Podaj nazwe pliku z pomiarami" << endl;
    cin >> pomiary_n;

    //Przygotowanie strumieni do pracy

    fstream pomiary;
    fstream baza;
    pomiary.open(pomiary_n, ios::in);
    baza.open(baza_n, ios::in);

    int ID_p;
    int pomiar;

    while(pomiary >> ID_p >> pomiar)
    {
        //Zmienne konieczne do wyliczenia wyniku
        int w_min;
        int w_max;
        string jedn;
        int rozdz;
        char status;
        //Zmienne tymczasowe odczytywane z bazy (BUFOR)
        int ID_buf;
        string IP_buf;
        int w_min_buf;
        int w_max_buf;
        string jedn_buf;
        int rozdz_buf;
        char status_buf;

        //Licznik znalezionych pasujacych definicji
        int licznik = 0;

        while(baza >> ID_buf >> IP_buf >> w_min_buf >> w_max_buf >> jedn_buf >> rozdz_buf >> status_buf)
        {
            if(ID_buf==ID_p){
                w_min=w_min_buf;
                w_max=w_max_buf;
                jedn=jedn_buf;
                rozdz=rozdz_buf;
                status=status_buf;
                licznik++;
            }
        }
        //Przygotowanie bazy do poszukiwan nastepnej definicji czujnika
        baza.clear();
        baza.seekg(0, ios::beg);

        //Wyliczenie wyniku pomiaru
        if(licznik)
        {
            if(status!='n')
            {
                float wynik;
                wynik = przelicznik(pomiar,rozdz,w_min,w_max);
                cout << setw(8) << wynik << '\t' << jedn << '\t' << "czujnik" << '\t' << ID_p << '\t';
                if(licznik>1)
                {
                    cout << '*' << endl;
                }
                else
                {
                    cout << endl;
                }
            }
            else
            {
                cout << "Znaleziony czujnik" << '\t' << ID_p << '\t' << "nieaktywny." << endl;
            }
        }
        else
        {
            cout << "Brak definicji czujnika" << '\t' << ID_p << endl;
        }

    }
    //Sprzatanie po liczeniu
    pomiary.close();
    baza.close();
    system("pause");
}



int main()
{
    string baza_n;
    cout << "Podaj nazwe pliku z czujnikami (baze danych)" << endl;
    cin >> baza_n;

    while(1)
    {
        int wybor;

        system("cls");
        cout << "MENU GLOWNE" << endl
        << endl
        << "--------------------------------------------" << endl
        << endl
        << "1.Odczyt czujnikow aktywnych/nieaktywnych" << endl
        << "2.Dodanie nowego czujnika/nadpisanie istniejacego" << endl
        << "3.Przeliczenie danych pomiarowych" << endl
        << endl
        << "Wybierz opcje i zatwierdz ENTER" << endl;

        cin >> wybor;

        switch(wybor)
        {
        case 1:
            wypisz_czujniki(baza_n);
            break;

        case 2:
            edytuj_czujniki(baza_n);
            break;

        case 3:
            przelicz_dane(baza_n);
            break;

        default:
            break;
        }
    }
}
