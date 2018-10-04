#include <iostream>
#include "NOR.hpp"

using namespace std;

NOR::NOR(int NrWyj, string Nazwa, int NrW1, int NrW2) :Bramka(NrWyj, Nazwa, NrW1, NrW2)
{
}

int NOR::Wynik(int WarWej1, int WarWej2)
{
    WartoscWejscia1 = WarWej1;
    WartoscWejscia2 = WarWej2;

    if ((WartoscWejscia1 == 0) && (WartoscWejscia2 == 0))
    {
        return 1;
    }
    else return 0;
}
