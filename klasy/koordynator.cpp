/*
 * koordynator.cpp
 *
 *  Created on: 22 maj 2015
 *      Author: rafal
 */

#include "koordynator.h"
#include <algorithm>
#include <random>

Koordynator::Koordynator(unsigned lP, unsigned lM1, unsigned lM2, unsigned lM3, unsigned int dlSym){

	std::list<Zlecenie> zleceniaOczekujace = std::list<Zlecenie>();
	std::list<Zlecenie> zleceniaWykonane   = std::list<Zlecenie>();

    this->PrSz1 = 0; 	//Liczba przetworzonych na maszynie I szaf
    this->PrSz2 = 0; 	//Liczba przetworzonych na maszynie II szaf
    this->PrK 	= 0; 	//Liczba przetworzonych na maszynie I krzeseł
    this->LSzM  = 0;	//Liczba Szaf w magazynie (gotowych)
    this->LKM 	= 0;	//Liczba krzeseł w magazynie (gotowych)
    this->KSz 	= 0;	//Liczba szaf czekających w kolejce na rozpoczęcie obróbki
    this->KK 	= 0;	//Liczba krzeseł oczekujących w kolejce na rozpoczęcie obróbki
    this->i		= 0;	//liczba zrealizowanych zamówień
    this->j 	= 0;	//liczba zrealizowanych zamówień
    this->ZASz 	= 0;	//Zapotrzebowanie na szafy
    this->ZAK   = 0;	//Zapotrzebowanie na krzesła
    this->LP	= lP;	//Liczba pracowników w ogóle
    this->LWP   = lP;	//Liczba wolnych pracowników
    this->LM1 	= lM1;	//liczba maszyn typu 1
    this->LM2 	= lM2;	//liczba maszyn typu 2
    this->LM3 	= lM3;	//liczba maszyn typu 3
    this->LWM1 	= lM1;	//Liczba wolnych maszyn typu 1
    this->LWM2 	= lM2;	//Liczba wolnych maszyn typu 2
    this->LWM3 	= lM3;  //Liczba wolnych maszyn typu 3


    this->aktualnyCzas = 0;
    this->dlugoscSymulacji = dlSym;

	std::list<unsigned> szafyKoniecM3 = std::list<unsigned>();
	std::list<unsigned> szafyKoniecM2 = std::list<unsigned>();
	std::list<unsigned> szafyKoniecM1 = std::list<unsigned>();

	//losowanie czasów nowych zleceń
	std::default_random_engine generator;
	std::uniform_int_distribution<unsigned> genCzasu(this->czasD, this->czasG);
	std::uniform_int_distribution<unsigned> genKrzesel(this->krzeslaD, this->krzeslaG);
	std::uniform_int_distribution<unsigned> genSzaf(this->szafyD, this->szafyG);

	while(this->aktualnyCzas <= this->dlugoscSymulacji){
		unsigned nowyCzas 	 = genCzasu(generator);
		unsigned noweKrzesla = genKrzesel(generator);
		unsigned noweSzafy	 = genSzaf(generator);

		this->aktualnyCzas += nowyCzas;

		Zlecenie noweZlecenie = Zlecenie(noweKrzesla, noweSzafy, this->aktualnyCzas);

		this->zleceniaPrzybywajace.push_back(noweZlecenie);
	}

	this->aktualnyCzas = 0;
}

void Koordynator::sim(unsigned n){
	for(unsigned i=0; i<n; i++){
		this->aktualnyCzas++;

		this->poczatekWyjsciaZlecenia();		//tutaj została zamieniona kolejność #Artur!!
		this->koniecWyjsciaZlecenia();
		this->koniecObrobkiMaszynaIII();
		this->poczatekObrobkiMaszynaIII();
		this->koniecObrobkiSzafMaszynaII();
		this->poczatekObrobkiSzafMaszynaII();
		this->koniecObrobkiSzafMaszynaI();
		this->poczatekObrobkiSzafMaszynaI();
		this->koniecObrobkiKrzeselMaszynaII();
		this->poczatekObrobkiKrzeselMaszynaII();
		this->koniecObrobkiKrzeselMaszynaI();
		this->poczatekObrobkiKrzeselMaszynaI();
		this->poczatekRealizacji();
		this->przybycieZlecenia();

		std::cerr << *this << std::endl;

		if(this->aktualnyCzas >= this->dlugoscSymulacji) break;
	}
}

//nagłówki rozpatrywane przez koordynatora
void Koordynator::koniecWyjsciaZlecenia(){
	std::list<Zlecenie> temp;

	//weź zrealizowane zlecenia
	std::copy_if(this->zleceniaOczekujace.begin(), this->zleceniaOczekujace.end(), temp.begin(), [&](Zlecenie z){
		return (Koordynator::LSzM >= z.zapotrzebowanieSzafy()) && (Koordynator::LKM >= z.zapotrzebowanieKrzesla());});

	if(!temp.empty()){
		//znajdź zlecenie o najmniejszym id
		Zlecenie zrobione = *std::min_element(temp.begin(), temp.end());
		auto p = std::find(this->zleceniaOczekujace.begin(), this->zleceniaOczekujace.end(), zrobione);
		if( p != this->zleceniaOczekujace.end()) p->czasWyjscia(this->aktualnyCzas);
	}

}

void Koordynator::poczatekWyjsciaZlecenia(){
	auto it = std::find_if(this->zleceniaOczekujace.begin(), this->zleceniaOczekujace.end(),
	[&](Zlecenie z){
		return z.czasWyjscia() == this->aktualnyCzas;
	});

	if(it != this->zleceniaOczekujace.end()){
		Koordynator::LSzM -= it->zapotrzebowanieSzafy();
		Koordynator::LKM  -= it->zapotrzebowanieKrzesla();
		this->zleceniaZrealizowane.push_back(*it);
		this->zleceniaOczekujace.remove(*it);
		Koordynator::i++;
	}
}
void Koordynator::poczatekRealizacji(){
	//todo w przybycieZlecenia jest to zrobione
}

void Koordynator::przybycieZlecenia(){
	//sprawdzam początek listy
	if((this->zleceniaPrzybywajace.front()).czasPrzybycia() == this->aktualnyCzas){
		this->j += 1;
		this->zleceniaOczekujace.push_back(this->zleceniaPrzybywajace.front());
		this->KK  += (this->zleceniaPrzybywajace.front()).zapotrzebowanieKrzesla();
		this->KSz += (this->zleceniaPrzybywajace.front()).zapotrzebowanieSzafy();
		this->ZAK += (this->zleceniaPrzybywajace.front()).zapotrzebowanieKrzesla();
		this->ZASz+= (this->zleceniaPrzybywajace.front()).zapotrzebowanieSzafy();
		this->zleceniaPrzybywajace.pop_front();
	}
}

void Koordynator::poczatekObrobkiMaszynaIII(){
	if((this->LWP > 0) && (this->LWM3 > 0) && (this->PrSz2 > 0)){
		this->LWP--;
		this->LWM3--;
		this->PrSz2--;
		this->szafyKoniecM3.push_back(this->aktualnyCzas + this->czasObrobkiSzafyMaszyna3);
	}
}

void Koordynator::koniecObrobkiMaszynaIII(){
	if(this->szafyKoniecM3.front() == this->aktualnyCzas){
		this->LWP++;
		this->LWM3++;
		this->LSzM++;
		this->szafyKoniecM3.pop_front();
	}
}

void Koordynator::poczatekObrobkiSzafMaszynaII(){
	if((this->LWP > 0) && (this->LWM2 > 0) && (this->PrSz1 > 0)){
		this->LWP--;
		this->LWM2--;
		this->PrSz1--;
		this->szafyKoniecM2.push_back(this->aktualnyCzas + this->czasObrobkiSzafyMaszyna2);
	}
}

void Koordynator::koniecObrobkiSzafMaszynaII(){
	if(this->szafyKoniecM2.front() == this->aktualnyCzas){
		this->LWP++;
		this->LWM2++;
		this->PrSz2++;
		this->szafyKoniecM2.pop_front();
	}
}

void Koordynator::koniecObrobkiSzafMaszynaI(){
	if(this->szafyKoniecM1.front() == this->aktualnyCzas){
		this->LWP++;
		this->LWM1++;
		this->PrSz1++;
		this->szafyKoniecM1.pop_front();
	}
}

void Koordynator::poczatekObrobkiSzafMaszynaI(){
	if((this->LWP > 0) && (this->LWM1 > 0) && (this->KSz > 0)){
		this->LWP--;
		this->LWM1--;
		this->KSz--;
		this->szafyKoniecM1.push_back(this->aktualnyCzas + this->czasObrobkiSzafyMaszyna1);
	}
}

void Koordynator::koniecObrobkiKrzeselMaszynaII(){
	if(this->krzeslaKoniecM2.front() == this->aktualnyCzas){
		this->LWP++;
		this->LWM2++;
		this->LKM++;
		this->krzeslaKoniecM2.pop_front();
	}
}

void Koordynator::poczatekObrobkiKrzeselMaszynaII(){
	if((this->LWP > 0) && (this->LWM2 > 0) && (this->PrK > 0)){
		this->LWP--;
		this->LWM2--;
		this->PrK--;
		this->krzeslaKoniecM2.push_back(this->aktualnyCzas + this->czasObrobkiKrzeslaMaszyna2);
	}
}

void Koordynator::koniecObrobkiKrzeselMaszynaI(){
	if(this->krzeslaKoniecM1.front() == this->aktualnyCzas){
		this->LWP++;
		this->LWM1++;
		this->PrK++;
		this->krzeslaKoniecM1.pop_front();
	}
}

void Koordynator::poczatekObrobkiKrzeselMaszynaI(){
	if((this->LWP > 0) && (this->LWM1 > 0) && (this->KK > 0) && (this->KSz == 0)){
		this->LWP--;
		this->LWM2--;
		this->krzeslaKoniecM1.push_back(this->aktualnyCzas + this->czasObrobkiKrzeslaMaszyna1);
	}
}

void Koordynator::set(Parameter param, unsigned val){
	switch(param){
		case Parameter::PrSz:
			this->PrSz1 = val;
			break;
		case Parameter::PrSz2:
			this->PrSz2 = val;
			break;
		case Parameter::PrK:
			this->PrK = val;
			break;
		case Parameter::LSzM:
			this->LSzM = val;
			break;
		case Parameter::LKM:
			this->LKM = val;
			break;
		case Parameter::KSz:
			this->KSz = val;
			break;
		case Parameter::KK:
			this->KK = val;
			break;
		case Parameter::i:
			this->i = val;
			break;
		case Parameter::j:
			this->j = val;
			break;
		case Parameter::LWP:
			this->LWP = val;
			break;
		case Parameter::ZASz:
			this->ZASz = val;
			break;
		case Parameter::ZAK:
			this->ZAK = val;
			break;
		case Parameter::LWM1:
			this->LWM1 = val;
			break;
		case Parameter::LWM2:
			this->LWM2 = val;
			break;
		case Parameter::LWM3:
			this->LWM3 = val;
			break;
		case Parameter::lPracownikow:
			this->LP = val;
			break;
		case Parameter::lMaszyn1:
			this->LM1 = val;
			break;
		case Parameter::lMaszyn2:
			this->LM2 = val;
			break;
		case Parameter::lMaszyn3:
			this->LM3 = val;
			break;
		case Parameter::aktualnyCzas:
			this->aktualnyCzas = val;
			break;
	}
}

unsigned Koordynator::get(Parameter param){
	switch(param){
		case Parameter::PrSz:
			return this->PrSz1;
			break;
		case Parameter::PrSz2:
			return this->PrSz2;
			break;
		case Parameter::PrK:
			return this->PrK;
			break;
		case Parameter::LSzM:
			return this->LSzM;
			break;
		case Parameter::LKM:
			return this->LKM;
			break;
		case Parameter::KSz:
			return this->KSz;
			break;
		case Parameter::KK:
			return this->KK;
			break;
		case Parameter::i:
			return this->i;
			break;
		case Parameter::j:
			return this->j;
			break;
		case Parameter::LWP:
			return this->LWP;
			break;
		case Parameter::ZASz:
			return this->ZASz;
			break;
		case Parameter::ZAK:
			return this->ZAK;
			break;
		case Parameter::LWM1:
			return this->LWM1;
			break;
		case Parameter::LWM2:
			return this->LWM2;
			break;
		case Parameter::LWM3:
			return this->LWM3;
			break;
		case Parameter::lPracownikow:
			return this->LP;
			break;
		case Parameter::lMaszyn1:
			return this->LM1;
			break;
		case Parameter::lMaszyn2:
			return this->LM2;
			break;
		case Parameter::lMaszyn3:
			return this->LM3;
			break;
		case Parameter::aktualnyCzas:
			return this->aktualnyCzas;
			break;
		default:
			return 0;
			break;
	};
}

std::ostream& operator<<(std::ostream &output, const Koordynator& koor){
	output << " Liczba przetworzonych szaf na maszynie I i II  " << koor.PrSz1 << " " << koor.PrSz2 << std::endl;
	output << " Liczba przetworzonych na maszynie I krzeseł " << koor.PrK << std::endl;
	output << " Liczba szaf i krzesełw magazynie (gotowych) " << koor.LSzM << " " <<  koor.LKM << std::endl;
	output << " Liczba szaf i krzeseł czekających w kolejce na obróbke " << koor.KSz << " " << koor.KK << std::endl;
	output << " Liczba zrealizowanych zamówień " << koor.i << std::endl;
	output << " Liczba zamówień, które przybyły do systemu " << koor.j << std::endl;
	output << " Liczba wolnych pracow    " << koor.LWP << std::endl;
	output << " Zapotrzebowanie na szafy " << koor.ZASz << std::endl;
	output << " Zapotrzebowanie na krzes " << koor.ZAK << std::endl;
	output << " Liczba wolnych maszyn I   " << koor.LWM1 << std::endl;
	output << " Liczba wolnych maszyn II  " << koor.LWM2 << std::endl;
	output << " Liczba wolnych maszyn III " << koor.LWM3 << std::endl;
	/*
	output << " Liczba pracowników" << koor.LP << std::endl;
	output << " Liczba maszyn 1 " << koor.LM1 << std::endl;
	output << " Liczba maszyn 2 " << koor.LM2 << std::endl;
	output << " Liczba maszyn 3 " << koor.LM3 << std::endl;
	*/
	output << " Czas " << koor.aktualnyCzas << std::endl;
	return output;
}
