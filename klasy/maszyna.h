/*
 * maszyna.h
 *
 *  Created on: 22 maj 2015
 *      Author: rafal
 */

#ifndef KLASY_MASZYNA_H_
#define KLASY_MASZYNA_H_

#include <iostream>

/**
 * Jedna klasa opisująca trzy typy maszyn.
 * */
class Maszyna{
	public:

		enum class typ{
				maszynaTypu1,
				maszynaTypu2,
				maszynaTypu3
		};

		Maszyna(typ = typ::maszynaTypu1);
		Maszyna(const Maszyna&);
		~Maszyna();
		Maszyna& operator=(const Maszyna&);
		friend std::ostream& operator<<(std::ostream&, const Maszyna&);


		//dla W
		enum class Parameter{

		};
		void set(Parameter, unsigned int);
		unsigned int get(Parameter);

	private:
		//zmienne stanu
		static unsigned int lm;
		static unsigned int lm1;
		static unsigned int lwm1;
		static unsigned int lm2;
		static unsigned int lwm2;
		static unsigned int lm3;
		static unsigned int lwm3;

		//czas opróbki na maszynie
		unsigned int CzO;

		enum class status{
			wolna,
			obrobkaKrzesla,
			obrobkaSzafy
		};

		typ typMaszyny;
		status statusMaszyny;
};


#endif /* KLASY_MASZYNA_H_ */
