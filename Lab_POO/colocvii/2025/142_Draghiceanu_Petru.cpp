/*
Draghiceanu
Petru
Compilator si flag-uri : g++ -g 142_Draghiceanu_Petru.cpp -o 142_Draghiceanu_Petru
Tutore de laborator: Razvan Campian
*/
#include<iostream>
#include <vector>
using namespace std;
class Produs{
    protected:
    string nume;
    int gramaj;
    public:
    Produs(string nume="", int gr = 0): nume(nume), gramaj(gr){};
    Produs(const Produs &other) : nume(other.nume), gramaj(other.gramaj){};
    ~Produs(){};
    //functie pentru citirea atributelor comune
    void read_base(istream& in){
        cout<<"\nNume Produs: "; in>>nume;
        cout<<"\nGramaj Produs"; in>>gramaj;
    }

    virtual float valoare_energetica() = 0;
};
class Bautura: public Produs{
    //protected pentru ca in viitor pot exita bauturi cola, sprite, drPepper etc
    protected:
    bool este_sticla;
    public:
    Bautura(string nume="", int gr = 0, bool sticla = false): Produs(nume, gr), este_sticla(sticla){};
    Bautura(const Bautura &other) : Produs(other), este_sticla(other.este_sticla){};
    ~Bautura(){};

    float valoare_energetica(){
        if (este_sticla){
            return 0.25 * gramaj;
        }else{
            return 25;
        }
    }
    friend istream& operator>>(istream& in, Bautura& b){
        b.read_base(in);
        int x;
        cout<<"\nEste la sticla(0/1)";
        in>>x;
        if (x == 1)
            b.este_sticla = true;
        else
            b.este_sticla = false;
        return in;
    }
};
class Desert: public Produs{
    private:
    string format_servire;
    public:
    Desert(string nume="", int gr = 0, string fs = ""): Produs(nume, gr), format_servire(fs){};
    Desert(const Desert &other) : Produs(other), format_servire(other.format_servire){};
    ~Desert(){};

    float valoare_energetica(){
        if (format_servire == "felie"){
            return 25;
        }else if (format_servire == "portie"){
            return 0.5 * gramaj;
        }else if (format_servire == "cupa"){
            return gramaj *2;
        }
    }
    friend istream& operator>>(istream& in, Desert& b){
        b.read_base(in);
        cout<<"\nFormat servire: "; in>>b.format_servire;
        return in;    
    }

};
class Burger : public Produs{
    private:
    vector<string> ingrediente;
    public:
    Burger(string nume="", int gr = 0, vector<string> ingrediente={}): Produs(nume, gr), ingrediente(ingrediente){};
    Burger(const Burger &other) : Produs(other), ingrediente(other.ingrediente){};
    ~Burger(){};

    float valoare_energetica(){
        return gramaj * 0.25 * ingrediente.size();
    }

    friend istream& operator>>(istream& in, Burger& b){
        b.read_base(in);
        int x;
        cout<<"\nNumar de ingrediente>: ";
        in>>x;
        for(int i=0; i < x; i++){
            string a;
            cout<<"\nIngredient: "; in >>a;
            b.ingrediente.push_back(a);
        }
        return in;
    }
};
/*
am inteles gresit si am implementat ceva mai
*/
class Comanda{
    private:
    int id;
    vector<Produs*>produse;
    int energie = 0;
    public:
    Comanda(int id = -1, int energie = 0, vector<Produs*> p={}) : id(id),energie(energie), produse(p){};
    Comanda(const Comanda& other) : id(other.id), produse(other.produse) {} ;
    ~Comanda(){
        for (auto& p : produse){
            if (p)
            delete p;
        }
    }
    int get_energie() const {return energie;}
    void set_energie(int n) {energie = n;}
    friend istream& operator>>(istream& in, Comanda& c){
        int nr, choice;
        cout<<"\nValoare energetica"; in>>c.energie;
        cout<<"\nCate Produse Citesti: ";
        in>>nr; 
        for(int i=0; i<nr; i++){
            cout<<"\nCe Produs adaugi Bautura(1), Desert(2), Burger(3)";
            in>>choice;
            if (choice == 1){
                Bautura b;
                in>>b;  
                c.produse.push_back(new Bautura(b));
            }else if(choice ==3) {
                Burger b;
                in>>b;  
                c.produse.push_back(new Burger(b));

            }else if(choice ==3){
                Desert d;
                in>>d;  
                c.produse.push_back(new Desert(d));
            }
        }
        return in;
    }
    float valoare_energeica(){
        float cost= 0;
        for (auto& prod : produse){
            cost+= prod->valoare_energetica();
        }
        return cost;
    }
    bool operator<(Comanda& c){
        return valoare_energeica() < c.valoare_energeica();
    }
    friend ostream& operator<<(ostream& out, const Comanda& c){
        cout<<"\nValoare: "; out<<c.energie;
        return out;
    }
};

class Angajat{
    protected:
    int puncte_energie;
    public:
    Angajat(int p = 0): puncte_energie(p){};
    Angajat(const Angajat& other): puncte_energie(other.puncte_energie){};
    ~Angajat();

    virtual void actiune() = 0;
    virtual void reset() = 0;
    int get_energie() const {return puncte_energie;}
    void set_energie(int n_pctj) {this->puncte_energie = n_pctj;}
};
class Casier: public Angajat{
    public:
    Casier(int p = 0): Angajat(p){};
    Casier(const Casier& other): Angajat(other){};
    ~Casier();
    void actiune(){
        puncte_energie-=25;   
    }
    void reset() {
        puncte_energie =100;
    };
};
class Livrator: public Angajat{
    public:
    Livrator(int p = 0): Angajat(p){};
    Livrator(const Livrator& other): Angajat(other){};
    ~Livrator();
    void actiune(){
        puncte_energie-=25;
    }
    void reset() {
        puncte_energie =100;
    };
};
class Bucatar: public Angajat{
    public:
    Bucatar(int p = 0): Angajat(p){};
    Bucatar(const Bucatar& other): Angajat(other){};
    ~Bucatar();
    void actiune(){
        puncte_energie-=25;
    }
    void reset() {
        puncte_energie =+100;
    };

};
//vrem sa existe doar o singgura simulare
class Simulare{
    private:
    static Simulare* simulare;
    vector<Comanda*> comenzi;
    vector<Angajat*> angajati;
    static int next_id;
    Simulare(vector<Comanda*> c ={}, vector<Angajat*>a={}) : comenzi(c), angajati(a){};
    ~Simulare(){
        for (auto& c : comenzi){
            if (c)
            delete c;
        }
        for (auto& a : angajati){
            if (a)
            delete a;
        }
    }
    public:
    static Simulare* Instance(){
        if (simulare == nullptr){
            simulare = new Simulare;
        }
        return simulare;
    }
    Simulare(const Simulare&otehr) =delete;
    Simulare operator=(const Simulare&other) = delete;

    void preluare_comenzi(){
        int nr;
        cout<<"\nCate comenzi vrei sa citest: ";
        cin>>nr;
        for (int i=0; i<nr; i++){
            Comanda c(next_id++);
            cin>>c;
            comenzi.push_back(new Comanda(c));
        }
    };
    void afisare_angajati(){
        int bucatari=0, casieri=0, livratori=0;
        for(auto& angajat : angajati){
            if(dynamic_cast<Casier*>(angajat)!=nullptr){
                casieri+=1;
            }
            if(dynamic_cast<Bucatar*>(angajat)!=nullptr){
                bucatari+=1;
            }
            if(dynamic_cast<Livrator*>(angajat)!=nullptr){
                livratori+=1;
            }
        }
        cout<<"\nCasieri: "<<casieri;
        cout<<"\nBUcatari: "<<bucatari;
        cout<<"\nLivratori: "<<livratori;
    }
    void preparare_comenzi(){
        //fiecare bucatar va prepara maxim o comanda si isi va consuma energia pe comanda sis
        //iau fiecare comanda si pun toti cate un bucatar sa incerce sa o termine
        for (auto& c : comenzi){
            if ( c->get_energie() > 0){
                for (auto &a : angajati){
                    if(auto em = dynamic_cast<Bucatar*>(a)){
                        while (c->get_energie() > 0 && em->get_energie()>0){
                            c->set_energie(c->valoare_energeica() - 2 *em->get_energie());
                            em->set_energie(0);
                            if(c->get_energie() < 0) {
                                c->set_energie(0);
                            }
                        }
                    }
                }
            }
        }
    }
    void livrare_comenzi(){
        int nr_comenzi = comenzi.size();
        //iau fiecare livrator si il pun sa livreze comenzi pana nu mai are  energie
        for(auto& angajat : angajati){
            if(auto em = dynamic_cast<Livrator*>(angajat)){
                while(nr_comenzi>0 && em->get_energie() >0){
                    em->actiune();
                    nr_comenzi-=1;
                    comenzi.erase(comenzi.begin(), comenzi.begin()+1);
                }
            }
        }
    };
    void resetare_angajati(){
        for (auto& angajat : angajati){
            angajat->reset();
        }
    };

    void prioritizare(){
        int x;
        cout<<"\nPrioritizare comenzi(1 da/0 nu): ";
        cin>>x;
        bool descending;
        if(x==1){
            cout<<"\n de la greu la usor sau invers(1/0)";
            cin>>x;
            if ( x== 1)
                descending = true;
            else
            descending = false;

            for(int i =0; i<comenzi.size(); i++){
                for (int j=i+1; j<comenzi.size(); j++){
                    if (descending){

                        if (comenzi[i] < comenzi[j]){
                            swap(comenzi[i], comenzi[j]);
                        }
                    }else{
                        if ( !(comenzi[i] < comenzi[j])){
                            swap(comenzi[i], comenzi[j]);
                        }
                    }
                }
            }
        }
    }
    void afisare_comenzi(){
        for (auto& c : comenzi){
            cout<<c;
        }
    }
    void run(){
        preluare_comenzi();
        afisare_comenzi();
        preparare_comenzi();
        livrare_comenzi();
        resetare_angajati();
    }
   
};
Simulare* Simulare::simulare = nullptr;
int Simulare::next_id =0;
int main()
{
    Simulare* sim = Simulare::Instance();
    sim->run();
    return 0;
}