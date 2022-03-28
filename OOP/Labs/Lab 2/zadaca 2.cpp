#include <iostream>
using namespace std;

class Krug {
private:
    float r;
    const float pi = 3.14;

public:
    Krug(): r(0) {};
    Krug(int _r): r(_r) {};

    float perimetar() {return pi*2*r;}
    float plostina() {return pi*r*r;}
    bool ednakvi() {return perimetar() == plostina();}
};

int main() {
    float r;
    cin >> r;
    Krug k(r);
    cout << k.perimetar() << endl;
    cout << k.plostina() << endl;
    cout << k.ednakvi() <<endl;
    Krug k2;
    return 0;
}