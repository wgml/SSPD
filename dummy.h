#ifndef DUMMY_H
#define DUMMY_H

typedef enum PARAMETERS {
    PrSz1, //Liczba przetworzonych na maszynie I szaf
    PrSz2, //Liczba przetworzonych na maszynie II szaf
    PrK, //Liczba przetworzonych na maszynie I krzeseł
    LSzM,//Liczba Szaf w magazynie (gotowych)
    LKM,//Liczba krzeseł w magazynie (gotowych)
    KSz,//Liczba szaf czekających w kolejce na rozpoczęcie obróbki
    KK,//Liczba krzeseł oczekujących w kolejce na rozpoczęcie obróbki
    i,//pokazuje numer aktualnie realizowanego zamówienia
    j,//pokazuje ilość zamówień, które przybyły do systemu
    LWP,//Liczba wolnych pracowników
    CzP,//Czas przybycia zlecenia
    CzW,//Czas wyjścia zlecenia z systemu
    ZASz,//Zapotrzebowanie na szafy danego zamówienia
    ZAK,//Zapotrzebowanie na krzesła danego zamówienia
    LWM1,//Liczba wolnych maszyn I
    LWM2,// Liczba wolnych maszyn II
    LWM3,//Liczba wolnych maszyn III

    lPracownikow,
    lMaszyn1,
    lMaszyn2,
    lMaszyn3,
    czstZamowien,

    aktualnyCzas
} Parameter;

class Dummy
{
public:
    Dummy() {}

    int get(Parameter p) { return int(p); } // pozwala pobrać wartość dowolnego parametru
    int getOrderChairs(int orderID) { return orderID; }
    int getOrderWardrobes(int orderID) { return orderID; }
    int getOrderTime(int orderID) { return orderID; }

    void set(Parameter p, int v) {} // pozwala ustawić parametry takie jak ilość pracowników czy maszyn

    void sim(unsigned time = 1) {} //symuluje zadaną ilość czasu
};

#endif // DUMMY_H
