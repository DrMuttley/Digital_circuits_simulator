#include <iostream>
#include "Bramka.hpp"

using namespace std;

class NAND :public Bramka
{
public:
    NAND(int, string, int, int);
    int Wynik(int, int);
};
