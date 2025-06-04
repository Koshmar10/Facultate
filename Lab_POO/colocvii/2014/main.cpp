#include<iostream>
#include <vector>
using namespace std;


class Pacient {
    protected:
        string nume;
        string prenume;
        int varsta;
        string adresa;
    public:
        Pacient(string nume = "", string prenume = "", int varsta = 0, string adresa = "")
        : nume(nume), prenume(prenume), adresa(adresa), varsta(varsta) {}
        ~Pacient(){};
    
        Pacient(const Pacient& other) {
            this->nume = other.nume;
            this->adresa = other.adresa;
            this -> varsta = other.varsta;
            this-> prenume = other.prenume;
        };

        void set_nume(string nume) {this->nume = nume;}
        void set_varsta(int varsta) {this->varsta = varsta;}
        void set_adresa(string adresa) {this->adresa = adresa;}
        void set_prenume(string prenume) {this->prenume = prenume;}

        string get_nume() const {return this->nume;}
        string get_adresa() const {return this->adresa;}
        string get_prenume() const {return this->prenume;}
        int get_varsta() const {return this->varsta;}

        friend istream& operator>> (istream& in, Pacient& p) {
            cout << "Nume: "; in >> p.nume;
            
            cout << "Prenume: "; in >> p.prenume;
            cout << "Adresa: "; in >> p.adresa;
            cout << "Varsta: "; in >> p.varsta;
            return in;
        }
        void show_info(){
            cout<<this->nume<<"\n";
            cout<<this->prenume<<"\n";
            cout<<this->adresa<<"\n";
            cout<<this->nume<<"\n";
            
            
            

        }
    };

class FisaMedicala {
    protected:
        Pacient* pacient;
        int colesterol;
        int tensiune_arteriala;
    public:
    FisaMedicala(Pacient* p = nullptr,  int colesterol = 0, int tensiune_arteriala = 0): pacient(p), colesterol(colesterol), tensiune_arteriala(tensiune_arteriala){};
    virtual ~FisaMedicala(){};

    FisaMedicala(const FisaMedicala& other){
        this->colesterol = other.colesterol;
        this->tensiune_arteriala = other.tensiune_arteriala;
    }
    void set_pacient(Pacient* p){this->pacient = p;}
    virtual void  read_info(istream& in ) {
            cout<<"Colesterol: "; in>>this->colesterol;
            cout<<"Tensiune: "; in>>this->tensiune_arteriala;
    };
    virtual void show_info() {
        this->pacient->show_info();
        cout<<"Colesterol: "<<this->colesterol;
        cout<<"Tensiune: "<<this->tensiune_arteriala;
    };
    virtual bool high_risk(){
        return (this-> colesterol >=240 && this->tensiune_arteriala>=140) ;
    }
};
class FisaMedicalaCopil : public FisaMedicala{
    string data;
    string nume_parinti;
    string prenume_mama;
    string prenume_tata;
    double proteina_C;

    public:

        FisaMedicalaCopil(Pacient* p = nullptr, int  col = 0, int ten =0, string np ="", string pt = "", string pm ="", double prot= 0.0)
        : FisaMedicala(p, col, ten), nume_parinti(np), prenume_mama(pm), prenume_tata(pt), proteina_C(prot){};
        ~FisaMedicalaCopil(){};
        FisaMedicalaCopil(const FisaMedicalaCopil& other) : FisaMedicala(other) {
            this->nume_parinti = other.nume_parinti;
            this->prenume_mama = other.prenume_mama;
            this->prenume_tata = other.prenume_tata;
            this->proteina_C = other.proteina_C;
            this->pacient = other.pacient ? new Pacient(*other.pacient) : nullptr;
        }
        void read_info(istream &in ){
            cout<<"Colesterol: "; in>>this->colesterol;
            cout<<"Tensiune: "; in>>this->tensiune_arteriala;
            cout<<"Nume parinti: "; in>> this->nume_parinti;
            cout<<"Prenume mama: "; in >> this->prenume_mama;
            cout<<"Prenume tata: "; in >> this->prenume_tata;
            cout<<"Proteina C: "; in>> this->proteina_C;
            
        } 
        friend istream& operator>>(istream& in, FisaMedicalaCopil& f){
            f.read_info(in);
            return in;
        }
        void show_info(){

            this->pacient->show_info();
            cout<<"Colesterol: "<<this->colesterol;
            cout<<"Tensiune: "<<this->tensiune_arteriala;
            cout<<"Mama: "<< this->nume_parinti<<" "<<this->prenume_mama;
            cout<<"Tata: "<< this->nume_parinti<<" "<<this->prenume_tata;
        }
        virtual bool high_risk(){
            return (this-> colesterol >=240 && this->tensiune_arteriala>=140) ;
        }

    
};
class FisaMedicalaAdlultPeste40 : public FisaMedicala{
    bool este_fumator;
    bool este_sedentar;

    public:

    FisaMedicalaAdlultPeste40(Pacient* p = nullptr, int  col = 0, int ten =0, bool f= false, bool s = false)
    : FisaMedicala(p,col, ten), este_fumator(f), este_sedentar(s){};
    FisaMedicalaAdlultPeste40(const FisaMedicalaAdlultPeste40& other) : FisaMedicala(other) {
        this->este_fumator = other.este_fumator;
        this->este_sedentar = other.este_sedentar;
        this->pacient = other.pacient ? new Pacient(*other.pacient) : nullptr;
    }
    
    void read_info(istream &in ){
        cout<<"Colesterol: "; in>>this->colesterol;
        cout<<"Tensiune: "; in>>this->tensiune_arteriala;
        string x;
        cout<<"Fumator: "; in>> x;
        if (x == "da") {
            this->este_fumator = true;
        }
        else {
            this->este_fumator = false;
        }
        cout<<"Sedentar: "; in >> x;
        if (x == "da") {
            this->este_sedentar = true;
        }
        else {
            this->este_sedentar = false;
        }
    }

    friend istream& operator>>(istream& in, FisaMedicalaAdlultPeste40& f){
        f.read_info(in);
        return in;
    }
    void show_info(){
        this->pacient->show_info();
        cout<<"Colesterol: "<<this->colesterol;
        cout<<"Tensiune: "<<this->tensiune_arteriala;
        if (este_fumator)
            cout<<"Fumator: DA";
        else
            cout<<"Fumator: NU";
            if (este_sedentar)
            cout<<"Sedentar: DA";
        else
            cout<<"Sedentar: NU";
        
    }
    
};
class DosarCabinet{
    private:
        vector<FisaMedicala*> fise_medicale;
    public:
    DosarCabinet(vector<FisaMedicala*> f = {}) : fise_medicale(f){}; 
    ~DosarCabinet(){
        for (auto& fisa : fise_medicale){
            delete fisa;
        }
    }
    void add_fisa(FisaMedicala* f){
        fise_medicale.push_back(f);
    }

    void toti_pacientii(){
        for (auto& pacient : this->fise_medicale){
            pacient->show_info();
        }
    }
    void toti_pacientii(string nume){}
    
    void adulti_risc(){}
    void toti_copii_risc(){}

};

int main()
{
    DosarCabinet dosar_cabinet = DosarCabinet();
    for(int i =0; i < 2; i++){
        Pacient p;
        cin>>p;
        if (p.get_varsta() < 18){
            FisaMedicalaCopil f;
            cin>>f;
            f.set_pacient(new Pacient(p));
            dosar_cabinet.add_fisa(new FisaMedicalaCopil(f));
        }else if (p.get_varsta() > 40){
            FisaMedicalaAdlultPeste40 f;
            cin>>f;
            f.set_pacient(new Pacient(p));
            dosar_cabinet.add_fisa(new FisaMedicalaAdlultPeste40(f));
        }else{

        }
        cout<<" \n";
        
    }
    dosar_cabinet.toti_pacientii();
    return 0;
}