#include <iostream>
#include "Bramka.hpp"

using namespace std;

class OR :public Bramka
{
public:
    OR(int, string, int, int);
    int Wynik(int, int);
};
