#include <iostream>
#include "NAND.hpp"

using namespace std;

NAND::NAND(int NrWyj, string Nazwa, int NrW1, int NrW2) :Bramka(NrWyj, Nazwa, NrW1, NrW2)
{
}

int NAND::Wynik(int WarWej1, int WarWej2)
{
    WartoscWejscia1 = WarWej1;
    WartoscWejscia2 = WarWej2;

    if ((WartoscWejscia1 == 1) && (WartoscWejscia2 == 1))
    {
        return 0;
    }
    else return 1;
}
