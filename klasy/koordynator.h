/*
 * koordynator.h
 *
 *  Created on: 22 maj 2015
 *      Author: rafal
 */

#ifndef KLASY_KOORDYNATOR_H_
#define KLASY_KOORDYNATOR_H_

#include <iostream>
#include <vector>
#include <list>

#include "zlecenie.h"

enum class Parameter{
    PrSz, 	//Liczba przetworzonych na maszynie I szaf
    PrSz2, 	//Liczba przetworzonych na maszynie II szaf
    PrK, 	//Liczba przetworzonych na maszynie I krzeseł
    LSzM,	//Liczba Szaf w magazynie (gotowych)
    LKM,	//Liczba krzeseł w magazynie (gotowych)
    KSz,	//Liczba szaf czekających w kolejce na rozpoczęcie obróbki
    KK,		//Liczba krzeseł oczekujących w kolejce na rozpoczęcie obróbki
    i,		//liczba zrealizowanych zamówień
    j,		//liczba zamówień, które przybyły do systemu
    LWP,	//Liczba wolnych pracowników
    ZASz,	//Zapotrzebowanie na szafy
    ZAK,	//Zapotrzebowanie na krzesła
    LWM1,	//Liczba wolnych maszyn I
    LWM2,	//Liczba wolnych maszyn II
    LWM3,	//Liczba wolnych maszyn III
    lPracownikow,
    lMaszyn1,
    lMaszyn2,
    lMaszyn3,
    aktualnyCzas
};

/**
 * klasa koordynatora zadaniowego który ogarnia cały ten burdel
 * */
class Koordynator{
	public:
		/*
		 * konstruktor Koordynatora obsługującego zakład
		 * @param lP liczba pracowników w zakkładzie
		 * @param lM1 liczba maszyn typu pierwszego
		 * @param lM2 liczba maszyn typu drugiego
		 * @param lM3 liczba maszyn typu trzeciego
		 * @param dlSym długość symulacji podana w jednostkach czasu
		 * */
		Koordynator(unsigned lP, unsigned lM1, unsigned lM2, unsigned lM3, unsigned int dlSym);

		/*
		 * przprowadza symulację trwającą n jednostek czasu
		 * jeżli czas symulacji przekroczy długość symulacji funkcja jest przerywana
		 * @param n ilosc jednostek czasu
		 */
		void sim(unsigned n);

		void set(Parameter, unsigned);
		unsigned get(Parameter);

	private:
		//nagłówki rozpatrywane przez koordynatora
		void koniecWyjsciaZlecenia();
		void poczatekWyjsciaZlecenia();
		void koniecObrobkiMaszynaIII();
		void poczatekObrobkiMaszynaIII();
		void koniecObrobkiSzafMaszynaII();
		void poczatekObrobkiSzafMaszynaII();
		void koniecObrobkiSzafMaszynaI();
		void poczatekObrobkiSzafMaszynaI();
		void koniecObrobkiKrzeselMaszynaII();
		void poczatekObrobkiKrzeselMaszynaII();
		void koniecObrobkiKrzeselMaszynaI();
		void poczatekObrobkiKrzeselMaszynaI();
		void poczatekRealizacji();
		void przybycieZlecenia();

		//"globalne zmienne stanu"
	    unsigned PrSz1; //Liczba przetworzonych na maszynie I szaf
		unsigned PrSz2; //Liczba przetworzonych na maszynie II szaf
		unsigned PrK; 	//Liczba przetworzonych na maszynie I krzeseł
		unsigned LSzM;	//Liczba Szaf w magazynie (gotowych)
		unsigned LKM;	//Liczba krzeseł w magazynie (gotowych)
		unsigned KSz;	//Liczba szaf czekających w kolejce na rozpoczęcie obróbki
		unsigned KK;	//Liczba krzeseł oczekujących w kolejce na rozpoczęcie obróbki
		unsigned i;		//liczba zrealizowanych zamówień
		unsigned j;		//liczbazamówień, które przybyły do systemu
		unsigned LWP;	//Liczba wolnych pracowników
		unsigned ZASz;	//Zapotrzebowanie na szafy danego zamówienia
		unsigned ZAK;	//Zapotrzebowanie na krzesła danego zamówienia
		unsigned LWM1;	//Liczba wolnych maszyn I
		unsigned LWM2;	//Liczba wolnych maszyn II
		unsigned LWM3;	//Liczba wolnych maszyn III
		unsigned LP;	//Liczba pracowników w ogóle
		unsigned LM1;	//liczba maszyn typu 1
		unsigned LM2;	//liczba maszyn typu 2
		unsigned LM3;	//liczba maszyn typu 3

		unsigned aktualnyCzas;
		unsigned dlugoscSymulacji;

		/*
		 * Czasy obsługi na maszynach
		 * todo narazie będą stałymi, kiedyś odjebie się losowanko
		 * */
		const unsigned czasObrobkiSzafyMaszyna3 = 30;
		const unsigned czasObrobkiSzafyMaszyna2 = 5;
		const unsigned czasObrobkiSzafyMaszyna1 = 15;
		const unsigned czasObrobkiKrzeslaMaszyna2 = 10;
		const unsigned czasObrobkiKrzeslaMaszyna1 = 20;

		//zakresy dla generatora
		const unsigned czasD = 10;
		const unsigned czasG = 45;
		const unsigned krzeslaD = 0;
		const unsigned krzeslaG = 10;
		const unsigned szafyD = 0;
		const unsigned szafyG = 5;

		//listy ze zleceniami
		std::list<Zlecenie> zleceniaPrzybywajace;
		std::list<Zlecenie> zleceniaOczekujace;
		std::list<Zlecenie> zleceniaZrealizowane;

		//czasy końca obórki szaf na maszynach
		std::list<unsigned> szafyKoniecM3;
		std::list<unsigned> szafyKoniecM2;
		std::list<unsigned> szafyKoniecM1;

		//czasy końca obróbki krzeseł na maszynach
		std::list<unsigned> krzeslaKoniecM2;
		std::list<unsigned> krzeslaKoniecM1;

};



#endif /* KLASY_KOORDYNATOR_H_ */
