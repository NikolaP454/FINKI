#include <iostream>
#include <cstring>

using namespace std;

class Pica
{
private:
    char ime[15];
    char * sostojki;
    int cena, popust;

public:
    Pica() { sostojki = nullptr; cena = popust = 0; }
    
    Pica(char * i, int c, char * s, int p = 0) : cena(c), popust(p) {
        sostojki = new char[strlen(s) + 1];

        strcpy(ime, i);
        strcpy(sostojki, s);
    }

    Pica(const Pica &p){
        cena = p.cena;
        popust = p.popust;

        sostojki = new char[strlen(p.sostojki) + 1];

        strcpy(ime, p.ime);
        strcpy(sostojki, p.sostojki);
    }

    ~Pica() { delete [] sostojki; }
    
    char * getsostojki() { return sostojki; }
    int getpopust() { return popust; }

    void pecatiOsnova(){
        cout << ime << " - " << sostojki << ", " << cena;
    }

    void pecati(){
        pecatiOsnova();
        cout << endl;
    }
    
    void pecatiPopust(){
        pecatiOsnova();
        cout << " " << (cena * (100 - popust) / 100.0) << endl;
    }
    bool istiSe(Pica &p){ return !strcmp(sostojki, p.getsostojki()); }

    void operator = (const Pica &p){
        cena = p.cena;
        popust = p.popust;

        delete [] sostojki;
        sostojki = new char[strlen(p.sostojki) + 1];

        strcpy(ime, p.ime);
        strcpy(sostojki, p.sostojki);
    }
};

class Picerija
{
private:
    char ime[15];
    Pica * pici;
    int br;

public:
    Picerija() { pici = nullptr; br = 0; }

    Picerija(char * i, Pica * p = nullptr, int b = 0): br(b) {
        strcpy(ime, i);

        if(br) pici = new Pica[br];
        for(int i = 0; i < br; i++)
            pici[i] = p[i];
    }

    Picerija(const Picerija &p){
        br = p.br;
        strcpy(ime, p.ime);

        if(br) pici = new Pica[br];
        for(int i = 0; i < br; i++)
            pici[i] = p.pici[i];
    }

    ~Picerija() { delete [] pici; }

    void setIme(char * i) { strcpy(ime, i); }

    char * getIme() { return ime; }
    
    void dodadi(Pica &p){
        for(int i = 0; i < br; i++){
            if(pici[i].istiSe(p)) return;
        }

        Pica * temp = new Pica[br+1];
        temp[br] = p;

        for(int i = 0; i < br; i++)
            temp[i] = pici[i];

        if(br) delete [] pici;
        pici = new Pica[++br];

        for(int i = 0; i < br; i++)
            pici[i] = temp[i];

        delete [] temp;
    }

    void piciNaPromocija(){
        for(int i = 0; i < br; i++){
            if(!pici[i].getpopust()) continue;

            pici[i].pecatiPopust();
        }
    }

    void operator = (const Picerija &p){
        br = p.br;
        strcpy(ime, p.ime);

        delete [] pici;
        if(br) pici = new Pica[br];

        for(int i = 0; i < br; i++)
            pici[i] = p.pici[i];
    }
};

int main () {

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for(int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp,100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki,100);
        int popust;
        cin >> popust;
        Pica p(imp,cena,sostojki,popust);
        p1.dodadi(p);
    }


    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp,100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki,100);
    int popust;
    cin >> popust;
    Pica p(imp,cena,sostojki,popust);
    p2.dodadi(p);

    cout<<p1.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p1.piciNaPromocija();

    cout<<p2.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p2.piciNaPromocija();

    return 0;
}
