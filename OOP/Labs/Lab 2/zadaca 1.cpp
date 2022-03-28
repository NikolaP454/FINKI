#include <iostream>
using namespace std;

class Agol {
private:
    int stepeni, minuti, sekundi;

public:
    Agol(int st, int mi, int se): stepeni(st), minuti(mi), sekundi(se) {};

    void set_stepeni(int deg) {stepeni = deg;}
    void set_minuti(int mi) {minuti = mi;}
    void set_sekundi(int sec) {sekundi = sec;}

    int getSekundi(){return sekundi;}

    int to_sekundi(){return stepeni * 3600 + minuti * 60 + sekundi;}
};

bool pecati(){
    cout << "Nevalidni vrednosti za agol";
    return 0;
}

bool proveri(int deg, int min, int sec){
    if(deg < 0 or deg > 360) return pecati();
    if(min < 0 or min >= 60) return pecati();
    if(sec < 0 or sec >= 60) return pecati();

    return true;
}


bool changeOfSeconds(Agol a, int sec){
    return a.getSekundi()!=sec;
}

int main() {
    
    Agol a1 = Agol(0,0,0);
    int deg, min, sec;
    cin >> deg >> min >> sec;
    
    if (proveri(deg, min, sec)) {
    
        a1.set_stepeni(deg);
        a1.set_minuti(min);
        a1.set_sekundi(sec);
        cout << a1.to_sekundi();
        if (changeOfSeconds(a1,sec))
            cout << "Ne smeete da gi menuvate sekundite vo ramkite na klasata!" << endl;
        
    }
    
    return 0;
}
