#include <iostream>
#include "XOR.hpp"

using namespace std;

XOR::XOR(int NrWyj, string Nazwa, int NrW1, int NrW2) :Bramka(NrWyj, Nazwa, NrW1, NrW2)
{
}

int XOR::Wynik(int WarWej1, int WarWej2)
{
    WartoscWejscia1 = WarWej1;
    WartoscWejscia2 = WarWej2;

    if (((WartoscWejscia1 == 0) && (WartoscWejscia2 == 0))
        || ((WartoscWejscia1 == 1) && (WartoscWejscia2 == 1)))
    {
        return 0;
    }
    else return 1;
}
