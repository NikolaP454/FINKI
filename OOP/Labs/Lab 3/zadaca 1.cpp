#include<iostream>
#include<cstring>
using namespace std;

class Person
{
    char ime[20];
    char prezime[20];

public:
    Person(){
        strcpy(ime, "not specified");
        strcpy(prezime, "not specified");
    };
    Person(char *_ime, char *_prezime){
        strcpy(ime, _ime);
        strcpy(prezime, _prezime);
    }
    ~Person() {};

    void print(){
        cout << ime << " " << prezime << endl;
    }
    
};

class Date
{
private:
    int year, month, day;

public:
    Date(): year(0), month(0), day(0) {};
    Date(int y, int m, int d): year(y), month(m), day(d) {};
    Date(const Date &date){
        year = date.gety();
        month = date.getm();
        day = date.getd();
    }

    ~Date() {};
    
    int gety() const { return year; }
    int getm() const { return month; }
    int getd() const { return day; }

    void print(){
        cout << year << '.' << month << '.' << day << endl;
    }
};

class Car
{
private:
    Person owner;
    Date date;
    float price;

public:
    Car() {};
    Car(Person p, Date d, float pr): owner(p), date(d), price(pr) {};
    ~Car() {};

    int getPrice() const { return price; }
    
    void print(){
        owner.print();
        date.print();

        cout << "Price: " << price << endl;
    }
};

void cheaperThan(Car* cars, int numCars, float price){
    for(int i = 0; i < numCars; i++, cars++){
        if(cars->getPrice() < price){
            cars->print();
        }
    }
}

int main() {
    char name[20];
    char lastName[20];
    int year;
    int month;
    int day;
    float price;

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cin >> name;
        cin >> lastName;
        Person lik(name, lastName);

        cin >> year;
        cin >> month;
        cin >> day;
        Date date(year, month, day);

        cin >> price;
        Car car(lik, date,  price);

        car.print();
    }
    else if (testCase == 2) {
        cin >> name;
        cin >> lastName;
        Person lik(name, lastName);

        cin >> year;
        cin >> month;
        cin >> day;
        Date date(Date(year, month, day));

        cin >> price;
        Car car(lik, date,  price);
        car.print();
    }
    else {
        int numCars;
        cin >> numCars;

        Car cars[10];
        for (int i = 0; i < numCars; i++) {
            cin >> name;
            cin >> lastName;
            Person lik(name, lastName);

            cin >> year;
            cin >> month;
            cin >> day;
            Date date(year, month, day);

            cin >> price;
            cars[i] = Car(lik, date,  price);
        }
        float priceLimit;
        cin >> priceLimit;
        cheaperThan(cars, numCars, priceLimit);
    }


    return 0;
}