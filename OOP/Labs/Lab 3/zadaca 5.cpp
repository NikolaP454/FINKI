#include<iostream>
#include<cstring>
using namespace std;

class Rabotnik
{
private:
    char ime[30];
    char prezime[30];
    int plata;

public:
    Rabotnik(): ime(""), prezime(""), plata(0) {};
    Rabotnik(char *i, char *p, int pl): plata(pl) {
        strcpy(ime, i);
        strcpy(prezime, p);
    }
    Rabotnik(const Rabotnik &r): plata(r.plata){
        strcpy(ime, r.ime);
        strcpy(prezime, r.prezime);
    }
    ~Rabotnik() {};

    int getPlata() { return plata; }
    
    void pecati(){
        cout << ime << " " << prezime << " " << plata << endl;
    }
};

class Fabrika
{
private:
    Rabotnik rabotnici[100];
    int brojVraboteni;

public:
    Fabrika(): brojVraboteni(0) {};
    Fabrika(Rabotnik * r, int n): brojVraboteni(n){
        for(int i = 0; i < n; i++)
            rabotnici[i] = r[i];
    }
    ~Fabrika() {};
    
    void pecatiVraboteni(){
        cout << "Site vraboteni:" << endl;

        for(int i = 0; i < brojVraboteni; i++){
            rabotnici[i].pecati();
        }
    }

    void pecatiSoPlata(int plata){
        cout << "Vraboteni so plata povisoka od " << plata << " :" << endl;

        for(int i = 0; i < brojVraboteni; i++){
            if(rabotnici[i].getPlata() > plata)
                rabotnici[i].pecati();
        }
    }
};


int main()
{
    int n; cin >> n;

    Rabotnik r[n];
    for(int i = 0; i < n; i++){
        char ime[30]; cin >> ime;
        char prezime[30]; cin >> prezime;
        int plata; cin >> plata;

        Rabotnik rabotnik(ime, prezime, plata);
        r[i] = rabotnik;
    }

    int plata; cin >> plata;

    Fabrika fabrika(r, n);
    fabrika.pecatiVraboteni();
    fabrika.pecatiSoPlata(plata);
}