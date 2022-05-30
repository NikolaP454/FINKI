#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

/// Functions * ////////////////////////////////////////////


/// Exception classes //////////////////////////////////////



/// Classes ////////////////////////////////////////////////

class Vozac
{
protected:
    char ime[100];
    int age;
    int races;
    bool vet;

    void copy(const Vozac & x){
        strcpy(ime, x.ime);
        age = x.age;
        races = x.races;
        vet = x.vet;
    }

public:
    Vozac(char * i, int a, int r, bool v):
        age(a), races(r), vet(v) { strcpy(ime, i); }
    Vozac(const Vozac & x) { copy(x); }
    ~Vozac() {}

    friend ostream & operator << (ostream &os, const Vozac & x){
        os << x.ime << "\n" << x.age << "\n" << x.races << "\n";

        if(x.vet) os << "VETERAN\n";
        return os;
    }

    virtual double zarabotuvacka() = 0;
    virtual double danok() = 0;

    bool operator == (Vozac & x){
        return zarabotuvacka() == x.zarabotuvacka();
    }

    void operator = (const Vozac & x){ copy(x); }
};

class Avtomobilist : public Vozac
{
private:
    double cena;

public:
    Avtomobilist(char * i, int a, int r, bool v, double c):
        Vozac(i,a,r,v), cena(c) {}

    Avtomobilist(const Avtomobilist & x): Vozac(x), cena(x.cena) {}

    ~Avtomobilist() {}

    double zarabotuvacka() {
        return cena * 0.2;
    }

    double danok() {
        return ( (races > 10)? 0.15 : 0.1 ) * Avtomobilist::zarabotuvacka();
    }
};

class Motociklist : public Vozac
{
private:
    int moknost;

public:
    Motociklist(char * i, int a, int r, bool v, int m):
        Vozac(i,a,r,v), moknost(m) {}

    Motociklist(const Motociklist & x): Vozac(x), moknost(x.moknost) {}

    ~Motociklist() {}

    double zarabotuvacka() {
        return moknost * 20;
    }

    double danok() {
        return ( (vet)? 0.25 : 0.2 ) * Motociklist::zarabotuvacka();
    }
};


/// Functions //////////////////////////////////////////////

int soIstaZarabotuvachka(Vozac ** arr, int n, Vozac * x){
   int ans = 0;
   for(int i = 0; i < n; i++){
        if(*arr[i] == *x )
            ++ans;
   }

   return ans;
}

/// Main ///////////////////////////////////////////////////

// vashiot kod ovde

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}


/// 1. Dali moze vakov file?
/// 2. Dali moze abbreviation?
