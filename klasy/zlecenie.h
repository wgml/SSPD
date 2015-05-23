/*
 * zlecenie.h
 *
 *  Created on: 21 maj 2015
 *      Author: rafal
 */

#ifndef KLASY_ZLECENIE_H_
#define KLASY_ZLECENIE_H_

#include <iostream>

class Zlecenie{
	public:
		Zlecenie();
		Zlecenie(unsigned krzesla, unsigned szafy, unsigned przybycie, unsigned wyjscie=0);
		Zlecenie(const Zlecenie&);
		~Zlecenie();
		Zlecenie& operator=(const Zlecenie &);
		friend std::ostream& operator<<(std::ostream&, const Zlecenie&);
		bool operator<(const Zlecenie&);
		bool operator==(const Zlecenie&);

		//settery
		void nrZlecenia(unsigned);
		void czasWyjscia(unsigned);
		void czasPrzybycia(unsigned);
		void zapotrzebowanieKrzesla(unsigned);
		void zapotrzebowanieSzafy(unsigned);

		//gettery
		unsigned nrZlecenia();
		unsigned czasWyjscia();
		unsigned czasPrzybycia();
		unsigned zapotrzebowanieKrzesla();
		unsigned zapotrzebowanieSzafy();

	private:
		static unsigned id;		//numery identyfikacyjne zleceń

		//parametery
		unsigned Nr;	//numer danego zamówienia(priorytet)
		unsigned CzP;	//czas przybycia zlecenia
		unsigned CzW;	//czas wyjscia zlecenia z systemu
		unsigned ZAKs;	//zapotrzebowanie na szafy
		unsigned ZAK;	//zapotrzebowanie na kaszesła

};


#endif /* KLASY_ZLECENIE_H_ */
