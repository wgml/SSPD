/*
 * pracownik.h
 *
 *  Created on: 21 maj 2015
 *      Author: rafal
 */

#ifndef KLASY_PRACOWNIK_H_
#define KLASY_PRACOWNIK_H_

#include <iostream>

/*
 * Klasa odpowiedzialna za obsługę maszyn, czyli przetwarzanie szaf i krzeseł.
 * */
class Pracownik{
	public:
		Pracownik();
		Pracownik(const Pracownik&);
		~Pracownik();
		Pracownik& operator=(const Pracownik&);
		friend std::ostream& operator<<(std::ostream&, const Pracownik&);

		//dla W
		enum class Parameter{
			idPracownika,
			liczbaPracownikow,
			liczbaWolnychPracownikow,
			czasObrobkiMaszyna1,
			czasObrobkiMaszyna2,
			czasObrobkiMaszyna3
		};
		void set(Parameter, unsigned int);
		unsigned int get(Parameter);
	private:
		//stany
		static unsigned int id;		//numery identyfikacyjne pracowników
		static unsigned int lp;		//liczba pracowników
		static unsigned int lwp;	//liczba wolnych pracownikow

		//parametry
		unsigned int czo1;		//czas obróbki na maszynie typu 1
		unsigned int czo2;		//czas obróbki na maszynie typu 2
		unsigned int czo3;		//czas obróbki na maszynie typu 3

		enum class statusPracownika{
			wolny,
			pracujeNaMaszyna1,
			pracujeNaMaszyna2,
			pracujeNaMaszyna3,
			oczekuje
		};

		unsigned int idP;			//id pracownika
		statusPracownika status;	//status pracownika określający co robi obecnie dany pracownik
};



#endif /* KLASY_PRACOWNIK_H_ */
