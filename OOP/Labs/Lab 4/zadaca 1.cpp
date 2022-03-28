#include <iostream>
using namespace std;

class List
{
private:
    int * niza;
    int n;

public:
    List() { n = 0; };
    List(int * arr, int _n): n(_n) {
        niza = new int[n];

        for(int i = 0; i < n; i++)
            niza[i] = arr[i];
    }

    List(const List &l) {
        n = l.n;
        niza = new int[n];

        for(int i = 0; i < n; i++)
            niza[i] = l.niza[i];
    }

    ~List() { if(n) delete [] niza; };

    int sum(){
        int ans = 0;
        for(int i = 0; i < n; i++)
            ans += niza[i];

        return ans;
    }

    double average(){
        return (double) sum() / n;
    }

    void pecati(){

        cout << n << ": ";
        for(int i = 0; i < n; i++){
            cout << niza[i] << " ";
        }

        cout << "sum: " << sum() << " ";
        cout.precision(5);
        cout << "average: " << (float)average() << endl;
    }

    int getsize() const { return n; }

    void operator = (const List &l) {
        if(n) delete [] niza;
        n = l.getsize();
        niza = new int[n];

        for(int i = 0; i < n; i++)
            niza[i] = l.niza[i];
    }
};

class ListContainer
{
private:
    List * lista;
    int n = 0, t = 0;

public:
    ListContainer() { n = 0; t = 0; };
    ListContainer(List * l, int _n, int _t): n(_n), t(_t){
        lista = new List[n];

        for(int i = 0; i < n; i++){
            lista[i] = l[i];
        }
    }

    ListContainer(const ListContainer &lc): n(lc.n), t(lc.t) {
        lista = new List[n];

        for(int i = 0; i < n; i++)
            this->lista[i] = lc.lista[i];
    }

    ~ListContainer() { if(n) delete [] lista; };

    int getsize() const { return n; }

    void addNewList(List l){
        bool flag = false;

        for(int i = 0; i < n; i++){
            if(l.sum() == lista[i].sum())
                flag = true;
        }

        if(flag){
            t++;
            return;
        }

        List * temp = new List[n+1];
        for(int i = 0; i < n; i++)
            temp[i] = lista[i];

        temp[n] = l;

        n++;
        if(n > 1) delete [] lista;
        lista = new List[n+2];

        for(int i = 0; i < n; i++)
            lista[i] = temp[i];

        delete [] temp;
    }

    int sum(){
        int ans = 0;
        for(int i = 0; i < n; i++)
            ans += lista[i].sum();

        return ans;
    } 

    double average(){
        int sum_n = 0;
        for(int i = 0; i < n; i++)
            sum_n += lista[i].getsize();


        return (double) sum() / sum_n;
    }

    void print(){
        if(!n){
            cout << "The list is empty\n";
            return;
        }
        for(int i = 0; i < n; i++){
            cout << "List number: " << i+1 << " ";
            cout << "List info: ";

            if(!lista[i].getsize()){
                cout << "The list is empty\n";
            }
            else lista[i].pecati();
        }

        cout << "Sum: " << sum() << " ";
        cout.precision(6);
        cout << "Average: " << average() << endl;
        cout << "Successful attempts: " << n << " Failed attempts: " << t << endl;
    }

    ListContainer * operator = (const ListContainer &lc) {
        if(n) delete [] lista;
        n = lc.getsize();
        t = lc.t;
        lista = new List[n];

        for(int i = 0; i < n; i++)
            lista[i] = lc.lista[i];

        return this;
    }
};

int main() {
    
    ListContainer lc;
    int N;  
    cin>>N; 
    
    for (int i=0;i<N;i++) {
        int n;
        int niza[100];
        
        cin>>n;
       
        for (int j=0;j<n;j++){
            cin>>niza[j];
            
        }
       
        List l=List(niza,n);
        
        lc.addNewList(l);
    }   
    
    
    int testCase;
    cin>>testCase;
    
    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();
        
    }
    else {
        lc.print();
    }
}