#include<iostream>
#include<cstring>

using namespace std;
enum Extension {pdf, txt, exe};

class File
{
private:
    Extension ext;
    char * ime;
    char * gazda;
    int golemina;

public:
    File() {};
    File(char * name, char * owner, int size, Extension extension){
        int n = strlen(name) + 1;
        ime = new char[n];
        strcpy(ime, name);

        n = strlen(owner) + 1;
        gazda = new char[n];
        strcpy(gazda, owner);

        golemina = size;
        ext = extension;
    }

    File(const File &f){
        int n = strlen(f.ime) + 1;
        ime = new char[n];
        strcpy(ime, f.ime);

        n = strlen(f.gazda) + 1;
        gazda = new char[n];
        strcpy(gazda, f.gazda);

        golemina = f.golemina;
        ext = f.ext;
    }

    ~File() { 
        if(strlen(ime)) delete [] ime; 
        if(strlen(gazda)) delete [] gazda; 
    };
    
    bool equals(const File &f){
        if(strcmp(f.ime, ime)) return false;
        if(strcmp(f.gazda, gazda)) return false;
        if(ext != f.ext) return false;

        return true;
    }

    bool equalsType(const File &f){
        if(strcmp(f.ime, ime)) return false;
        if(ext != f.ext) return false;

        return true;
    }

    void print(){
        cout << "File name: " << ime << ".";
        if(ext == pdf) cout << "pdf" << endl;
        if(ext == txt) cout << "txt" << endl;
        if(ext == exe) cout << "exe" << endl;
        cout << "File owner: " << gazda << endl;
        cout << "File size: " << golemina << endl;
    }

    File * operator = (const File &f){
        int n = strlen(f.ime) + 1;
        ime = new char[n];
        strcpy(ime, f.ime);

        n = strlen(f.gazda) + 1;
        gazda = new char[n];
        strcpy(gazda, f.gazda);

        golemina = f.golemina;
        ext = f.ext;

        return this;
    }
};

class Folder
{
private:
    char * dir;
    int n = 0;
    File * files;

public:
    Folder() {};
    Folder(char * name){
        int strn = strlen(name) + 1;
        dir = new char[strn];
        strcpy(dir, name);
    }

    ~Folder(){
        if(strlen(dir)) delete [] dir;
        if(n) delete [] files;
    }

    void remove(const File &f){
        bool flag = true;
        int idx = 0;

        for(int i = 0; i < n; i++){
            if(files[i].equals(f)){
                flag = false;
                idx = i;
                break;
            }
        }

        if(flag) return;

        File * temp = new File[n + 1];
        for(int j = 0, i = 0; i < n; i++){
            if(i == idx) continue;
            temp[j++] = files[i];
        }

        if(n) delete [] files;
        n--;
        files = new File[n];
        
        for(int i = 0; i < n; i++)
            files[i] = temp[i];

        //if(n) delete [] temp;
    }
    
    void add(const File &f){
        File * temp = new File[n+1];
        for(int i = 0; i < n; i++)
            temp[i] = files[i];

        temp[n] = f;

        if(n) delete [] files;
        files = new File[++n];

        for(int i = 0; i < n; i++)
            files[i] = temp[i];

        delete [] temp;
    }

    void print(){
        cout << "Folder name: " << dir << endl;
        for(int i = 0; i < n; i++){
            files[i].print();
        }
    }
};

int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    }
    else if (testCase == 2) {
        cout << "======= FILE EQUALS AND EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext; 

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    }
    else if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    }
    else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    }
    else {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}