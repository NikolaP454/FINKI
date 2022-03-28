#include <iostream>
#include <cstring>
using namespace std;

enum zanr {akcija, komedija, drama};

class Film
{
private:
    char * ime;
    int memory;
    zanr tip;

public:
    Film(){
        ime = nullptr;
        memory = 0;
        tip = akcija;
    };

    Film(char * name, int mem, zanr t): memory(mem), tip(t){
        ime = new char[strlen(name) + 1];
        strcpy(ime, name);
    };

    Film(const Film &f): memory(f.memory), tip(f.tip) {
        ime = new char[strlen(f.ime) + 1];
        strcpy(ime, f.ime);
    };

    ~Film(){
        delete [] ime;
    };
    
    zanr getzanr() { return tip; }

    int getsize() { return memory; }

    void pecati(){
        cout << memory << "MB-";
        cout << "\"" << ime << "\"" << endl;
    }

    void operator = (const Film &f){
        memory = f.memory;
        tip = f.tip;

        delete [] ime;
        ime = new char[strlen(f.ime) + 1];
        strcpy(ime, f.ime);
    }
};

class DVD
{
private:
    Film filmovi[5];
    int br;
    int cap;

public:
    DVD(){ br = 0; cap = 0; }

    DVD(int c, Film * films = nullptr, int n = 0): br(n), cap(c){
        for(int i = 0; i < n; i++)
            this->filmovi[i] = films[i];
    }

    DVD(const DVD &dvd){
        br = dvd.br;
        cap = dvd.cap;

        for(int i = 0; i < br; i++)
            filmovi[i] = dvd.filmovi[i];
    }

    ~DVD() {};

    Film getFilm(int i) { return filmovi[i]; }

    int getBroj() { return br; }

    void dodadiFilm(Film f){
        if(br == 5) return;
        if(cap - f.getsize() < 0) return;

        filmovi[br++] = f;
        cap -= f.getsize();
    }

    void pecatiFilmoviDrugZanr(zanr z){
        for(int i = 0; i < br; i++){
            if(z == filmovi[i].getzanr()) continue;

            filmovi[i].pecati();
        }
    }

    float procentNaMemorijaOdZanr(zanr z){
        int sum = 0, tojTip = 0;

        for(int i = 0; i < br; i++){
            if(z == filmovi[i].getzanr())
                tojTip += filmovi[i].getsize();

            sum += filmovi[i].getsize();
        }

        return (tojTip * 100.0) / (sum * 1.0);
    }

    void operator = (const DVD &dvd){
        br = dvd.br;
        cap = dvd.cap;

        for(int i = 0; i < br; i++)
            filmovi[i] = dvd.filmovi[i];
    }
    
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, memorija, kojzanr;
    char ime[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata Film ======" << endl;
        cin >> ime;
        cin >> memorija;
        cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
        Film f(ime, memorija, (zanr) kojzanr);
        f.pecati();
    } else if (testCase == 2) {
        cout << "===== Testiranje na klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        for (int i = 0; i < n; i++)
            (omileno.getFilm(i)).pecati();
    } else if (testCase == 3) {
        cout << "===== Testiranje na metodot dodadiFilm() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        for (int i = 0; i < omileno.getBroj(); i++)
            (omileno.getFilm(i)).pecati();
    } else if (testCase == 4) {
        cout << "===== Testiranje na metodot pecatiFilmoviDrugZanr() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        omileno.pecatiFilmoviDrugZanr((zanr) kojzanr);

    } else if (testCase == 5) {
        cout << "===== Testiranje na metodot pecatiFilmoviDrugZanr() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        omileno.pecatiFilmoviDrugZanr((zanr) kojzanr);

    } else if (testCase == 6){
        cout<<"===== Testiranje na metodot procentNaMemorijaOdZanr() od klasata DVD =====" <<endl;
        DVD omileno(40);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        cout<<"Procent na filmovi od dadeniot zanr iznesuva: "<<omileno.procentNaMemorijaOdZanr((zanr) kojzanr)<<"%\n";
        
    }

    return 0;
}