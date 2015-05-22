/*
 * koordynator.cpp
 *
 *  Created on: 22 maj 2015
 *      Author: rafal
 */

#include "koordynator.h"
#include <algorithm>

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

}

void Koordynator::sim(unsigned n){
	for(unsigned i=0; i<n; i++){

		if(this->aktualnyCzas == this->aktualnyCzas) break;
	}
}

void Koordynator::koniecWyjsciaZlecenia(){
	//todo
}

void Koordynator::poczatekWyjsciaZlecenia(){
	//todo
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
	if(this->szafyKoniecM2.front() == this->aktualnyCzas){
		this->LWP++;
		this->LWM2++;
		this->PrSz2++;
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
		this->szafyKoniecM2.push_back(this->aktualnyCzas + this->czasObrobkiSzafyMaszyna2);
	}
}

void Koordynator::koniecObrobkiKrzeselMaszynaI(){

}

void Koordynator::poczatekObrobkiKrzeselMaszynaI(){

}

/*
Koordynator::Koordynator(unsigned int lP, unsigned int lMI, unsigned int lMII, unsigned int lMIII, unsigned int dlSym):
	dlugoscSymulacji(dlSym), czasSymulacji(0){

	this->pracownicy = std::vector<Pracownik>();
	//todo trzeba dodać odpowiednie maszyny
	this->maszyny = std::vector<Maszyna>();
	this->zlecenia = std::list<Zlecenie>();

}

//nagłówki rozpatrywane przez koordynatora


void Koordynator::poczatekWyjsciaZlecenia(){
	std::list<Zlecenie> temp;

	//weź zrealizowane zlecenia
	std::copy_if(this->zlecenia.begin(), this->zlecenia.end(), temp.begin(), [](Zlecenie z){
		return (Koordynator::LSzM >= z.get(Zlecenie::Parameter::zapotrzebowanieNaSzsafy)) &&
				(Koordynator::LKM >= z.get(Zlecenie::Parameter::zapotrzebowanieNaKrzesla));
	});

	//znajdź zlecenie o najmniejszym id
	Zlecenie zrobione = *std::min_element(temp.begin(), temp.end());

	auto p = std::find(this->zlecenia.begin(), this->zlecenia.end(), zrobione);
	if( p != this->zlecenia.end()) p->set(Zlecenie::Parameter::czasWyjsciaZlecenia, this->czasSymulacji);

}

void Koordynator::koniecWyjsciaZlecenia(){
	auto it = std::find_if(this->zlecenia.begin(), this->zlecenia.end(), [&](Zlecenie z){
		return z.get(Zlecenie::Parameter::czasWyjsciaZlecenia) == this->czasSymulacji;
	});

	if(it != this->zlecenia.end()){
		Koordynator::LSzM = Koordynator::LSzM - it->get(Zlecenie::Parameter::zapotrzebowanieNaSzsafy);
		Koordynator::LKM = Koordynator::LKM - it->get(Zlecenie::Parameter::zapotrzebowanieNaKrzesla);
		this->zlecenia.remove(*it);
		Koordynator::i++;
	}

}

void Koordynator::koniecObrobkiMaszynaIII(){
	unsigned int LWP = (this->pracownicy[0]).get(Pracownik::Parameter::liczbaWolnychPracownikow);
	unsigned int LWM3 = (this->maszyny[0].get(Maszyna::Parameter::liczbaWolnychMaszynTypu3));

	if((LWP > 0) && (LWM3 > 0) && (Koordynator::Pr2Sz > 0)){
		// todo trzeba dodać metody dla maszyn i pracowników aby mogli iśc pracować
		Koordynator::Pr2Sz--;
	}
}



void Koordynator::symuluj(unsigned int n){
	for(unsigned i=0; i<n; i++){
		this->czasSymulacji++;

		this->poczatekWyjsciaZlecenia();		//todo tutaj została zamieniona kolejność #Artur!!
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

		if(this->czasSymulacji == this->dlugoscSymulacji) break;
	}

}
*/
