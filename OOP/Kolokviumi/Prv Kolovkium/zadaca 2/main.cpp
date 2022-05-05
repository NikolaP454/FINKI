#include<iostream>
#include<cstring>
using namespace std;

class Flight{
private:
    char from[50];
    char to[50];

    double time;
    double price;

public:
    /// Constructors & Destructor //////////////////////////////////////////////////////////////

    /// Default & Parametric Constructor
    Flight(char * f = "", char * t = "", double ti = 0.0, double p = 0.0): time(ti), price(p) {
        strcpy(from, f);
        strcpy(to, t);
    }

    /// Copy constructor
    Flight(const Flight &f){
        strcpy(from, f.from);
        strcpy(to, f.to);

        time = f.time;
        price = f.price;
    }

    /// Destructor
    ~Flight() {}

    /// Get functions //////////////////////////////////////////////////////////////////////////

    char * getDepartureCity() { return from; }
    char * getArrivalCity() { return to; }

    /// Functions //////////////////////////////////////////////////////////////////////////////

    void printDuration(){
        cout << (int)(time) << "h:" << (time - (int)(time)) * 60 << "min";
    }

    void printFlight(){
        cout << from << " -> ";
        printDuration();
        cout << " -> ";
        cout << to << ": " << price << "EUR";
    }

    bool sameFrom(char * f){
        return !strcmp(from, f);
    }

    bool sameTo(char * t){
        return !strcmp(to, t);
    }

    bool same(char * f, char * t){
        return sameFrom(f) && sameTo(t);
    }

    /// Operators //////////////////////////////////////////////////////////////////////////////

    bool operator == (const Flight &f){
        if(strcmp(from, f.from)) return false;
        if(strcmp(to, f.to)) return false;

        return true;
    }

    Flight &operator = (const Flight &f) {
        if(this != &f){
            strcpy(from, f.from);
            strcpy(to, f.to);

            time = f.time;
            price = f.price;
        }

        return *this;
    }
};


class Airline {
private:
   char ime[50];
   Flight * fl;
   int n;

public:
    /// Constructors & Destructor //////////////////////////////////////////////////////////////

    /// Default & Parametric Constructor
    Airline(char * i = "", int br = 0, Flight * f = nullptr) {
        strcpy(ime, i);
        n = br;
        if(n){
            fl = new Flight[n];
            for(int i = 0; i < n; i++)
                fl[i] = f[i];
        }
    }

    /// Copy constructor
    Airline(const Airline &a){
        strcpy(ime, a.ime);
        n = a.n;
        if(n){
            fl = new Flight[n];
            for(int i = 0; i < n; i++)
                fl[i] = a.fl[i];
        }
    }

    /// Destructor
    ~Airline() {
        if(n) delete [] fl;
    }

    /// Get functions //////////////////////////////////////////////////////////////////////////

    int getN(){ return n; }
    Flight * getFlights() { return fl; }

    /// Functions //////////////////////////////////////////////////////////////////////////////

    bool check(int i, int j){
        return(!strcmp(fl[i].getArrivalCity(), fl[j].getDepartureCity()));
    }

    void addFlight(const Flight &f){
        bool flag = false;
        for(int i = 0; i < n; i++){
            if(fl[i] == f)
                flag = true;
        }

        if(flag) return;

        Flight * temp = new Flight[n+1];
        temp[n] = f;

        for(int i = 0; i < n; i++)
            temp[i] = fl[i];


        if(n) delete [] fl;
        fl = new Flight[++n];

        for(int i = 0; i < n; i++)
            fl[i] = temp[i];

        delete [] temp;
    }

    bool direct(int i, char * f, char * t){
        return fl[i].same(f,t);
    }

    bool indirect(int i, char * f, char * t, int type){
        if(type == 0) return fl[i].sameFrom(f);
        if(type == 1) return fl[i].sameTo(t);

        return false;
    }

    void printFlight(int i){
        fl[i].printFlight();
    }

    /// Operators //////////////////////////////////////////////////////////////////////////////

    Airline &operator = (const Airline &a) {
        if(this != &a){
            strcpy(ime, a.ime);
            if(n) delete [] fl;
            n = a.n;
            if(n){
                fl = new Flight[n];
                for(int i = 0; i < n; i++)
                    fl[i] = a.fl[i];
            }
        }

        return *this;
    }
};

/// Regular Functions //////////////////////////////////////////////////////////////////////////

void searchFlights(Airline &a, char * dep, char * arr){

    /// Check for direct flight

    bool flag = false;
    for(int i = 0; i < a.getN(); i++){
        if(a.direct(i,dep, arr)){
            flag = true;
            a.printFlight(i);
        }
    }

    if(flag) return;

    /// Check for indirect flight

    for(int i = 0; i < a.getN(); i++){
        for(int j = 0; j < a.getN(); j++){
            if(a.indirect(i,dep, arr, 0) && a.indirect(j,dep,arr,1) && a.check(i, j)){
                a.printFlight(i);
                cout << " 1 stop " ;
                a.printFlight(j);
                cout << endl;
                flag = true;
            }
        }
    }

    if(flag) return;

    /// No flight found case

    cout << "Nema konekcija pomegju baranite gradovi" << endl;
}

/// Main //////////////////////////////////////////////////////////////////////////////////////

//NE MENUVAJ VO MAIN FUNKCIJATA
int main(){

    int testCase;
    cin >> testCase;

    if(testCase == 1){
        cout << "====Testing class Flight constructors and additional methods====" << endl;
        Flight f1;
        char dep[50], arr[50];
        double dur, pr;
        cin >> dep >> arr >> dur >> pr;
        Flight f2(dep, arr, dur, pr);
        cout << f2.getDepartureCity() << " " << f2.getArrivalCity() << endl;
        cout << "Testing OK" << endl;
    }
    else if(testCase == 2){
        cout << "====Testing class Flight methods printDuration() and printFlight()====" << endl;
        char dep[50], arr[50];
        double dur, pr;
        cin >> dep >> arr >> dur >> pr;
        Flight f2(dep, arr, dur, pr);
        f2.printFlight();
        cout << endl;
    }
    else if(testCase == 3){
        cout << "====Testing class Airplane constructors and methods====" << endl;
        Airline a("Wizzair");
        char dep[50], arr[50];
        double dur, pr;
        cin >> dep >> arr >> dur >> pr;
        Flight f1(dep, arr, dur, pr);
        a.addFlight(f1);
        Flight f3 = f1;
        a.addFlight(f3);
        a.getFlights()[0].printFlight();
        cout << endl;
        cout << a.getN() << endl;
        Airline b = a;
        b.getFlights()[0].printFlight();
        cout << endl;
        cin >> dep >> arr >> dur >> pr;
        Flight f2(dep, arr, dur, pr);
        b.addFlight(f2);
        b.getFlights()[1].printFlight();
        cout << endl;
        cout << "Testing OK" << endl;
    }
    else if(testCase == 4){
        cout << "====Testing global function====" << endl;
        Airline a("Wizzair");
        char dep[50], arr[50];
        double dur, pr;
        int n;
        cin >> n;
        for(int i = 0; i < n; i++){
            cin >> dep >> arr >> dur >> pr;
            Flight f(dep, arr, dur, pr);
            a.addFlight(f);
        }
        cin >> dep >> arr;
        searchFlights(a, dep, arr);
        cout << endl << "Testing OK" << endl;
    }

    return 0;
}
