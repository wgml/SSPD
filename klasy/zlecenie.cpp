/*
 * zlecenie.cpp
 *
 *  Created on: 22 maj 2015
 *      Author: rafal
 */


#include "zlecenie.h"

unsigned int Zlecenie::id = 1;
unsigned int Zlecenie::lz = 0;

Zlecenie::Zlecenie():Nr(Zlecenie::id), CzP(0), CzW(0), ZAKs(0), ZAK(0){
	Zlecenie::id++;
	Zlecenie::lz++;
}

Zlecenie::Zlecenie(const Zlecenie& z):Nr(z.Nr), CzP(z.CzP), CzW(z.CzW), ZAKs(z.ZAKs), ZAK(z.ZAK){
	Zlecenie::lz++;
}

Zlecenie::~Zlecenie(){
	Zlecenie::lz--;
}

Zlecenie& Zlecenie::operator=(const Zlecenie & z){
	this->Nr = z.Nr;
	this->CzP = z.CzP;
	this->CzW = z.CzW;
	this->ZAKs = z.ZAKs;
	this->ZAK = z.ZAK;

	return *this;
}

std::ostream& operator<<(std::ostream& output, const Zlecenie& z){
	output << "Zlecenie nr=" << z.Nr << " parametry=" << z.CzP << " " << z.CzW << " " << z.ZAKs << " " << z.ZAK;
	return output;
}

void Zlecenie::set(Parameter param, unsigned int val){
	switch(param){
		case Parameter::nrZlecenia:
			this->Nr = val;
			break;

		case Parameter::czasPrzybyciaZlecenia:
			this->CzP = val;
			break;

		case Parameter::czasWyjsciaZlecenia:
			this->CzW = val;
			break;

		case Parameter::zapotrzebowanieNaSzsafy:
			this->ZAKs = val;
			break;

		case Parameter::zapotrzebowanieNaKrzesla:
			this->ZAK = val;
			break;
	}
}

unsigned int Zlecenie::get(Parameter param){
	switch(param){
		case Parameter::nrZlecenia:
			return this->Nr;
			break;

		case Parameter::czasPrzybyciaZlecenia:
			return this->CzP;
			break;

		case Parameter::czasWyjsciaZlecenia:
			return this->CzW;
			break;

		case Parameter::zapotrzebowanieNaSzsafy:
			return this->ZAKs;
			break;

		case Parameter::zapotrzebowanieNaKrzesla:
			return this->ZAK;
			break;

		default:
			return 0;
			break;
	}
}
