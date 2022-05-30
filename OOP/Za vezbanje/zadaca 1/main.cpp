#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

class Book
{
protected:
    char isbn[25];
    char title[55];
    char avtor[35];
    double cena;

public:
    Book() = default;
    Book(const char * i,const char * t,const char * a,const double c): cena(c) { 
        strcpy(isbn, i);
        strcpy(title, t);
        strcpy(avtor, a);
    }
    ~Book() {}
    
    virtual double bookPrice() = 0;

    friend bool operator > (Book & x, Book & y){
        return x.bookPrice() > y.bookPrice();
    }

    friend ostream & operator << (ostream & os, Book & b){
        return os << b.isbn << ": " << b.title << ", " << b.avtor << " " << b.bookPrice() << '\n';
    }

    void update(const char * i,const char * t,const char * a,const double c) {
        strcpy(isbn, i);
        strcpy(title, t);
        strcpy(avtor, a);
        cena = c;
    }
};

class OnlineBook : public Book
{
    char * url;
    int size;

    void copy(const OnlineBook &b){
        Book::update(b.isbn, b.title, b.avtor, b.cena);

        size = b.size;
        url = new char[strlen(b.url) + 1];
        strcpy(url, b.url);
    }
public:
    OnlineBook(char * i, char * t, char * a, double c, char * u = nullptr, int s = 0): 
        Book(i,t,a,c), size(s) {
        url = new char[strlen(u) + 1];
        strcpy(url, u);
    }
    OnlineBook(const OnlineBook &b) {
        copy(b);
    }

    ~OnlineBook() { delete [] url; }
    
    void setISBN(char * x) { strcpy(isbn, x); }

    double bookPrice(){
        return ((size > 20)? 1.2 : 1) * cena;
    }

    void operator = (const OnlineBook &b){
        if(this == &b) return;

        delete [] url;
        copy(b);   
    }
};


class PrintBook : public Book
{
    double kg;
    bool have;

    void copy(const PrintBook &b){
        Book::update(b.isbn, b.title, b.avtor, b.cena);

        kg = b.kg;
        have = b.have;
    }

public:
    PrintBook(char * i, char * t, char * a, double c, double k, bool h):
        Book(i,t,a,c), kg(k), have(h) {}

    PrintBook(const PrintBook & b){
        copy(b);
    }

    ~PrintBook() {}
    
    double bookPrice() {
        return ((kg > 0.7)? 1.15 : 1) * cena;
    }

    void operator = (const PrintBook & b){
        copy(b);
    }
};

void mostExpensiveBook (Book** arr, int n) {
    int on = 0, pr = 0;
    for(int i = 0; i < n; i++){
        on += (bool)(dynamic_cast<OnlineBook*> (arr[i]));
        pr += (bool)(dynamic_cast<PrintBook*> (arr[i]));
    }

    cout << "FINKI-Education\n";
    cout << "Total number of online books: " << on << '\n';
    cout << "Total number of print books: " << pr << '\n';

    Book * exp = arr[0];
    for(int i = 1; i < n; i++){
        if(*arr[i] > *exp)
            exp = arr[i];
    }
    cout << "The most expensive book is:\n";
    cout << *exp << '\n';
}

int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3){
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4){
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i<n; i++) delete books[i];
        delete[] books;
    return 0;
}

