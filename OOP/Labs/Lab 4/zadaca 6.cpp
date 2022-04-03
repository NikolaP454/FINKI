#include <iostream>
#include <cstring>

using namespace std;

enum Tip{ LINUX, UNIX, WINDOWS };

class OperativenSistem
{
private:
    char * ime;
    float verzija;
    Tip tip;
    float size;

public:
    OperativenSistem() {
        ime = nullptr;
        size = 0;
        verzija = 0.0;
        tip = LINUX;
    }

    OperativenSistem(char * i, float v, Tip t, float s){
        verzija = v;
        size = s;
        tip = t;

        ime = new char[strlen(i) + 1];
        strcpy(ime, i);
    }

    OperativenSistem(const OperativenSistem &os) {
        verzija = os.verzija;
        size = os.size;
        tip = os.tip;

        ime = new char[strlen(os.ime) + 1];
        strcpy(ime, os.ime);
    }

    ~OperativenSistem() {
        delete [] ime;
    }

    void pecati(){
        //cout.precision(3);
        cout << "Ime: " << ime << " ";
        cout << "Verzija: ";
        cout << verzija << " ";
        cout << "Tip: " << tip << " ";
        cout << "Golemina:"  << size << "GB\n";
    }

    bool istaFamilija(const OperativenSistem &os) {
        if(tip != os.tip) return false;
        if(strcmp(ime, os.ime)) return false;

        return true;
    }
    int sporediVerzija(const OperativenSistem &os) {
        if(verzija == os.verzija) return 0;
        if(verzija < os.verzija) return -1;

        return 1;
    } 

    bool ednakviSe(const OperativenSistem &os) {
        if(size != os.size)
            return false;

        return istaFamilija(os) && !sporediVerzija(os);
    }
   
    void operator = (const OperativenSistem &os) {
        verzija = os.verzija;
        size = os.size;
        tip = os.tip;

        if(ime != nullptr) delete [] ime;
        ime = new char[strlen(os.ime) + 1];
        strcpy(ime, os.ime);
    }
};

class Repozitorium
{
private:
    char ime[20];
    OperativenSistem * OSs;
    int n;

public:
    Repozitorium(): n(0) { OSs = nullptr; }

    Repozitorium(char * i, OperativenSistem * os = nullptr, int br = 0){
        n = br;

        if(n) OSs = new OperativenSistem[n];
        for(int i = 0; i < n; i++)
            OSs[i] = os[i];

        strcpy(ime, i);
    }

    Repozitorium(const Repozitorium &repo) {
        n = repo.n;

        if(n) OSs = new OperativenSistem[n];
        for(int i = 0; i < n; i++)
            OSs[i] = repo.OSs[i];

        strcpy(ime, repo.ime);
    }


    ~Repozitorium() { if(n) delete [] OSs; }

    void pecatiOperativniSistemi() {
        cout << "Repozitorium: " << ime << '\n';
        for(int i = 0; i < n; i++)
            OSs[i].pecati();
    }    

    void izbrishi(const OperativenSistem &os) {
        int idx = -1;

        for(int i = 0; i < n; i++){
            if(OSs[i].ednakviSe(os))
                idx = i;
        }

        if(idx == -1) return;

        OperativenSistem * temp = new OperativenSistem[n-1];

        for(int j = 0, i = 0; i < n; i++){
            if(idx == i) continue;

            temp[j++] = OSs[i];
        }

        delete [] OSs;
        if(n > 1) OSs = new OperativenSistem[--n];
        for(int i = 0; i < n; i++)
            OSs[i] = temp[i];

        delete [] temp;
    }

    void dodadi(const OperativenSistem &os){
        for(int i = 0; i < n; i++){
            if(OSs[i].istaFamilija(os) and OSs[i].sporediVerzija(os) == -1){
                OSs[i] = os;
                return;
            }
        }

        OperativenSistem * temp = new OperativenSistem[n+1];
        temp[n] = os;

        for(int i = 0; i < n; i++)
            temp[i] = OSs[i];

        if(n) delete [] OSs;
        OSs = new OperativenSistem[++n];

        for(int i = 0; i < n; i++)
            OSs[i] = temp[i];

        delete [] temp;
    }

    void operator = (const Repozitorium &repo) {
        if(n) delete [] OSs;

        n = repo.n;
        if(n) OSs = new OperativenSistem[n];

        for(int i = 0; i < n; i++)
            OSs[i] = repo.OSs[i];

        strcpy(ime, repo.ime);
    }
};

int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
     cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}