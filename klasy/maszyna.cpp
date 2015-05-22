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
	output<< "Maszyna ";

	switch(m.typMaszyny){
		case Maszyna::typ::maszynaTypu1:


			break;
		case Maszyna::typ::maszynaTypu2:


			break;
		case Maszyna::typ::maszynaTypu3:


			break;
	}

	return output;
}
