/*
 * pracownik.cpp
 *
 *  Created on: 21 maj 2015
 *      Author: rafal
 */


#include "pracownik.h"

Pracownik::Pracownik(): idP(Pracownik::id), czo1(0), czo2(0), czo3(0), status(statusPracownika::wolny){
	Pracownik::id++;
	Pracownik::lp++;
	Pracownik::lwp++;
}

Pracownik::Pracownik(const Pracownik& p): idP(p.idP), czo1(p.czo1), czo2(p.czo2), czo3(p.czo3), status(p.status){
	Pracownik::id++;
	Pracownik::lp++;
	if(p.status == statusPracownika::wolny) Pracownik::lwp++;
}

Pracownik::~Pracownik(){
	Pracownik::lp--;
	if(this->status == statusPracownika::wolny) Pracownik::lwp--;
}

Pracownik& Pracownik::operator=(const Pracownik& p){
	this->idP = p.idP;
	this->czo1 = p.czo1;
	this->czo2 = p.czo2;
	this->czo2 = p.czo3;
	statusPracownika poprzedni = this->status;
	this->status = p.status;

	//todo ogarnąć należy lwp, lp przy używaniu operatora przypisania
	if((poprzedni != statusPracownika::wolny) && (this->status == statusPracownika::wolny))
		Pracownik::lwp++;

	if((poprzedni == statusPracownika::wolny) && (this->status != statusPracownika::wolny))
		Pracownik::lwp--;

	return *this;
}

void Pracownik::set(Parameter param, unsigned int val){
	switch(param){
		case Parameter::idPracownika:
			this->idP = val;
			break;

		case Parameter::liczbaPracownikow:
			Pracownik::lp = val;
			break;

		case Parameter::liczbaWolnychPracownikow:
			Pracownik::lwp = val;
			break;

		case Parameter::czasObrobkiMaszyna1:
			this->czo1 = val;
			break;

		case Parameter::czasObrobkiMaszyna2:
			this->czo2 = val;
			break;

		case Parameter::czasObrobkiMaszyna3:
			this->czo3 = val;
			break;
	};
}

unsigned int Pracownik::get(Parameter param){
	switch(param){
		case Parameter::idPracownika:
			return this->idP;
			break;

		case Parameter::liczbaPracownikow:
			return Pracownik::lp;
			break;

		case Parameter::liczbaWolnychPracownikow:
			return Pracownik::lwp;
			break;

		case Parameter::czasObrobkiMaszyna1:
			return this->czo1;
			break;

		case Parameter::czasObrobkiMaszyna2:
			return this->czo2;
			break;

		case Parameter::czasObrobkiMaszyna3:
			return this->czo3;
			break;

		default:
			return 0;
			break;
	};
}
