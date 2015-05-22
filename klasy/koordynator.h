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

#include "maszyna.h"
#include "pracownik.h"
#include "zlecenie.h"



/**
 * klasa koordynatora zadaniowego który ogarnia cały ten burdel
 * */
class Koordynator{
	public:
		Koordynator(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

		void symuluj(unsigned int);

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

		//dla W
		enum class Parameter{

		};

		void set(Parameter, unsigned int);
		unsigned int set(Parameter);


	private:
		//"globalne zmienne stanu"
		static unsigned int PrSz;	//liczba szaf przetworzonych na maszynie typu I
		static unsigned int PrK;	//liczba krzeseł przetworzonych na maszynie typu I
		static unsigned int LSzM;	//liczba szaf w magazynie(gotowych)
		static unsigned int LKM;	//liczba krzeseł w magazynie(gotowych)
		static unsigned int KSz;	//liczba szaf czekających w kolejce na rozpoczęcie obróbki
		static unsigned int KK;     //liczba krzeseł oczekujących w kolejce na rozpoczęcie obróbki
		static unsigned int i;		//numer aktualnie realizowanego zamówienia
		static unsigned int j;		//pokazuje ilość zamówień, które przybyły do systemu


		unsigned int dlugoscSymulacji;
		unsigned int czasSymulacji;

		std::vector<Pracownik> pracownicy;
		std::vector<Maszyna> maszyny;
		std::list<Zlecenie> zlecenia;


};



#endif /* KLASY_KOORDYNATOR_H_ */
