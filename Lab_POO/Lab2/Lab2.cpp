// Online C++ compiler to run C++ program online
#include <iostream>
#include <array>
using namespace std;
/*

class Persoana {
    string nume;
    int id;
    static int contor;
    public:
    Persoana(string nume = "Martipan") {
        this->nume = nume;
        id = contor++;
    }
    //~Persoana(){cout<<"~()"<<endl;}
    void afisare() {cout<<"Nume: "<<nume<<" ID: "<<id<<endl;}
    static int getContor() {return contor;}
};

int Persoana::contor = 0;


int main() {
    array<Persoana,15> persoane;
    for(Persoana p : persoane) {
        p.afisare();
    }
    cout<<Persoana::getContor();


    return 0;
}
*/
/////////////////////////////////////////////EXCEPTII 
// Online C++ compiler to run C++ program online
class MyException1 : public exception {
    public:
        const char *what(){return "MyException1 ";}
};
class MyException2 : public exception {
    string msg = "MyException2 ";
    public:
        MyException2(string s) {msg += s;}
        const char *what() {return msg.c_str();}
};

void f1() {throw MyException1();}
void f2() {throw MyException2("HEHEHE am adaugat ceva in mesai");}
void f3() {throw 57238; }
void f4() {throw bad_typeid();}

int main() {
    try {
        //f1();
        //f2();
        f4();
    } catch(MyException1 &ex) {
        cout<<ex.what();
    } catch(MyException2 &ex) {
        cout<<ex.what();
    } catch(int i) {
        cout<<i;
    } catch (exception &ex) {
        cout<<ex.what();
    }
    return 0;
}
