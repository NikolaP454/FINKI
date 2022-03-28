#include<iostream>
#include<cstring>
using namespace std;

class Category
{
private:
    char name[20] = "unnamed";
public:
    Category() { strcpy(name, "unnamed"); }
    Category(char * n) { strcpy(name, n); }
    Category(const Category &c) { strcpy(name, c.name); }
    ~Category() {};

    void print() const{
        cout << "Category: " << name << endl;
    }    
};

class NewsArticle
{
private:
    Category category;
    char title[30] = "untitled";
public:
    NewsArticle(): category(Category()){ strcpy(title, "untitled"); };
    NewsArticle(Category c, char *t = (char *)"untitled"): category(c) { strcpy(title, t); };
    NewsArticle(const NewsArticle &na){
        category = na.category;
        strcpy(title, na.title);
    }
    ~NewsArticle() {};
    
    void print() const {
        cout << "Article title: " << title << endl;
        category.print();
    }
};

class FrontPage
{
private:
    NewsArticle news;
    float price;
    int editionNumber;

public:
    FrontPage(): news(NewsArticle()), price(0), editionNumber(0) {};
    FrontPage(NewsArticle n, float p = 0, int ed = 0): news(n), price(p), editionNumber(ed) {};
    ~FrontPage() {};
    
    void print() {
        cout << "Price: " << price << ", ";
        cout << "Edition number: " << editionNumber << endl;
        news.print(); 
    }
};


int main() {
    char categoryName[20];
    char articleTitle[30];
    float price;
    int editionNumber;

    int testCase;
    cin >> testCase;


    if (testCase == 1) {
        int iter;
        cin >> iter;
        while (iter > 0) {
            cin >> categoryName;
            cin >> articleTitle;
            cin >> price;
            cin >> editionNumber;
            Category category(categoryName);
            NewsArticle article(category, articleTitle);
            FrontPage frontPage(article, price, editionNumber);
            frontPage.print();
            iter--;
        }
    }
    else if (testCase == 2) {
        cin >> categoryName;
        cin >> price;
        cin >> editionNumber;
        Category category(categoryName);
        NewsArticle article(category);
        FrontPage frontPage(article, price, editionNumber);
        frontPage.print();
    }// test case 3
    else if (testCase == 3) {
        cin >> categoryName;
        cin >> articleTitle;
        cin >> price;
        Category category(categoryName);
        NewsArticle article(category, articleTitle);
        FrontPage frontPage(article, price);
        frontPage.print();
    }
    else {
        FrontPage frontPage = FrontPage();
        frontPage.print();
    }
    return 0;
}