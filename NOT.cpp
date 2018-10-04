#include <iostream>
#include "NOT.hpp"

using namespace std;

NOT::NOT(int NrWyj, string Nazwa, int NrW)
{
    NrWyjscia = NrWyj;
    NazwaBramki = Nazwa;
    NrWejscia = NrW;
}

int NOT::wynik(int WarWej)
{
    WartoscWejscia = WarWej;

    if (WartoscWejscia == 1)
    {
        return 0;
    }
    else return 1;
}

