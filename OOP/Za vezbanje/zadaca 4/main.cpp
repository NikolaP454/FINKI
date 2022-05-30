#include <cstring>
#include <iostream>
using namespace std;

enum Size {mala, golema, familijarna};

class Pizza
{
protected:
    char ime[22];
    char sostojki[110];
    double cena;

public:
    Pizza(char * i, char * s, double c): cena(c) {
        strcpy(ime, i);
        strcpy(sostojki, s);
    }
    ~Pizza(){}
    
    virtual double price() const = 0;

    bool operator < (const Pizza &p){
        return price() < p.price();
    }
};

class FlatPizza : public Pizza
{
    Size golemina;

public:
    FlatPizza(char * i, char * s, double c, Size g = (Size)(0)): Pizza(i,s,c), golemina(g) {}
    ~FlatPizza() {}

    double price() const {
        switch(golemina) {
            case 0: return cena * 1.1;
            case 1: return cena * 1.3;
            case 2: return cena * 1.3;
            default: return 0;
        }
    }

    friend ostream & operator << (ostream &os, FlatPizza & p) {
        os << p.ime << ": ";
        for(int i = 0; i < min((int)strlen(p.sostojki), 49); i++)
            os << p.sostojki[i];

        os << ", ";
        switch(p.golemina) {
            case 0 : os << "small"; break;
            case 1 : os << "large"; break;
            case 2 : os << "family"; break;
        }

        return os << " - " << p.price() << '\n';
    }
};

class FoldedPizza : public Pizza
{
    bool wf;
public:
    FoldedPizza(char * i, char * s, double c, bool w = true): Pizza(i,s,c), wf(w) {}
    ~FoldedPizza() {}

    void setWhiteFlour(bool x) { wf = x; }

    double price() const {
        if(wf) return cena * 1.1;
        return cena * 1.3;
    }
    
    friend ostream & operator << (ostream &os, FoldedPizza & p) {
        os << p.ime << ": " << p.sostojki << ", ";
        if(p.wf) os << "wf";
        else os << "nwf";

        return os << " - " << p.price() << '\n';
    }
};

void expensivePizza(Pizza ** arr, int n) {
    Pizza * ans = arr[0];

    for(int i = 1; i < n; i++){
        if(ans->price() < arr[i]->price())
            ans = arr[i];
    }

    if(dynamic_cast<FlatPizza *> (ans)){
        cout << *(dynamic_cast<FlatPizza*> (ans));
    }
    else {
        cout << *(dynamic_cast<FoldedPizza*> (ans));
    }
}

// Testing

int main() {
  int test_case;
  char name[20];
  char ingredients[100];
  float inPrice;
  Size size;
  bool whiteFlour;

  cin >> test_case;
  if (test_case == 1) {
    // Test Case FlatPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FlatPizza fp(name, ingredients, inPrice);
    cout << fp;
  } else if (test_case == 2) {
    // Test Case FlatPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    int s;
    cin>>s;
    FlatPizza fp(name, ingredients, inPrice, (Size)s);
    cout << fp;
    
  } else if (test_case == 3) {
    // Test Case FoldedPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza fp(name, ingredients, inPrice);
    cout << fp;
  } else if (test_case == 4) {
    // Test Case FoldedPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza fp(name, ingredients, inPrice);
    fp.setWhiteFlour(false);
    cout << fp;

  } else if (test_case == 5) {
    // Test Cast - operator <, price
    int s;
    
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    cin>>s;
    FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
    cout << *fp1;
      
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    cin>>s;
    FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
    cout << *fp2;
      
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
    cout << *fp3;
      
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
    fp4->setWhiteFlour(false);
    cout << *fp4;
      
    cout<<"Lower price: "<<endl;
    if(*fp1<*fp2)
        cout<<fp1->price()<<endl;
    else cout<<fp2->price()<<endl;
        
    if(*fp1<*fp3)
        cout<<fp1->price()<<endl;
    else cout<<fp3->price()<<endl;    
        
    if(*fp4<*fp2)
        cout<<fp4->price()<<endl;
    else cout<<fp2->price()<<endl;
    
    if(*fp3<*fp4)
        cout<<fp3->price()<<endl;
    else cout<<fp4->price()<<endl;

  } else if (test_case == 6) {
    // Test Cast - expensivePizza
    int num_p;
    int pizza_type;

    cin >> num_p;
    Pizza **pi = new Pizza *[num_p];
    for (int j = 0; j < num_p; ++j) {

      cin >> pizza_type;
      if (pizza_type == 1) {
        cin.get();
        cin.getline(name,20);
          
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << (*fp);
        pi[j] = fp;
      }
      if (pizza_type == 2) {

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp =
            new FoldedPizza (name, ingredients, inPrice);
        if(j%2)
          (*fp).setWhiteFlour(false);
        cout << (*fp);
        pi[j] = fp;

      }
    }

    cout << endl;
    cout << "The most expensive pizza:\n";
    expensivePizza(pi,num_p);


  }
  return 0;
}
