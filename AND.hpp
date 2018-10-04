#include <iostream>
#include "Bramka.hpp"

using namespace std;

class AND :public Bramka
{
public:
    AND(int, string, int, int);
    int Wynik(int, int);
};
