#ifndef DUMMY_H
#define DUMMY_H

typedef enum PARAMETERS {
    TUTAJ,
    LISTA,
    DOSTEPNYCH,
    PARAMETROW
} Parameter;

class Dummy
{
public:
    Dummy() {}

    int get(Parameter p) { return int(p); } // pozwala pobrać wartość dowolnego parametru

    void set(Parameter p, int v) {} // pozwala ustawić parametry takie jak ilość pracowników czy maszyn

    void sim(unsigned time = 1) {} //symuluje zadaną ilość czasu
};

#endif // DUMMY_H
