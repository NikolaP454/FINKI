#include <iostream>
#include <cstring>
using namespace std;

class Potpisuvac{
private:
    char ime[20];
    char prezime[20];
    char embg[14];

public:
    Potpisuvac(): ime(""), prezime(""), embg("") {};
    Potpisuvac(char *i, char *p, char *e){
        strcpy(ime, i);
        strcpy(prezime, p);
        strcpy(embg, e);
    }
    Potpisuvac(const Potpisuvac &p){
        strcpy(ime, p.ime);
        strcpy(prezime, p.prezime);
        strcpy(embg, p.embg);
    }
    ~Potpisuvac() {};

    const bool operator == (const Potpisuvac &p) const{
        return (strcmp(embg, p.embg) == 0);
    }

    void print(){ cout << ime << " " << prezime << " " << embg << endl; }
};

class Dogovor{
private:
    int broj;
    char kategorija[50];
    Potpisuvac potpisuvaci[3];

public:
    Dogovor() {};
    Dogovor(int br, char *kat, Potpisuvac *p){
        broj = br;
        strcpy(kategorija, kat);

        for(int i = 0; i < 3; i++){
            potpisuvaci[i] = p[i];
        }
    };

    ~Dogovor() {};

    bool proverka(){
        for(int i = 0; i < 3; i++){
            //potpisuvaci[i].print();
            for(int j = i+1; j < 3; j++){
                if(potpisuvaci[i] == potpisuvaci[j])
                    return true;
            }
        }

        return false;
    }

    void print(){
        cout << "Br: " << broj << endl;
        cout << "Kategorija: " << kategorija << endl;

        for(int i = 0; i < 3; i++)
            potpisuvaci[i].print();
    }
};


//ne smee da se menuva main funkcijata
int main()
{
    char embg[14], ime[20], prezime[20], kategorija[20];
    int broj, n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> embg >> ime >> prezime;
        Potpisuvac p1(ime, prezime, embg);
        cin >> embg >> ime >> prezime;
        Potpisuvac p2(ime, prezime, embg);
        cin >> embg >> ime >> prezime;
        Potpisuvac p3(ime, prezime, embg);
        cin >> broj >> kategorija;
        Potpisuvac p[3];
        p[0] = p1; p[1] = p2; p[2] = p3;
        Dogovor d(broj, kategorija, p);
        cout << "Dogovor " << broj << ":" << endl; 
        if(d.proverka() == true)
            cout << "Postojat potpishuvaci so ist EMBG" << endl;
        else
            cout << "Ne postojat potpishuvaci so ist EMBG" << endl;
    }
    return 0;
}