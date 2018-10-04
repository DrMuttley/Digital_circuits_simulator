#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include "AND.hpp"
#include "OR.hpp"
#include "NAND.hpp"
#include "NOR.hpp"
#include "XOR.hpp"
#include "NOT.hpp"

using namespace std;

struct elementSchematu
{
    int nrWyjsciaBramki;
    string NazwaBramki;
    int nrWejscia1;
    int nrWejscia2;
    int wejscieNOTa;
};

void WczytajPlikWejSygnaly(vector<elementSchematu> &, int, string, string);
int WczytajPlikWejSchemat(vector<elementSchematu> &, string);
void DodajNieNOTa(vector<elementSchematu> &,int, string, int, int);
void DodajNOTa(vector<elementSchematu> &,int, string, int);
void PokazSchematUkladu(vector<int>, vector<elementSchematu>, int, int, int[]);
int RozmiarTablicyWynikow(vector<elementSchematu> &);
void WartoscWyjsciaUkladu(vector<int>&, vector<elementSchematu> &, int, int, string);
void EksportujWynikiDoPliku(int, int[], vector<int>, int, string);
void PobierzDaneZLinii(int, char*[],string[]);

int main(int argc, char** argv)
{
    string TabNazwPlikow[3];

    PobierzDaneZLinii(argc, argv, TabNazwPlikow);

    vector<elementSchematu> TabSchemat;
    int liczbaBramek;
    liczbaBramek = WczytajPlikWejSchemat(TabSchemat, TabNazwPlikow[1]);
    int WyjscieUkladu = RozmiarTablicyWynikow(TabSchemat);
    WczytajPlikWejSygnaly(TabSchemat, WyjscieUkladu,
                          TabNazwPlikow[0], TabNazwPlikow[2]);

    return 0;
}

void WczytajPlikWejSygnaly(vector<elementSchematu> &TabSchemat, int MaksNrWyj,
                           string SciezkaSygnal, string SciezkaWyniki)
{
    int liczbaWierszy = 0;

    vector <int> TablicaSygnalow;

    fstream PlikSygnaly;
    char znak;
    int sygnal;

    PlikSygnaly.open(SciezkaSygnal.c_str(),ios::in);
    if(!PlikSygnaly.good())
    {
        cout<<endl<<"Blad otwarcia pliku z sygnalami!!!"<<endl;
        exit(0);
    }
    znak = PlikSygnaly.get();

    while(!PlikSygnaly.eof())
    {
        liczbaWierszy++;

        while ((znak != '\n')&&(!PlikSygnaly.eof()))
        {
            if(znak != ' ')
            {
                sygnal = static_cast<int>(znak);
                sygnal = sygnal - 48;
                TablicaSygnalow.push_back(sygnal);
            }
            znak = PlikSygnaly.get();
        }
        if(!PlikSygnaly.eof())
        {
            WartoscWyjsciaUkladu(TablicaSygnalow, TabSchemat,
                                 liczbaWierszy, MaksNrWyj, SciezkaWyniki);

            TablicaSygnalow.clear();
            znak = PlikSygnaly.get();
        }
    }
    PlikSygnaly.close();
}

int WczytajPlikWejSchemat(vector<elementSchematu> &tab, string Sciezka)
{
    int MaxNrWyjscia = 0;
    int licznikWierszy = 0;

    fstream PlikWejSchemat;
    int WyjscieBramki,WejscieJeden, WejscieDwa, WejscieNot;
    string NazwaBramki;

    PlikWejSchemat.open(Sciezka.c_str(),ios::in);

    if(!PlikWejSchemat.good())
    {
        cout<<endl<<"Blad otwarcia pliku z schematem!!!"<<endl;
        exit(0);
    }
    while(!PlikWejSchemat.eof())
    {
        PlikWejSchemat>>WyjscieBramki>>NazwaBramki;

        if(WyjscieBramki > MaxNrWyjscia)
        {
            MaxNrWyjscia = WyjscieBramki;
        }

        if(NazwaBramki != "NOT")
        {
            PlikWejSchemat>>WejscieJeden>>WejscieDwa;

            DodajNieNOTa(tab, WyjscieBramki, NazwaBramki,
                         WejscieJeden, WejscieDwa);
        }
        else
        {
            PlikWejSchemat>>WejscieNot;

            DodajNOTa(tab, WyjscieBramki, NazwaBramki, WejscieNot);
        }
        licznikWierszy++;
    }
    PlikWejSchemat.close();

    return licznikWierszy;
}

void DodajNieNOTa(vector<elementSchematu> &tab,
                  int wyjBramki, string nazBramki, int wej1, int wej2)
{
    if(nazBramki != "NOT")
    {
        elementSchematu element;
        element.nrWyjsciaBramki = wyjBramki;
        element.NazwaBramki = nazBramki;
        element.nrWejscia1 = wej1;
        element.nrWejscia2 = wej2;
        element.wejscieNOTa = -1;
        tab.push_back(element);
    }
}

void DodajNOTa(vector<elementSchematu> &tab,
                  int wyjBramki, string nazBramki, int wejN)
{
    elementSchematu element;
    element.nrWyjsciaBramki = wyjBramki;
    element.NazwaBramki = nazBramki;
    element.nrWejscia1 = -1;
    element.nrWejscia2 = -1;
    element.wejscieNOTa = wejN;
    tab.push_back(element);
}

void PokazSchematUkladu(vector<int> TablicaSygnalow,
                        vector<elementSchematu> TablicaSchemat,
                        int NumerTestu, int NumerWyjsciaUkladu,
                        int TabWynikow[])
{
    if(NumerTestu == 1)
    {
        cout<<endl;
    }
    cout<<"Wyniki testu nr: "<<NumerTestu<<endl<<endl<<"Sygnaly wejsiowe: ";

    for(int i=0; i<TablicaSygnalow.size(); i++)
    {
        cout<<TablicaSygnalow[i]<<" ";
    }
    cout<<endl<<endl<<"Schemat ukladu: "<<endl;
    for(int i=0; i<TablicaSchemat.size(); i++)
    {
        if(TablicaSchemat[i].NazwaBramki != "NOT")
        {
            cout<<TablicaSchemat[i].nrWyjsciaBramki<<" ";
            cout<<TablicaSchemat[i].NazwaBramki<<" ";
            cout<<TablicaSchemat[i].nrWejscia1<<" ";
            cout<<TablicaSchemat[i].nrWejscia2<<endl;
        }
        else
        {
            cout<<TablicaSchemat[i].nrWyjsciaBramki<<" ";
            cout<<TablicaSchemat[i].NazwaBramki<<" ";
            cout<<TablicaSchemat[i].wejscieNOTa<<endl;
        }
    }
    cout<<endl<<"Wynik na wysjciu ukladu: ";
    cout<<TabWynikow[NumerWyjsciaUkladu-1]<<endl;
    cout<<"------------"<<endl<<endl<<endl;
}

int RozmiarTablicyWynikow(vector<elementSchematu> &tab)
{
    int OstatnieWyjscie = tab[0].nrWyjsciaBramki;

    for(int i=0; i<tab.size(); i++)
    {
        if(tab[i].nrWyjsciaBramki > OstatnieWyjscie)
        {
            OstatnieWyjscie = tab[i].nrWyjsciaBramki;
        }
    }
    return OstatnieWyjscie;
}

void WartoscWyjsciaUkladu(vector<int> &TabSygnalow,
                          vector<elementSchematu> &TabSchemat,
                          int NrTestu, int NrWyjsciaUkladu, string SciezkaWyniki)
{
    int TablicaWynikowa[NrWyjsciaUkladu];

    for(int i=0; i<TabSygnalow.size(); i++)
    {
        TablicaWynikowa[i] = TabSygnalow[i];
    }
    for(int i=0; i<TabSchemat.size(); i++)
    {
        if(TabSchemat[i].NazwaBramki == "AND")
        {
            AND and1(TabSchemat[i].nrWyjsciaBramki, TabSchemat[i].NazwaBramki,
                     TabSchemat[i].nrWejscia1, TabSchemat[i].nrWejscia2);

            TablicaWynikowa[TabSchemat[i].nrWyjsciaBramki-1] =

            and1.Wynik(TablicaWynikowa[TabSchemat[i].nrWejscia1-1],
                       TablicaWynikowa[TabSchemat[i].nrWejscia2-1]);
        }
        if(TabSchemat[i].NazwaBramki == "NAND")
        {
            NAND nand1(TabSchemat[i].nrWyjsciaBramki, TabSchemat[i].NazwaBramki,
                     TabSchemat[i].nrWejscia1, TabSchemat[i].nrWejscia2);

            TablicaWynikowa[TabSchemat[i].nrWyjsciaBramki-1] =

            nand1.Wynik(TablicaWynikowa[TabSchemat[i].nrWejscia1-1],
                       TablicaWynikowa[TabSchemat[i].nrWejscia2-1]);
        }
        if(TabSchemat[i].NazwaBramki == "OR")
        {
            OR or1(TabSchemat[i].nrWyjsciaBramki, TabSchemat[i].NazwaBramki,
                     TabSchemat[i].nrWejscia1, TabSchemat[i].nrWejscia2);

            TablicaWynikowa[TabSchemat[i].nrWyjsciaBramki-1] =

            or1.Wynik(TablicaWynikowa[TabSchemat[i].nrWejscia1-1],
                       TablicaWynikowa[TabSchemat[i].nrWejscia2-1]);
        }
        if(TabSchemat[i].NazwaBramki == "NOR")
        {
            NOR nor1(TabSchemat[i].nrWyjsciaBramki, TabSchemat[i].NazwaBramki,
                     TabSchemat[i].nrWejscia1, TabSchemat[i].nrWejscia2);

            TablicaWynikowa[TabSchemat[i].nrWyjsciaBramki-1] =

            nor1.Wynik(TablicaWynikowa[TabSchemat[i].nrWejscia1-1],
                       TablicaWynikowa[TabSchemat[i].nrWejscia2-1]);
        }
        if(TabSchemat[i].NazwaBramki == "XOR")
        {
            XOR xor1(TabSchemat[i].nrWyjsciaBramki, TabSchemat[i].NazwaBramki,
                     TabSchemat[i].nrWejscia1, TabSchemat[i].nrWejscia2);

            TablicaWynikowa[TabSchemat[i].nrWyjsciaBramki-1] =

            xor1.Wynik(TablicaWynikowa[TabSchemat[i].nrWejscia1-1],
                       TablicaWynikowa[TabSchemat[i].nrWejscia2-1]);
        }
        if(TabSchemat[i].NazwaBramki == "NOT")
        {
            NOT nt1(TabSchemat[i].nrWyjsciaBramki, TabSchemat[i].NazwaBramki,
                     TabSchemat[i].wejscieNOTa);

            TablicaWynikowa[TabSchemat[i].nrWyjsciaBramki-1] =

            nt1.wynik(TablicaWynikowa[TabSchemat[i].wejscieNOTa-1]);
        }
    }
    PokazSchematUkladu(TabSygnalow, TabSchemat, NrTestu,
                      NrWyjsciaUkladu, TablicaWynikowa);

    EksportujWynikiDoPliku(NrWyjsciaUkladu, TablicaWynikowa,
                           TabSygnalow, NrTestu, SciezkaWyniki);
}

void EksportujWynikiDoPliku(int Rozmiar, int TabWynikow[],
                            vector<int> TablicaSyg, int NumerTestu,
                            string SciezkaWyniki)
{
    fstream PlikWyjsciowy;

    if(NumerTestu == 1)
    {
        PlikWyjsciowy.open(SciezkaWyniki.c_str(),ios::out);

        if(!PlikWyjsciowy.good())
        {
        cout<<"Pojawil sie problem przy eksporcie"
            <<" wynikow do pliku!"<<endl;
        exit(0);
        }
    }
    else
    {
        PlikWyjsciowy.open(SciezkaWyniki.c_str(),ios::app);

        if(!PlikWyjsciowy.good())
        {
        cout<<"Pojawil sie problem przy eksporcie"
            <<" wynikow do pliku!"<<endl;
        exit(0);
        }
    }
    PlikWyjsciowy<<"[";

    for(int i=0; i<TablicaSyg.size(); i++)
    {
        PlikWyjsciowy<<TabWynikow[i];
        if(i<TablicaSyg.size()-1)
        {
            PlikWyjsciowy<<" ";
        }
    }
    PlikWyjsciowy<<"] -> "<<TabWynikow[Rozmiar-1]<<endl;

    PlikWyjsciowy.close();
}

void PobierzDaneZLinii(int RozmiarTabLinia, char* TabDaneZLinii[],
                       string TabNazw[])
{
    string NazwaPlikuSygnaly, NazwaPlikuSchemat, NazwaPlikuWyniki;
    string SciezkaPlikSygnaly, SciezkaPlikSchemat, SciezkaPlikWyniki;

    SciezkaPlikSygnaly = "..\\..\\";//"bin\\Debug\\" uruchamianie z C::B
    SciezkaPlikSchemat = "..\\..\\";//"bin\\Debug\\"
    SciezkaPlikWyniki = "..\\..\\";//"bin\\Debug\\"

    fstream PlikSygnaly, PlikSchemat, PlikWyniki;

    if (((RozmiarTabLinia == 2) && (TabDaneZLinii[1] == "-h"))
        ||(RozmiarTabLinia != 7))
    {
        if(RozmiarTabLinia != 2)
        {
            cout<<endl<<"Podano zbyt mala ilosc parametrow!!!"<<endl
                <<"Uruchom ponownie program i wprowadz parametry ponownie lub "<<endl
                <<"uruchom pomoc (wcisnij klawisz h a nastepnie kaliwsz enter)"<<endl;

            while(getchar() != 104 && getchar() != 13)
            {
                cout<<"To nie jest (h) sprawdz Caps Lock i sprobuj ponownie."<<endl;
            }
        }
        cout<<endl<<"Podaj nazwe pliku z sygnalami (nazwa.txt): ";
        cin>>NazwaPlikuSygnaly;
        SciezkaPlikSygnaly += NazwaPlikuSygnaly;
        TabNazw[0] = SciezkaPlikSygnaly;

        cout<<"Podaj nazwe pliku ze schematem (nazwa.txt): ";
        cin>>NazwaPlikuSchemat;
        SciezkaPlikSchemat += NazwaPlikuSchemat;
        TabNazw[1] = SciezkaPlikSchemat;

        cout<<"Podaj nazwe pliku wyjsciowego (nazwa.txt): ";
        cin>>NazwaPlikuWyniki;
        SciezkaPlikWyniki += NazwaPlikuWyniki;
        TabNazw[2] = SciezkaPlikWyniki;
    }
    else if (RozmiarTabLinia == 7)
    {
        string zmienna = "-i";

        for(int i=1;i<7;i++)
        {
            if(TabDaneZLinii[i] == zmienna)
            {
                NazwaPlikuSygnaly = TabDaneZLinii[i+1];
                SciezkaPlikSygnaly += NazwaPlikuSygnaly;
                TabNazw[0] = SciezkaPlikSygnaly;
            }
        }
        zmienna = "-s";
        for(int i=1;i<7;i++)
        {
            if(TabDaneZLinii[i] == zmienna)
            {
                NazwaPlikuSchemat = TabDaneZLinii[i+1];
                SciezkaPlikSchemat += NazwaPlikuSchemat;
                TabNazw[1] = SciezkaPlikSchemat;
            }
        }
        zmienna = "-o";
        for(int i=1;i<7;i++)
        {
            if(TabDaneZLinii[i] == zmienna)
            {
                NazwaPlikuWyniki = TabDaneZLinii[i+1];
                SciezkaPlikWyniki += NazwaPlikuWyniki;
                TabNazw[2] = SciezkaPlikWyniki;
            }
        }
    }
}
