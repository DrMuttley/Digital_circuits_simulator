#include <iostream>
#include "Bramka.hpp"

using namespace std;

class XOR :public Bramka
{
public:
    XOR(int, string, int, int);
    int Wynik(int, int);
};
