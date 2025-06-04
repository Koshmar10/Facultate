#include<iostream>
#include <vector>
using namespace std;
class Jucarie {
    protected: 
    string denumire;
    int dimensiune;
    string tip;
    public:
    Jucarie(string den ="", int dim = 0 , string tip="")
    :denumire(den), dimensiune(dim), tip(tip){};
    Jucarie(const Jucarie& other){
        denumire = other.denumire;
        dimensiune = other.dimensiune;
        tip = other.tip;
    }
    ~Jucarie(){};

    void read_base(istream& in){
        cout<<"\nDenumire: "; in>>denumire;
        cout<<"\nDimensiune: "; in>>dimensiune;
        cout<<"\nTip: "; in>>tip;
    }
    void show_base(ostream& out){
        out<<"\nDenumire: "<<denumire;
        out<<"\nDimensiune: "<<dimensiune;
        out<<"\nTip: "<<tip;
    }
    friend istream& operator>>(istream& in, Jucarie& j){
        j.read_base(in);
        return in;
    }
    friend ostream& operator>>(ostream& out, Jucarie& j){
        j.show_base(out);
        return out;
    }

};
class JucarieClasica : public Jucarie {
    
    string material;
    string culoare;

    public:
    JucarieClasica(string den ="", int dim = 0 , string tip="", string mat = "", string col ="")
    :Jucarie(den, dim, tip), material(mat), culoare(col){};
    JucarieClasica(const JucarieClasica& other)
        : Jucarie(other), material(other.material), culoare(other.culoare) {}
    ~JucarieClasica(){};

    friend istream& operator>>(istream& in, JucarieClasica& j){
        j.read_base(in);
        cout<<"\nMatrial: "; in>>j.material;
        cout<<"\nCuloare: "; in>>j.culoare;
        return in;
    }
    friend ostream& operator<<(ostream& out, JucarieClasica& j){
        j.show_base(out);
        out<<"\nMatrial: "<<j.material;
        out<<"\nCuloare: "<<j.culoare;
        return out;
    }

};
class JucarieEducativa : virtual public Jucarie {
    protected:
    string abilitate_dezvoltata;
    public:
    JucarieEducativa(string den ="", int dim = 0 , string tip="", string ab = "")
    :Jucarie(den, dim, tip), abilitate_dezvoltata(ab){};
    JucarieEducativa(const JucarieEducativa& other)
    :Jucarie(other), abilitate_dezvoltata(other.abilitate_dezvoltata){};
    ~JucarieEducativa(){};

    friend istream& operator>>(istream& in, JucarieEducativa& j){
        j.read_base(in);
        cout<<"\nAbilitate: "; in>>j.abilitate_dezvoltata;
        return in;
    }

    friend ostream& operator<<(ostream& out, JucarieEducativa& j){
        j.show_base(out);
        out<<"\nAbilitate: "<<j.abilitate_dezvoltata;
        return out;
    }
};
class JucarieElectronica : virtual public Jucarie {
    protected:
    int nr_baterii;
    public:
    JucarieElectronica(string den ="", int dim = 0 , string tip="", int nr_bat = 0)
    :Jucarie(den, dim, tip), nr_baterii(nr_bat){};
    JucarieElectronica(const JucarieElectronica& other)
    :Jucarie(other), nr_baterii(other.nr_baterii){};
    ~JucarieElectronica(){};

    friend istream& operator>>(istream& in, JucarieElectronica& j){
        j.read_base(in);
        cout<<"\nBaterii: "; in>>j.nr_baterii;
        return in;
    }

    friend ostream& operator<<(ostream& out, JucarieElectronica& j){
        j.show_base(out);
        cout<<"\nBaterii: "<<j.nr_baterii;
        return out;
    }
};

class JucarieModerna : public JucarieEducativa, public JucarieElectronica {
    string breand;
    string model;

public:
    JucarieModerna(string den = "", int dim = 0, string tip = "", string ab = "", int nr_bat = 0, string br = "", string mod = "")
        : Jucarie(den, dim, tip), JucarieEducativa(den, dim, tip, ab), JucarieElectronica(den, dim, tip, nr_bat), breand(br), model(mod) {}
    JucarieModerna(const JucarieModerna& other)
    :Jucarie(other.denumire, other.dimensiune, other.tip), JucarieEducativa(other), JucarieElectronica(other), breand(other.breand), model(other.model) {};
    ~JucarieModerna() {}

    friend istream& operator>>(istream& in, JucarieModerna& j) {
        j.JucarieEducativa::read_base(in); // Explicitly call the base class method
        cout << "\nAbilitate: ";
        in >> j.abilitate_dezvoltata;
        cout << "\nBaterii: ";
        in >> j.nr_baterii;
        cout << "\nBrand: ";
        in >> j.breand;
        cout << "\nModel: ";
        in >> j.model;
        return in;
    }

    friend ostream& operator<<(ostream& out, JucarieModerna& j) {
        j.JucarieEducativa::show_base(out); // Explicitly call the base class method
        cout << "\nAbilitate: "<<j.abilitate_dezvoltata;
        cout << "\nBaterii: "<<j.nr_baterii;
        cout << "\nBrand: "<<j.breand;
        cout << "\nModel: "<<j.model;
        return out;
    }
};

class Copil {
    protected:
    int id;
    string nume;
    string prenume;
    string adresa;
    int varsta;
    int nr_fapte_bune;
    vector<Jucarie*> jucarii;

    public:
    Copil(int id=0, string num = "", string pre ="", string ad ="", int v = 0, int nfb = 0, vector<Jucarie*> j = {})
    :id(id), nume(num), prenume(pre), adresa(ad), varsta(v), nr_fapte_bune(nfb), jucarii(j){};
    Copil(const Copil& other){
        prenume = other.prenume;
        nume = other.nume;
        adresa = other.adresa;
        varsta = other.varsta;
        nr_fapte_bune = other.nr_fapte_bune;
        jucarii.clear();
        for (auto j : other.jucarii) {
            jucarii.push_back(new Jucarie(*j)); // Assuming Jucarie has a copy constructor
        }
    }
    ~Copil() {
        for (auto& j : jucarii){
            delete j;
        }
    }
    void read_base(istream& in){
        cout<<"\nNume: "; in>>this->nume;
        cout<<"\nPrenume: "; in>>this->prenume;
        cout<<"\nAdresa: "; in>>this->adresa;
        cout<<"\nVarsta: "; in>>this->varsta;
        cout<<"\nFapteBune:"; in>>this->nr_fapte_bune; 
    }

    void show_base(ostream& out){
        out<<"\nNume: "<<this->nume;
        out<<"\nPrenume: "<<this->prenume;
        out<<"\nAdresa: "<<this->adresa;
        out<<"\nVarsta: "<<this->varsta;
        out<<"\nFapteBune:"<<this->nr_fapte_bune; 
    }

    friend istream& operator>>(istream& in, Copil& c){
        c.read_base(in);
        return in;
    }
    friend ostream& operator<<(ostream& out, Copil& c){
        c.show_base(out);
        return out;
    }
};

class CopilCuminte :public Copil{
    int nr_dulciuri;
    public:
    CopilCuminte(int id=0, string num = "", string pre ="", string ad ="", int v = 0, int nfb = 0, vector<Jucarie*> j = {}, int nr_dulciuri= 0)
    :Copil(id, num, pre, ad, v, nfb, j), nr_dulciuri(nr_dulciuri){};
    CopilCuminte(const CopilCuminte& other) : Copil(other) , nr_dulciuri(other.nr_dulciuri){};
    
    ~CopilCuminte() {
        for (auto& j : jucarii){
            delete j;
        }
    }
    friend istream& operator>>(istream& in, CopilCuminte& c){
        c.read_base(in);
        while(c.nr_fapte_bune < 10){
            cout<<"\nIncorect fapte une trebuie sa fie mai mare decata 10 \n";
            cout<<"\nFapteBune:"; in>>c.nr_fapte_bune; 
        }
        cout<<"\nDulciuri"; in>>c.nr_dulciuri;
        for (int i=0; i<c.nr_fapte_bune; i++){
            if (i%4 == 0)
            {
                JucarieClasica j;
                cin>>j;
                c.jucarii.push_back(new JucarieClasica(j));
            }
            if (i%4 == 1){

                JucarieElectronica j;
                cin>>j;
                c.jucarii.push_back(new JucarieElectronica(j));
            }
            if (i%4 == 2){

                JucarieEducativa j;
                cin>>j;
                c.jucarii.push_back(new JucarieEducativa(j));
            }
            if (i%4 == 3){
                
                JucarieModerna j;
                cin>>j;
                c.jucarii.push_back(new JucarieModerna(j));
            }
        }
        return in;
    }
    friend ostream& operator<<(ostream& out, CopilCuminte& c){
        c.show_base(out);
        out<<"\nDulciuri"<<c.nr_dulciuri;
           return out;
    }
};
class CopilObraznic : public Copil {
    int nr_carbuni;
    public:
    CopilObraznic(int id=0, string num = "", string pre ="", string ad ="", int v = 0, int nfb = 0, vector<Jucarie*> j = {}, int nr_carbuni= 0)
    :Copil(id, num, pre, ad, v, nfb, j), nr_carbuni(nr_carbuni){};
    CopilObraznic(const CopilObraznic& other) : Copil(other) , nr_carbuni(other.nr_carbuni){};
    ~CopilObraznic() {
        for (auto& j : jucarii){
            delete j;
        }
    }
    friend istream& operator>>(istream& in, CopilObraznic& c){
        c.read_base(in);
        cout<<"\nCarbuni: "; in>>c.nr_carbuni;
        for (int i=0; i<c.nr_fapte_bune; i++){
            if (i%4 == 0)
            {
                JucarieClasica j;
                cin>>j;
                c.jucarii.push_back(new JucarieClasica(j));
            }
            if (i%4 == 1){

                JucarieElectronica j;
                cin>>j;
                c.jucarii.push_back(new JucarieElectronica(j));
            }
            if (i%4 == 2){

                JucarieEducativa j;
                cin>>j;
                c.jucarii.push_back(new JucarieEducativa(j));
            }
            if (i%4 == 3){
                
                JucarieModerna j;
                cin>>j;
                c.jucarii.push_back(new JucarieModerna(j));
            }
        }
        return in;
    }
    friend ostream& operator<<(ostream& out, CopilObraznic& c){
        c.show_base(out);
        out<<"\nCarbuni: "<<c.nr_carbuni;
           return out;
    }
    
};


class SantaList{
    private:
    static int next_id;
    vector<Copil*> copii;
    public:
    SantaList(vector<Copil*> c ={}) : copii(c){
    };
    ~SantaList(){
        for (auto& copil : copii){
            delete copil;
        }
    };
    void adauga_cuminte(){
        CopilCuminte c; 
        cin>>c;
        copii.push_back(new CopilCuminte(c));
    }
    void adauga_obraznic(){
        CopilObraznic c; 
        cin>>c;
        copii.push_back(new CopilObraznic(c));
    }
    void afiseaza(){
        for (auto& copil : copii){
            cout<<*copil;
        }
    }
};
int SantaList::next_id =0;

int main()
{

    SantaList lista = SantaList();
    lista.adauga_cuminte();
    lista.afiseaza();
    return 0;
}