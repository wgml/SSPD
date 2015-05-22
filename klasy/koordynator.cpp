/*
 * koordynator.cpp
 *
 *  Created on: 22 maj 2015
 *      Author: rafal
 */

#include "koordynator.h"
#include <algorithm>


unsigned int Koordynator::PrSz = 0;
unsigned int Koordynator::PrK  = 0;
unsigned int Koordynator::LSzM = 0;
unsigned int Koordynator::LKM  = 0;
unsigned int Koordynator::KSz  = 0;
unsigned int Koordynator::KK   = 0;
unsigned int Koordynator::i    = 0;
unsigned int Koordynator::j    = 0;


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

	p->set(Zlecenie::Parameter::czasWyjsciaZlecenia, this->czasSymulacji);

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

}

void Koordynator::poczatekObrobkiMaszynaIII(){

}

void Koordynator::koniecObrobkiSzafMaszynaII(){

}

void Koordynator::poczatekObrobkiSzafMaszynaII(){

}

void Koordynator::koniecObrobkiSzafMaszynaI(){

}

void Koordynator::poczatekObrobkiSzafMaszynaI(){

}

void Koordynator::koniecObrobkiKrzeselMaszynaII(){

}

void Koordynator::poczatekObrobkiKrzeselMaszynaII(){

}

void Koordynator::koniecObrobkiKrzeselMaszynaI(){

}

void Koordynator::poczatekObrobkiKrzeselMaszynaI(){

}

void Koordynator::poczatekRealizacji(){

}

void Koordynator::przybycieZlecenia(){

}

void Koordynator::symuluj(unsigned int n){
	for(unsigned i=0; i<n; i++){
		this->czasSymulacji++;

		this->poczatekWyjsciaZlecenia();
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
