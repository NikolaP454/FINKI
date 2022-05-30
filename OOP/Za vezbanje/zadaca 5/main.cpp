#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

const int MAX = 50;
enum typeC {standard, loyal, vip};

/// Functions * ////////////////////////////////////////////


/// Exception classes //////////////////////////////////////

class UserExistsException
{
public:
    UserExistsException() {}
    ~UserExistsException() {}

    void print() {
        cout << "The user already exists in the list!\n";
    }
    
};

/// Classes ////////////////////////////////////////////////

class Customer
{
protected:
    char ime[55];
    char adresa[55];
    static int popust;
    static int popustPlus;
    int type;
    int br;

private:
    void copy(const Customer &c){
        strcpy(ime, c.ime);
        strcpy(adresa, c.adresa);
        type = c.type;
        br = c.br;
    }
public:
    Customer() = default;
    Customer(char * i, char * a, int t, int b): type(t), br(b) {
        strcpy(ime, i);
        strcpy(adresa, a);
    }
    
    Customer(const Customer &c) { copy(c); }

    ~Customer() {}

    static void setDiscount1(int x) { popust = x; }
    
    void BumpStatus() {
        switch(type) {
            case 0: type = (br > 5)? 1 : type; break;
            case 1: type = (br > 10)? 2 : type; break;
            default: return;
        }

        return;
    }

    Customer & operator = (const Customer &c) {
        copy(c);
        return *this;
    }

    friend ostream & operator << (ostream &os, Customer & c){
        os << c.ime << '\n';
        os << c.adresa << '\n';
        os << c.br << '\n';

        switch(c.type) {
            case 0: return os << "standard 0\n";
            case 1: return os << "loyal " << c.popust << '\n';
            case 2: return os << "vip " << c.popust + c.popustPlus << '\n';
            default: return os << "ERROR\n"; break;
        }

        return os; /// JUST IN CASE (NOT NEEDED)
    } 

    bool operator == (const Customer & c){
        return !strcmp(adresa, c.adresa);
    }
};

class FINKI_bookstore
{
    Customer * arr;
    int n;

public:
    FINKI_bookstore(): arr(nullptr), n(0) {}
    ~FINKI_bookstore() { delete [] arr; }
    

    void update() {
        for(int i = 0; i < n; i++)
            arr[i].BumpStatus();
    }

    void setCustomers(Customer * c, int x){
        n = x;

        delete [] arr;
        arr = new Customer[n];

        for(int i = 0; i < n; i++)
            arr[i] = c[i];
    }

    friend ostream & operator << (ostream &os, FINKI_bookstore & fb) {
        for(int i = 0; i < fb.n; i++)
            os << fb.arr[i];

        return os;
    }

    Customer & operator [] (int i) {
        return arr[i];
    }

    FINKI_bookstore & operator += (const Customer & c){
        for(int i = 0; i < n; i++){
            if(arr[i] == c) throw UserExistsException();
        }

        Customer * temp = new Customer[n+1];
        temp[n++] = c;

        for(int i = 0; i < n-1; i++)
            temp[i] = arr[i];

        delete [] arr;
        arr = temp;

        return *this;
    }
};

int Customer::popust = 10;
int Customer::popustPlus = 20;

/// Functions //////////////////////////////////////////////


/// Main ///////////////////////////////////////////////////

int main(){
  int testCase;
  cin >> testCase;

  char name[MAX];
  char email[MAX];
  int tC;
  int discount;
  int numProducts;


  if (testCase == 1){
    cout << "===== Test Case - Customer Class ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

  }

  if (testCase == 2){
    cout << "===== Test Case - Static Members ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

    c.setDiscount1(5);

    cout << c;
  }

  if (testCase == 3){
    cout << "===== Test Case - FINKI-bookstore ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << fc <<endl;
  }

  if (testCase == 4){
    cout << "===== Test Case - operator+= ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;

    Customer c(name, email, (typeC) tC, numProducts);

    try { fc+=c; }
    catch(UserExistsException & e) { e.print(); }

    cout << fc;
  }

  if (testCase == 5){
    cout << "===== Test Case - operator+= (exception) ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    Customer c(name, email, (typeC) tC, numProducts);

    try { fc+=c; }
    catch(UserExistsException & e) { e.print(); }
    
    cout << fc;
  }

  if (testCase == 6){
    cout << "===== Test Case - update method  ======" << endl << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << "Update:" << endl;
    fc.update();
    cout << fc;
  }
  return 0;
   
}
