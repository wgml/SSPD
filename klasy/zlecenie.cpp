/*
 * zlecenie.cpp
 *
 *  Created on: 22 maj 2015
 *      Author: rafal
 */


#include "zlecenie.h"

unsigned int Zlecenie::id = 1;

Zlecenie::Zlecenie():Nr(Zlecenie::id), CzP(0), CzW(0), ZAKs(0), ZAK(0){
	Zlecenie::id++;
}

Zlecenie::Zlecenie(unsigned krzesla, unsigned szafy, unsigned przybycie, unsigned wyjscie):
	Nr(Zlecenie::id), CzP(przybycie), CzW(wyjscie), ZAK(krzesla),  ZAKs(szafy){
	Zlecenie::id++;
}

Zlecenie::Zlecenie(const Zlecenie& z):Nr(z.Nr), CzP(z.CzP), CzW(z.CzW), ZAKs(z.ZAKs), ZAK(z.ZAK){}


Zlecenie& Zlecenie::operator=(const Zlecenie & z){
	this->Nr = z.Nr;
	this->CzP = z.CzP;
	this->CzW = z.CzW;
	this->ZAKs = z.ZAKs;
	this->ZAK = z.ZAK;

	return *this;
}

bool Zlecenie::operator<(const Zlecenie& z){
	return this->Nr < z.Nr;
}

bool Zlecenie::operator==(const Zlecenie& z){
	return this->Nr == z.Nr;
}

std::ostream& operator<<(std::ostream& output, const Zlecenie& z){
	output << "Zlecenie nr=" << z.Nr << " parametry=" << z.CzP << " " << z.CzW << " " << z.ZAKs << " " << z.ZAK;
	return output;
}

void Zlecenie::nrZlecenia(unsigned v){
	this->Nr = v;
}

void Zlecenie::czasWyjscia(unsigned v){
	this->CzW = v;
}

void Zlecenie::czasPrzybycia(unsigned v){
	this->CzP = v;
}

void Zlecenie::zapotrzebowanieKrzesla(unsigned v){
	this->ZAK = v;
}

void Zlecenie::zapotrzebowanieSzafy(unsigned v){
	this->ZAKs = v;
}

unsigned Zlecenie::nrZlecenia(){
	return this->Nr;
}

unsigned Zlecenie::czasWyjscia(){
	return this->CzW;
}

unsigned Zlecenie::czasPrzybycia(){
	return this->CzP;
}

unsigned Zlecenie::zapotrzebowanieKrzesla(){
	return this->ZAK;
}

unsigned Zlecenie::zapotrzebowanieSzafy(){
	return this->ZAKs;
}
