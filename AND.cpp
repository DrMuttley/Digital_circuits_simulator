#include <iostream>
#include "AND.hpp"

using namespace std;

AND::AND(int NrWyj, string Nazwa, int NrW1, int NrW2) :Bramka(NrWyj, Nazwa, NrW1, NrW2)
{
}

int AND::Wynik(int WarWej1, int WarWej2)
{
    WartoscWejscia1 = WarWej1;
    WartoscWejscia2 = WarWej2;

    if ((WartoscWejscia1 == 1) && (WartoscWejscia2 == 1))
    {
        return 1;
    }
    else return 0;
}
