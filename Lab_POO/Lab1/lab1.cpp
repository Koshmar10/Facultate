#include<iostream>
#include <string>
#include <vector>

using namespace std;

//exemplu proiect

class Camera {
    private:
        string nume;
        float suprafata;
    public:
    Camera(string nume = "Hol", float suprafata = 15.2);
    void incSup(float v){this->suprafata+=v;};
    float getSup(){return this->suprafata;};
};

class Locuinta{
    private:
        string tip;
        vector<Camera> camere;
    public:
        Locuinta(string tip, vector<Camera> camere) {
            this->tip = tip;
            this->camere = camere;
        }
        float getTotalSup();
};
float Locuinta::getTotalSup(){
    float st;
    for(auto &c: camere){
        st+=c.getSup();
    }
    return st;
}

Camera::Camera(string nume, float suprafata){
    this->nume = nume;
    this->suprafata = suprafata;
}
class Proprietar{
    private:
        string nume;
        Locuinta *locuinta;
    public:
        Proprietar(string nume= "Razvan", Locuinta *locuinta = nullptr)
};
int main()
{
    Camera c1("Baie", 13);
    cout<<c1.getSup()<<"\n";

    return 0;
}