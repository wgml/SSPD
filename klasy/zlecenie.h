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
		Zlecenie(const Zlecenie&);
		~Zlecenie();
		Zlecenie& operator=(const Zlecenie &);
		friend std::ostream& operator<<(std::ostream&, const Zlecenie&);
		bool operator<(const Zlecenie&);
		bool operator==(const Zlecenie&);

		//dla W
		enum class Parameter{
			nrZlecenia,
			czasPrzybyciaZlecenia,
			czasWyjsciaZlecenia,
			zapotrzebowanieNaSzsafy,
			zapotrzebowanieNaKrzesla
		};

		void set(Parameter, unsigned int);
		unsigned int get(Parameter);

	private:
		static unsigned int id;		//numery identyfikacyjne zleceń
		static unsigned int lz;		//liczba zleceń

		//parametery
		unsigned int Nr;	//numer danego zamówienia(priorytet)
		unsigned int CzP;	//czas przybycia zlecenia
		unsigned int CzW;	//czas wyjscia zlecenia z systemu
		unsigned int ZAKs;	//zapotrzebowanie na szafy
		unsigned int ZAK;	//zapotrzebowanie na kaszesła

};


#endif /* KLASY_ZLECENIE_H_ */
