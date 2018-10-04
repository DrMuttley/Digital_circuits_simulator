#ifndef BRAMKA_H_INCLUDED
#define BRAMKA_H_INCLUDED

#include <iostream>

using namespace std;

class Bramka
{
protected:

    int NumerWyjscia;
    string NazwaBramki;
    int NumerWejscia1;
    int NumerWejscia2;
    int WartoscWejscia1;
    int WartoscWejscia2;
    int WartoscWyjscia;

public:
    Bramka(int, string, int, int);
    virtual int Wynik(int, int) = 0;
};

#endif
