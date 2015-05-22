/*
 * maszyna.cpp
 *
 *  Created on: 22 maj 2015
 *      Author: rafal
 */


#include "maszyna.h"

unsigned int Maszyna::lm   = 0;
unsigned int Maszyna::lm1  = 0;
unsigned int Maszyna::lwm1 = 0;
unsigned int Maszyna::lm2  = 0;
unsigned int Maszyna::lwm2 = 0;
unsigned int Maszyna::lm3  = 0;
unsigned int Maszyna::lwm3 = 0;

Maszyna::Maszyna(typ t): CzO(0), typMaszyny(t), statusMaszyny(status::wolna){
	Maszyna::lm++;
	switch(this->typMaszyny){
		case typ::maszynaTypu1:
			Maszyna::lm1++;
			Maszyna::lwm1++;
			break;

		case typ::maszynaTypu2:
			Maszyna::lm2++;
			Maszyna::lwm2++;
			break;

		case typ::maszynaTypu3:
			Maszyna::lm3++;
			Maszyna::lwm3++;
			break;
	}
}

Maszyna::Maszyna(const Maszyna& m): CzO(m.CzO), typMaszyny(m.typMaszyny), statusMaszyny(m.statusMaszyny){
	bool w = (this->statusMaszyny == status::wolna)?true:false;
	switch(this->typMaszyny){
		case typ::maszynaTypu1:
			Maszyna::lm1++;
			if(w) Maszyna::lwm1++;
			break;
		case typ::maszynaTypu2:
			Maszyna::lm2++;
			if(w) Maszyna::lwm2++;
			break;
		case typ::maszynaTypu3:
			Maszyna::lm3++;
			if(w) Maszyna::lwm3++;
			break;
	}
}

Maszyna::~Maszyna(){
	Maszyna::lm--;
	bool w = (this->statusMaszyny == status::wolna)?true:false;
	switch(this->typMaszyny){
		case typ::maszynaTypu1:
			Maszyna::lm1--;
			if(w) Maszyna::lwm1--;
			break;
		case typ::maszynaTypu2:
			Maszyna::lm2--;
			if(w) Maszyna::lwm2--;
			break;
		case typ::maszynaTypu3:
			Maszyna::lm3--;
			if(w) Maszyna::lwm3--;
			break;
	}
}

Maszyna& Maszyna::operator=(const Maszyna& m){
	//skasuj informacje o poprzedniej maszynie opisywanej przez obiekt
	bool w = (this->statusMaszyny == status::wolna)?true:false;
	switch(this->typMaszyny){
		case typ::maszynaTypu1:
			Maszyna::lm1--;
			if(w) Maszyna::lwm1--;
			break;
		case typ::maszynaTypu2:
			Maszyna::lm2--;
			if(w) Maszyna::lwm2--;
			break;
		case typ::maszynaTypu3:
			Maszyna::lm3--;
			if(w) Maszyna::lwm3--;
			break;
	}

	this->CzO = m.CzO;
	this->statusMaszyny = m.statusMaszyny;
	this->typMaszyny = m.typMaszyny;

	//dodaj informacje o "nowej" maszynie"
	w = (this->statusMaszyny == status::wolna)?true:false;

	switch(this->typMaszyny){
		case typ::maszynaTypu1:
			Maszyna::lm1++;
			if(w) Maszyna::lwm1++;
			break;
		case typ::maszynaTypu2:
			Maszyna::lm2++;
			if(w) Maszyna::lwm2++;
			break;
		case typ::maszynaTypu3:
			Maszyna::lm3++;
			if(w) Maszyna::lwm3++;
			break;
	}

	return *this;
}

std::ostream& operator<<(std::ostream& output, const Maszyna& m){
	output << "Maszyna ";

	switch(m.typMaszyny){
		case Maszyna::typ::maszynaTypu1:
			output << "typu I, ";
			break;
		case Maszyna::typ::maszynaTypu2:
			output << "typu II, ";
			break;
		case Maszyna::typ::maszynaTypu3:
			output << "typu III, ";
			break;
	}

	switch(m.statusMaszyny){
		case Maszyna::status::wolna:
			output << "wolna";
			break;
		case Maszyna::status::obrobkaSzafy:
			output << "trwa obróbka szaf";
			break;
		case Maszyna::status::obrobkaKrzesla:
			output << "trwa obróbka szaf";
			break;
	}

	return output;
}

void Maszyna::set(Parameter param, unsigned int val){
	switch(param){
		case Parameter::czasObrobki:
			this->CzO = val;
			break;
		case Parameter::liczbaMaszyn:
			Maszyna::lm = val;
			break;
		case Parameter::liczbaMaszynTypu1:
			Maszyna::lm1 = val;
			break;
		case Parameter::liczbaWolnychMaszynTypu1:
			Maszyna::lwm1 = val;
			break;
		case Parameter::liczbaMaszynTypu2:
			Maszyna::lm2 = val;
			break;
		case Parameter::liczbaWolnychMaszynTypu2:
			Maszyna::lwm2 = val;
			break;
		case Parameter::liczbaMaszynTypu3:
			Maszyna::lm3 = val;
			break;
		case Parameter::liczbaWolnychMaszynTypu3:
			Maszyna::lwm3 = val;
			break;
	}
}

unsigned int Maszyna::get(Parameter param){
	switch(param){
		case Parameter::czasObrobki:
			return this->CzO;
			break;
		case Parameter::liczbaMaszyn:
			return Maszyna::lm;
			break;
		case Parameter::liczbaMaszynTypu1:
			return Maszyna::lm1;
			break;
		case Parameter::liczbaWolnychMaszynTypu1:
			return Maszyna::lwm1;
			break;
		case Parameter::liczbaMaszynTypu2:
			return Maszyna::lm2;
			break;
		case Parameter::liczbaWolnychMaszynTypu2:
			return Maszyna::lwm2;
			break;
		case Parameter::liczbaMaszynTypu3:
			return Maszyna::lm3;
			break;
		case Parameter::liczbaWolnychMaszynTypu3:
			return Maszyna::lwm3;
		default:
			return 0;
	}
}
