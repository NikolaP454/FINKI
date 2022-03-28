#include<iostream>
#include<cstring>
using namespace std;

//vasiot kod ovde
class Masa
{
private:
    int dolzina, shirina;
public:
    Masa(): dolzina(0), shirina(0) {};
    Masa(int s, int d): dolzina(d), shirina(s) {};
    Masa(const Masa &m): dolzina(m.dolzina), shirina(m.shirina) {};
    ~Masa() {};
    
    void pecati(){
        cout << "Masa: " << shirina << " " << dolzina;
    }   
};

class Soba
{
private:
    int dolzina, shirina;
    Masa masa;

public:
    Soba(): dolzina(0), shirina(0), masa(Masa()) {};
    Soba(int s, int d, Masa m): dolzina(d), shirina(s), masa(m) {};
    Soba(const Soba &s): shirina(s.shirina), dolzina(s.dolzina), masa(s.masa) {};
    ~Soba() {};
    
    void pecati(){
        cout << "Soba: " << shirina << " " << dolzina << " ";
        masa.pecati();
    }
};

class Kukja
{
private:
    Soba soba;
    char adresa[50];
public:
    Kukja(): soba(Soba()), adresa("") {};
    Kukja(Soba s, char * adr): soba(s) { strcpy(adresa, adr); };
    ~Kukja() {};
    
    void pecati(){
        cout << "Adresa: " << adresa << " ";
        soba.pecati();
        cout << endl;
    }
};

//ne smee da se menuva main funkcijata!
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int masaSirina,masaDolzina;
        cin>>masaSirina;
        cin>>masaDolzina;
        Masa m(masaSirina,masaDolzina);
        int sobaSirina,sobaDolzina;
        cin>>sobaSirina;
        cin>>sobaDolzina;
        Soba s(sobaSirina,sobaDolzina,m);
        char adresa[30];
        cin>>adresa;
        Kukja k(s,adresa);
        k.pecati();
    }
    
    return 0;
}