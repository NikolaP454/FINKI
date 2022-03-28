#include <iostream>
#include <cstring>
using namespace std;

class Film
{
private:
    char ime[100];
    char reziser[50];
    char zanr[50];
    int godina;

public:
    Film(): ime(""), reziser(""), zanr(""), godina(0) {};
    Film(char i[100], char r[100], char z[100], int g){
        strcpy(ime, i);
        strcpy(reziser,r);
        strcpy(zanr,z);
        godina = g;
    }

    void pecati(){
        cout << "Ime: ";
        for(int i = 0; i < strlen(ime); i++)
            cout << ime[i]; 
        cout << '\n';

        cout << "Reziser: ";
        for(int i = 0; i < strlen(reziser); i++)
            cout << reziser[i]; 
        cout << '\n';

        cout << "Zanr: ";
        for(int i = 0; i < strlen(zanr); i++)
            cout << zanr[i]; 
        cout << '\n';

        cout << "Godina: " << godina << '\n';
    }
    
    int getGodina() { return godina; }
};

void pecati_po_godina(Film *f, int n, int godina){
    for(int i = 0; i < n; i++){
        if(f[i].getGodina() == godina)
            f[i].pecati();
    }
}

int main() {
    int n;
    cin >> n;
    Film f[n];
    for(int i = 0; i < n; ++i) {
        char ime[100];
        char reziser[50];
        char zanr[50];
        int godina;
        cin >> ime;
        cin >> reziser;
        cin >> zanr;
        cin >> godina;
        f[i] = Film(ime,reziser,zanr,godina);
    }
    int godina;
    cin >> godina;
    pecati_po_godina(f,n,godina);
    return 0;
 }