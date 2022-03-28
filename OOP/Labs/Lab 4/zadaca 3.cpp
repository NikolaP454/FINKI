#include <iostream>
#include <cstring>
using namespace std;

class Avtomobil
{
private:
    char color[20];
    char brand[20];
    char model[20];

public:
    Avtomobil() {};
    Avtomobil(char *c, char *b, char *m){
        strcpy(color, c);
        strcpy(brand, b);
        strcpy(model, m);
    }

    ~Avtomobil() {};
    
    void operator = (const Avtomobil &a){
        strcpy(color, a.color);
        strcpy(brand, a.brand);
        strcpy(model, a.model);
    }

    void pecati(){
        cout << color << " " << brand << " " << model << endl;
    }
};


class ParkingPlac
{
private:
    char adresa[20];
    char * id;
    int cena = 0; 
    int profit = 0;

    Avtomobil * cars;
    int n = 0;

public:
    ParkingPlac(){
        id = nullptr;
        cars = nullptr;
        cena = 0;
        profit = 0;
        n = 0;
    };

    ParkingPlac(char * _ad, char * _id, int _cena){
        strcpy(adresa, _ad);

        id = new char[strlen(_id) + 1];
        strcpy(id, _id);

        cena = _cena;
        cars = nullptr;
        profit = n = 0;

    }
        
    ParkingPlac(const ParkingPlac &pp){
        strcpy(adresa, pp.adresa);

        id = new char[strlen(pp.id) + 1];
        strcpy(id, pp.id);

        cena = pp.cena;
        profit = pp.profit;

        n = pp.n;
        cars = new Avtomobil[n];

        for(int i = 0; i < n; i++)
            cars[i] = pp.cars[i];
    }

    ~ParkingPlac(){
        delete [] id;
        delete [] cars;
    };
    
    char * getId() { return id; }

    void platiCasovi(int h) { profit += h * cena; }
    bool daliIstaAdresa(ParkingPlac &p) { return !strcmp(p.adresa, adresa); }

    void parkirajVozilo(Avtomobil &a){
        Avtomobil * temp = new Avtomobil[n+1];

        for(int i = 0; i < n; i++)
            temp[i] = cars[i];

        temp[n++] = a;

        if(n - 1) delete [] cars;
        cars = new Avtomobil[n];

        for(int i = 0; i < n; i++)
            cars[i] = temp[i];

        delete [] temp;
    }

    void pecatiParkiraniVozila(){
        cout << "Vo parkingot se parkirani slednite vozila:\n";
        for(int i = 0; i < n; i++){
            cout << i+1 << ".";
            cars[i].pecati();
        }

    }
    void pecati(){
        cout << id << " " << adresa;
        if(profit) cout << " - " << profit << " denari";
        cout << endl;
    }

    void operator = (const ParkingPlac &pp){
        strcpy(adresa, pp.adresa);

        delete [] id;
        id = new char[strlen(pp.id) + 1];
        strcpy(id, pp.id);

        cena = pp.cena;
        profit = pp.profit;

        n = pp.n;
        delete [] cars;
        cars = new Avtomobil[n];

        for(int i = 0; i < n; i++)
            cars[i] = pp.cars[i];
    }
};

int main(){

    ParkingPlac p[100];
    int n,m;
    char adresa[50],id[50];
    int brojcasovi,cenacas;
    cin>>n;
    if(n > 0){


        for (int i=0;i<n;i++){
            cin.get();
            cin.getline(adresa,50);
            cin>>id>>cenacas;
            
            ParkingPlac edna(adresa,id,cenacas);
            
            p[i]=edna;
        }
        
        //plakjanje
        cin>>m;
        for (int i=0;i<m;i++){

            cin>>id>>brojcasovi;
            int findId=false;
            for (int j=0;j<n;j++){
                if (strcmp(p[j].getId(), id)==0){
                    p[j].platiCasovi(brojcasovi);
                    findId=true;
                }
            }
            if (!findId)
            cout<<"Ne e platen parking. Greshen ID."<<endl;
        }

        cout<<"========="<<endl;
        ParkingPlac pCentar("Cvetan Dimov","C10",80);
        for (int i=0;i<n;i++)
            if (p[i].daliIstaAdresa(pCentar))
                p[i].pecati();
    } else {

        ParkingPlac najdobarPlac("Mars", "1337", 1);
        int brVozila;
        cin >> brVozila;
        for(int i = 0; i < brVozila; ++i){

            char boja[20];
            char brend[20];
            char model[20];

            cin >> boja >> brend >> model;
            Avtomobil novAvtomobil(boja, brend, model);
            najdobarPlac.parkirajVozilo(novAvtomobil);
        }
        if(brVozila != 0)
        najdobarPlac.pecatiParkiraniVozila();

    }
}