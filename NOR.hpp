#include <iostream>
#include "Bramka.hpp"

using namespace std;

class NOR :public Bramka
{
public:
    NOR(int, string, int, int);
    int Wynik(int, int);
};
