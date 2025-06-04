#include <iostream>
#include <string>
using namespace std;
class Animal {
protected:
    unsigned int nrPicioare;
    string nume;
public:
    Animal(unsigned int nrPicioare = 1, string nume = "Schiop") {
        this->nrPicioare = nrPicioare;
        this-> nume = nume;
    }
    virtual void afisare() {cout<<"Nume: "<<nume<<endl<<"nrPicioare: "<<nrPicioare<<endl;}
};

class Marsupial : public Animal {
    int volumMarsupiu;
public:
    Marsupial(unsigned int nrPicioare = 1, string nume="Spanac", int volumMarsupiu = 3) : Animal(nrPicioare,nume) {
        this->volumMarsupiu = volumMarsupiu;
    }
    void afisare() {
        Animal::afisare();
        cout<<"volumMarsupiu: "<<volumMarsupiu<<endl;
    }
    virtual void hop() {cout<<"hop hop";}
};

class Koala : public Marsupial{
public:
    void afisare(){
        Marsupial::afisare();
    } 
    void hop() {cout<<"kOALA HOP";}
};




int main() {
    Animal animal(3,"AnimalStandard");
    Marsupial cangur(1,"Johnson",5);
    
    //animal.afisare();
    //cangur.afisare();
    //etichetare
    Animal* a =  &cangur;
    a->afisare();
    
    
   

    return 0;
}