/*
 * koordynator.cpp
 *
 *  Created on: 22 maj 2015
 *      Author: rafal
 */

#include "koordynator.h"
#include <algorithm>
#include <random>
#include <ctime>

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

	std::default_random_engine generator(time(NULL));
	std::uniform_int_distribution<unsigned> genCzasu(this->czasD, this->czasG);
	std::uniform_int_distribution<unsigned> genKrzesel(this->krzeslaD, this->krzeslaG);
	std::uniform_int_distribution<unsigned> genSzaf(this->szafyD, this->szafyG);

	while(this->aktualnyCzas <= this->dlugoscSymulacji){
		unsigned nowyCzas 	 = genCzasu(generator);
		unsigned noweKrzesla = genKrzesel(generator);
		unsigned noweSzafy	 = genSzaf(generator);

		//zabezpieczenie przed dodawaniem "pustych zleceń"
		while((noweKrzesla == 0) && (noweSzafy == 0)){
            noweKrzesla = genKrzesel(generator);
            noweSzafy	 = genSzaf(generator);
		}

		this->aktualnyCzas += nowyCzas;

		Zlecenie noweZlecenie = Zlecenie(noweKrzesla, noweSzafy, this->aktualnyCzas);

		this->zleceniaPrzybywajace.push_back(noweZlecenie);
	}

	this->aktualnyCzas = 0;

}

void Koordynator::sim(unsigned n){
	for(unsigned i=0; i<n; i++){
		this->aktualnyCzas++;

		this->koniecWyjsciaZlecenia();
		this->poczatekWyjsciaZlecenia();		//tutaj została zamieniona kolejność #Artur!!
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
	auto it = std::find_if(this->zleceniaOczekujace.begin(), this->zleceniaOczekujace.end(),
	[&](Zlecenie z){
		return (this->LSzM >= z.zapotrzebowanieSzafy()) && (this->LKM >= z.zapotrzebowanieKrzesla());
	});

	if(it != this->zleceniaOczekujace.end()){
		it->czasWyjscia(this->aktualnyCzas);
		this->LSzM -= it->zapotrzebowanieSzafy();
		this->ZASz -= it->zapotrzebowanieSzafy();
		this->LKM  -= it->zapotrzebowanieKrzesla();
		this->ZAK  -= it->zapotrzebowanieKrzesla();
		this->zleceniaZrealizowane.push_back(*it);
		this->zleceniaOczekujace.remove(*it);
		this->i++;
	}

}

void Koordynator::poczatekWyjsciaZlecenia(){
	//połączone z  koniecWyjsciaZlecenia
}

void Koordynator::poczatekRealizacji(){
	//połączone z  przybycieZlecenia
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
		this->LWM1--;
		this->KK--;
		this->krzeslaKoniecM1.push_back(this->aktualnyCzas + this->czasObrobkiKrzeslaMaszyna1);
	}
}

unsigned Koordynator::getOrderChairs(unsigned orderID){
	unsigned s1 = this->zleceniaOczekujace.size();
	unsigned s2 = this->zleceniaPrzybywajace.size();
	unsigned s3 = this->zleceniaZrealizowane.size();
	unsigned s = s1 + s2 + s3;

	if(orderID > s) return 0;

	auto itPrzyb = std::find_if(this->zleceniaPrzybywajace.begin(), this->zleceniaPrzybywajace.end(),
	[&](Zlecenie z){
		return z.nrZlecenia() == orderID;
	});

	if(itPrzyb != this->zleceniaPrzybywajace.end()){
		return itPrzyb->zapotrzebowanieKrzesla();
	}

	auto itOczek = std::find_if(this->zleceniaOczekujace.begin(), this->zleceniaOczekujace.end(),
	[&](Zlecenie z){
		return z.nrZlecenia() == orderID;
	});

	if(itOczek != this->zleceniaOczekujace.end()){
			return itOczek->zapotrzebowanieKrzesla();
	}

	auto itZreal = std::find_if(this->zleceniaZrealizowane.begin(), this->zleceniaZrealizowane.end(),
	[&](Zlecenie z){
		return z.nrZlecenia() == orderID;
	});

	if(itZreal != this->zleceniaZrealizowane.end()){
			return itZreal->zapotrzebowanieKrzesla();
	}

}

unsigned Koordynator::getOrderWardrobes(unsigned orderID){
	unsigned s1 = this->zleceniaOczekujace.size();
	unsigned s2 = this->zleceniaPrzybywajace.size();
	unsigned s3 = this->zleceniaZrealizowane.size();
	unsigned s = s1 + s2 + s3;

	if(orderID > s) return 0;

	auto itPrzyb = std::find_if(this->zleceniaPrzybywajace.begin(), this->zleceniaPrzybywajace.end(),
	[&](Zlecenie z){
		return z.nrZlecenia() == orderID;
	});

	if(itPrzyb != this->zleceniaPrzybywajace.end()){
		return itPrzyb->zapotrzebowanieSzafy();
	}

	auto itOczek = std::find_if(this->zleceniaOczekujace.begin(), this->zleceniaOczekujace.end(),
	[&](Zlecenie z){
		return z.nrZlecenia() == orderID;
	});

	if(itOczek != this->zleceniaOczekujace.end()){
			return itOczek->zapotrzebowanieSzafy();
	}

	auto itZreal = std::find_if(this->zleceniaZrealizowane.begin(), this->zleceniaZrealizowane.end(),
	[&](Zlecenie z){
		return z.nrZlecenia() == orderID;
	});

	if(itZreal != this->zleceniaZrealizowane.end()){
			return itZreal->zapotrzebowanieSzafy();
	}

}

unsigned Koordynator::getOrderTime(unsigned orderID){
	unsigned s1 = this->zleceniaOczekujace.size();
	unsigned s2 = this->zleceniaPrzybywajace.size();
	unsigned s3 = this->zleceniaZrealizowane.size();
	unsigned s = s1 + s2 + s3;

	if(orderID > s) return 0;

	auto itPrzyb = std::find_if(this->zleceniaPrzybywajace.begin(), this->zleceniaPrzybywajace.end(),
	[&](Zlecenie z){
		return z.nrZlecenia() == orderID;
	});

	if(itPrzyb != this->zleceniaPrzybywajace.end()){
		return itPrzyb->czasPrzybycia();
	}

	auto itOczek = std::find_if(this->zleceniaOczekujace.begin(), this->zleceniaOczekujace.end(),
	[&](Zlecenie z){
		return z.nrZlecenia() == orderID;
	});

	if(itOczek != this->zleceniaOczekujace.end()){
			return itOczek->czasPrzybycia();
	}

	auto itZreal = std::find_if(this->zleceniaZrealizowane.begin(), this->zleceniaZrealizowane.end(),
	[&](Zlecenie z){
		return z.nrZlecenia() == orderID;
	});

	if(itZreal != this->zleceniaZrealizowane.end()){
			return itZreal->czasPrzybycia();
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
	output << " Liczba szaf i krzeseł czekających na rozp   " << koor.KSz << " " << koor.KK << std::endl;
	output << " Liczba zrealizowanych zamówień " << koor.i << std::endl;
	output << " Liczba zamówień                " << koor.j << std::endl;
	output << " Liczba wolnych pracow    " << koor.LWP << std::endl;
	output << " Zapotrzebowanie szafy krzes    " << koor.ZASz << " " << koor.ZAK <<std::endl;
	output << " Liczba wolnych maszyn I II III " << koor.LWM1 << " " << koor.LWM2 << " " <<  koor.LWM3 <<std::endl;
	output << " Czas " << koor.aktualnyCzas << std::endl;
	return output;
}
