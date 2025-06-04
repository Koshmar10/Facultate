/*Anonim Anonim, grupa Anonim
CodeBlock 16.01 GNU CC Compiler, flag: have g++ follow the c++ ISO C++ language standard [~std=c++11]
Tutore laborator: Gusatu Marian*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <algorithm>
#include<sstream>

using namespace std;

class Masca {
protected:
    string tipprot;
    string culoare;
    int nrpliuri;

public:
    Masca(const string &tipprot, const string &culoare, int nrpliuri);
    virtual ~Masca();

    const string &getTipprot() const;

    void setTipprot(const string &tipprot);

    const string &getCuloare() const;

    void setCuloare(const string &culoare);

    int getNrpliuri() const;

    void setNrpliuri(int nrpliuri);

    virtual void citire(istream&);
    virtual void afisare(ostream&) const;
    friend istream& operator>>(istream& in, Masca& obj);
    friend ostream& operator<<(ostream& out, const Masca& obj);
    Masca(const Masca& obj);
    Masca& operator=(const Masca& obj);
};
Masca::Masca(const string &tipprot="", const string &culoare="", int nrpliuri=0) : tipprot(tipprot), culoare(culoare),
                                                                                   nrpliuri(nrpliuri) {}
Masca::~Masca() {
    tipprot="";
    culoare="";
    nrpliuri=0;
}


Masca::Masca(const Masca& obj) {
    this->tipprot = obj.tipprot;
    this->culoare = obj.culoare;
    this->nrpliuri = obj.nrpliuri;
}

Masca& Masca::operator=(const Masca& obj) {
    if (this != &obj) {
        this->tipprot = obj.tipprot;
        this->culoare = obj.culoare;
        this->nrpliuri = obj.nrpliuri;
    }
    return *this;
}
const string &Masca::getTipprot() const {
    return tipprot;
}
void Masca::setTipprot(const string &tipprot) {
    this->tipprot = tipprot;
}
const string &Masca::getCuloare() const {
    return culoare;
}
void Masca::setCuloare(const string &culoare) {
    this->culoare = culoare;
}
int Masca::getNrpliuri() const {
    return nrpliuri;
}
void Masca::setNrpliuri(int nrpliuri) {
    this->nrpliuri = nrpliuri;
}
void Masca::citire(istream& in) {
    cout << "Culoare: ";
    getline(in, culoare);
    cout<<"Nr pliuri: ";
    in >> nrpliuri;
}
void Masca::afisare(ostream& out) const {
    out << ",culoare: "<<culoare<<", nr pliuri: "<<nrpliuri;
}
istream& operator>>(istream& in, Masca& obj) {
    obj.citire(in);
    return in;
}
ostream& operator<<(ostream& out, const Masca& obj) {
    obj.afisare(out);
    return out;
}



class MascaChirurgicala : public Masca {
public:
    MascaChirurgicala(const string &tipprot, const string &culoare, int nrpliuri);
    ~MascaChirurgicala();
    MascaChirurgicala(const MascaChirurgicala& obj);
    MascaChirurgicala& operator=(const MascaChirurgicala& obj);
    void citire(istream&);
    void afisare(ostream&) const;
    friend istream& operator>>(istream& in, MascaChirurgicala& obj);
    friend ostream& operator<<(ostream& out, const MascaChirurgicala& obj);
};
MascaChirurgicala::MascaChirurgicala(const string &tipprot="", const string &culoare="", int nrpliuri=0) : Masca(tipprot,
                                                                                                                 culoare,
                                                                                                                 nrpliuri) {}
MascaChirurgicala::~MascaChirurgicala() {
}
void MascaChirurgicala::citire(istream& in) {
    cout<<"Tip protectie(ffp1/ffp2/ffp3): ";
    in>>tipprot;
    Masca::citire(in);
}
void MascaChirurgicala::afisare(ostream& out) const {
    out<<"\nTip protectie: "<<tipprot;
    Masca::afisare(out);
}
istream& operator>>(istream& in, MascaChirurgicala& obj) {
    obj.citire(in);
    return in;
}
ostream& operator<<(ostream& out, const MascaChirurgicala& obj) {
    obj.afisare(out);
    return out;

}


MascaChirurgicala::MascaChirurgicala(const MascaChirurgicala& obj) : Masca(obj) {
}

MascaChirurgicala& MascaChirurgicala::operator=(const MascaChirurgicala& obj) {
    if (this != &obj) {
        Masca::operator=(obj) ;
    }
    return *this;
}


class MascaPolicarbonat : public Masca {
    string tipPrindere;
public:
    MascaPolicarbonat(const string &tipPrindere, const string &tipprot, const string &culoare, int nrpliuri);
    ~MascaPolicarbonat();
    MascaPolicarbonat(const MascaPolicarbonat& obj);
    MascaPolicarbonat& operator=(const MascaPolicarbonat& obj);
    const string &getTipPrindere() const;

    void setTipPrindere(const string &tipPrindere);

    void citire(istream&);
    void afisare(ostream&) const;
    friend istream& operator>>(istream& in, MascaPolicarbonat& obj);
    friend ostream& operator<<(ostream& out, const MascaPolicarbonat& obj);
};
MascaPolicarbonat::MascaPolicarbonat(const string &tipPrindere="",const string &tipprot="", const string &culoare="",
                                     int nrpliuri=0) : Masca(tipprot, culoare, nrpliuri), tipPrindere(tipPrindere) {}
MascaPolicarbonat::~MascaPolicarbonat() {
    tipPrindere="";
}
const string &MascaPolicarbonat::getTipPrindere() const {
    return tipPrindere;
}

void MascaPolicarbonat::setTipPrindere(const string &tipPrindere) {
    this->tipPrindere = tipPrindere;
}

MascaPolicarbonat::MascaPolicarbonat(const MascaPolicarbonat &obj): Masca(obj) {
    this->tipPrindere=obj.tipPrindere;
}

MascaPolicarbonat &MascaPolicarbonat::operator=(const MascaPolicarbonat &obj) {
    if (this != &obj) {
        Masca::operator=(obj) ;
        this->tipPrindere=obj.tipPrindere;
    }
    return *this;
}

void MascaPolicarbonat::citire(istream& in) {
    tipprot="ffp0";
    Masca::citire(in);
    cout << "Tip prindere(elastic/scai/...): ";
    in >> tipPrindere;
}
void MascaPolicarbonat::afisare(ostream& out) const {
    out<<"\nTip protectie "<<tipprot;
    Masca::afisare(out);
    out << ", tip prindere: " << tipPrindere;
}
istream& operator>>(istream& in, MascaPolicarbonat& obj) {
    obj.citire(in);
    return in;
}
ostream& operator<<(ostream& out, const MascaPolicarbonat& obj) {
    obj.afisare(out);
    return out;
}



class Dezinfectant {
protected:
    int nrspecii;
    vector<string> ingrediente;
    vector<string> suprafete;
    double eficienta;
public:
    Dezinfectant(int nrspecii, vector<string> ingrediente, vector<string> suprafete);
    virtual ~Dezinfectant();

    int getNrspecii() const;

    void setNrspecii(int nrspecii);

    Dezinfectant(const Dezinfectant& obj);
    Dezinfectant& operator=(const Dezinfectant& obj);
    virtual double Eficienta()=0;
    virtual void citire(istream&);
    virtual void afisare(ostream&) const;
    friend istream& operator>>(istream& in, Dezinfectant& obj);
    friend ostream& operator<<(ostream& out, const Dezinfectant& obj);
};
Dezinfectant::Dezinfectant(int nrspecii=0, vector<string> ingrediente=vector<string>()
        , vector<string> suprafete=vector<string>()) : nrspecii(
        nrspecii)
{
    for(unsigned int i=0;i<ingrediente.size();i++)
        this->ingrediente.push_back(ingrediente[i]);
    for(unsigned int i=0;i<suprafete.size();i++)
        this->suprafete.push_back(suprafete[i]);
}
Dezinfectant::~Dezinfectant() {
    nrspecii=0;
    ingrediente.clear();
    suprafete.clear();
    eficienta=0;
}


Dezinfectant::Dezinfectant(const Dezinfectant& obj) {
    this->nrspecii = obj.nrspecii;
    for(unsigned int i=0;i<obj.ingrediente.size();i++)
        this->ingrediente.push_back(obj.ingrediente[i]);
    for(unsigned int i=0;i<obj.suprafete.size();i++)
        this->suprafete.push_back(obj.suprafete[i]);
}

Dezinfectant& Dezinfectant::operator=(const Dezinfectant& obj) {
    if (this != &obj) {
        this->nrspecii = obj.nrspecii;
        for(unsigned int i=0;i<obj.ingrediente.size();i++)
            this->ingrediente.push_back(obj.ingrediente[i]);
        for(unsigned int i=0;i<obj.suprafete.size();i++)
            this->suprafete.push_back(obj.suprafete[i]);
    }
    return *this;
}
int Dezinfectant::getNrspecii() const {
    return nrspecii;
}

void Dezinfectant::setNrspecii(int nrspecii) {
    this->nrspecii = nrspecii;
}
void Dezinfectant::citire(istream& in) {
    cout<<"\nNumar specii: ";
    in>>nrspecii;
    int nring;
    cout<<"Nr ingrediente: ";
    in>>nring;
    cout<<"Enumerati-le: ";
    in.get();
    for(int i=0;i<nring;i++){
        string ing;
        getline(in, ing);
        ingrediente.push_back(ing);
    }

}
void Dezinfectant::afisare(ostream& out) const {
    cout<<"\nNumar specii ucise: "<<nrspecii;
    cout<<"\nIngrediente: \n";
    for(unsigned int i=0;i<ingrediente.size();i++)
        cout<<ingrediente[i]<<"; ";
    cout<<"\nSuprafete: \n";
    for(unsigned int i=0;i<suprafete.size();i++)
        cout<<suprafete[i]<<"; ";
}
istream& operator>>(istream& in, Dezinfectant& obj) {
    obj.citire(in);
    return in;
}
ostream& operator<<(ostream& out, const Dezinfectant& obj) {
    obj.afisare(out);
    return out;
}




class DezinfectantVirusi : virtual public Dezinfectant {
    const int TotalVirusuri;
public:
    DezinfectantVirusi(int nrspecii,vector<string> ingrediente, vector<string> suprafete);
    ~DezinfectantVirusi();
    DezinfectantVirusi(const DezinfectantVirusi& obj);
    DezinfectantVirusi& operator=(const DezinfectantVirusi& obj);
    double Eficienta();
    void citire(istream&);
    void afisare(ostream&) const;
    friend istream& operator>>(istream& in, DezinfectantVirusi& obj);
    friend ostream& operator<<(ostream& out, const DezinfectantVirusi& obj);
};
DezinfectantVirusi::DezinfectantVirusi(int nrspecii=0, vector<string> ingrediente=vector<string>(),
                                       vector<string> suprafete=vector<string>())
        : Dezinfectant(nrspecii, ingrediente, suprafete), TotalVirusuri(100000000) {}
DezinfectantVirusi::~DezinfectantVirusi() {
}
DezinfectantVirusi::DezinfectantVirusi(const DezinfectantVirusi& obj): Dezinfectant(obj), TotalVirusuri(100000000) {
}

DezinfectantVirusi& DezinfectantVirusi::operator=(const DezinfectantVirusi& obj) {
    if (this != &obj) {
        Dezinfectant::operator=(obj) ;
    }
    return *this;
}
double DezinfectantVirusi::Eficienta()
{
    double calcul;
    calcul=nrspecii/TotalVirusuri;
    calcul=calcul*100;
    return calcul;
}
void DezinfectantVirusi::citire(istream& in) {
    Dezinfectant::citire(in);
    int nrsup;
    cout<<"Nr suprafete: ";
    in>>nrsup;
    cout<<"Enumerati-le: ";
    in.get();
    for(int i=0;i<nrsup;i++){
        string supr;
        getline(in, supr);
        suprafete.push_back(supr);
    }
}
void DezinfectantVirusi::afisare(ostream& out) const {
    Dezinfectant::afisare(out);
}
istream& operator>>(istream& in, DezinfectantVirusi& obj) {
    obj.citire(in);
    return in;
}
ostream& operator<<(ostream& out, const DezinfectantVirusi& obj) {
    obj.afisare(out);
    return out;
}




class DezinfectantFungi : virtual public Dezinfectant {
    const int TotalFungi;
public:
    DezinfectantFungi(int nrspecii,vector<string> ingrediente,vector<string> suprafete);
    ~DezinfectantFungi();
    DezinfectantFungi(const DezinfectantFungi& obj);
    DezinfectantFungi& operator=(const DezinfectantFungi& obj);
    double Eficienta();
    void citire(istream&);
    void afisare(ostream&) const;
    friend istream& operator>>(istream& in, DezinfectantFungi& obj);
    friend ostream& operator<<(ostream& out, const DezinfectantFungi& obj);
};

DezinfectantFungi::DezinfectantFungi(int nrspecii=0, vector<string> ingrediente=vector<string>(),
                                     vector<string> suprafete=vector<string>())
        : Dezinfectant(nrspecii, ingrediente, suprafete), TotalFungi(1.5*1000000) {}
DezinfectantFungi::~DezinfectantFungi() {
}
DezinfectantFungi::DezinfectantFungi(const DezinfectantFungi& obj): Dezinfectant(obj), TotalFungi(1.5*1000000) {
}

DezinfectantFungi& DezinfectantFungi::operator=(const DezinfectantFungi& obj) {
    if (this != &obj) {
        Dezinfectant::operator=(obj) ;
    }
    return *this;
}
double DezinfectantFungi::Eficienta()
{
    double calcul;
    calcul=nrspecii/TotalFungi;
    calcul=calcul*100;
    return calcul;
}
void DezinfectantFungi::citire(istream& in) {
    Dezinfectant::citire(in);
    int nrsup;
    cout<<"Nr suprafete: ";
    in>>nrsup;
    cout<<"Enumerati-le: ";
    in.get();
    for(int i=0;i<nrsup;i++){
        string supr;
        while (true) {
            try {
                getline(in, supr);
                if (supr=="marmura") {
                    throw "\nDezinfectantul antifungic nu se aplica pe marmura, citeste alta suprafata.\n";
                }
                break;
            } catch (const char* c) {
                cout << c;
            }
        }
        suprafete.push_back(supr);
    }
}
void DezinfectantFungi::afisare(ostream& out) const {
    Dezinfectant::afisare(out);
}
istream& operator>>(istream& in, DezinfectantFungi& obj) {
    obj.citire(in);
    return in;
}
ostream& operator<<(ostream& out, const DezinfectantFungi& obj) {
    obj.afisare(out);
    return out;
}


class DezinfectantBacterii : virtual public Dezinfectant {
    const int TotalBacterii;
public:
    DezinfectantBacterii(int nrspecii, vector<string> ingrediente, vector<string> suprafete);
    ~DezinfectantBacterii();
    DezinfectantBacterii(const DezinfectantBacterii& obj);
    DezinfectantBacterii& operator=(const DezinfectantBacterii& obj);
    double Eficienta();
    void citire(istream&);
    void afisare(ostream&) const;
    friend istream& operator>>(istream& in, DezinfectantBacterii& obj);
    friend ostream& operator<<(ostream& out, const DezinfectantBacterii& obj);
};

DezinfectantBacterii::DezinfectantBacterii(int nrspecii=0, vector<string> ingrediente=vector<string>(),
                                           vector<string> suprafete=vector<string>()):
        Dezinfectant(nrspecii, ingrediente, suprafete), TotalBacterii(1000000000) {}
DezinfectantBacterii::~DezinfectantBacterii() {
}
DezinfectantBacterii::DezinfectantBacterii(const DezinfectantBacterii& obj): Dezinfectant(obj), TotalBacterii(1000000000){
}

DezinfectantBacterii& DezinfectantBacterii::operator=(const DezinfectantBacterii& obj) {
    if (this != &obj) {
        Dezinfectant::operator=(obj) ;
    }
    return *this;
}
double DezinfectantBacterii::Eficienta()
{
    double calcul;
    calcul=nrspecii/TotalBacterii;
    calcul=calcul*100;
    return calcul;
}
void DezinfectantBacterii::citire(istream& in) {
    Dezinfectant::citire(in);
    int nrsup;
    cout<<"Nr suprafete: ";
    in>>nrsup;
    cout<<"Enumerati-le: ";
    in.get();
    for(int i=0;i<nrsup;i++){
        string supr;
        getline(in, supr);
        suprafete.push_back(supr);
    }
}
void DezinfectantBacterii::afisare(ostream& out) const {
    Dezinfectant::afisare(out);
}
istream& operator>>(istream& in, DezinfectantBacterii& obj) {
    obj.citire(in);
    return in;
}
ostream& operator<<(ostream& out, const DezinfectantBacterii& obj) {
    obj.afisare(out);
    return out;
}

class Achizitie {
    static int nrach;
    int nrClient;
    string client;
    int zia, lunaa, ana;
    vector<Dezinfectant*> dezachizitie;
    vector<Masca*> mastiachizitie;
    int total;
public:
    Achizitie(const string &client, int zia, int lunaa, int ana);
    virtual ~Achizitie();
    const string &getClient() const;
    void setClient(const string &client);
    int getZia() const;
    void setZia(int zia);
    int getLunaa() const;
    void setLunaa(int lunaa);
    int getAna() const;
    void setAna(int ana);

    int getTotal() const;

    void setTotal(int total);
    Achizitie(const Achizitie& obj);
    Achizitie& operator=(const Achizitie& obj);
    virtual void citire(istream&);
    virtual void afisare(ostream&) const;
    friend istream& operator>>(istream& in, Achizitie& obj);
    friend ostream& operator<<(ostream& out, const Achizitie& obj);
    Achizitie& operator+=(Masca* masca);
    int getNrClient() const;
    string nume();
    bool operator<(const Achizitie &obj) const;
    bool operator>(const Achizitie &obj) const;
    bool operator==(const Achizitie &rhs) const;
    bool operator!=(const Achizitie &rhs) const;
};
int Achizitie::nrach=0;
Achizitie::Achizitie(const string &client="", int zia=0, int lunaa=0, int ana=0) : client(client), zia(zia), lunaa(lunaa),
                                                                                   ana(ana) {}
Achizitie::~Achizitie() {
    client="";
    zia=0;
    lunaa=0;
    ana=0;
    total=0;
    for(unsigned int i=0;i<dezachizitie.size();i++)
        delete dezachizitie[i];
    dezachizitie.clear();
    for(unsigned int i=0;i<mastiachizitie.size();i++)
        delete mastiachizitie[i];
    mastiachizitie.clear();
}

Achizitie::Achizitie(const Achizitie& obj) {
    this->client = obj.client;
    this->zia=obj.zia;
    this->lunaa=obj.lunaa;
    this->ana=obj.ana;
    for(unsigned int i=0;i<obj.dezachizitie.size();i++)
        this->dezachizitie.push_back(obj.dezachizitie[i]);
    for(unsigned int i=0;i<mastiachizitie.size();i++)
        this->mastiachizitie.push_back(obj.mastiachizitie[i]);
    this->total=obj.total;
}

Achizitie& Achizitie::operator=(const Achizitie& obj) {
    if (this != &obj) {
        this->client = obj.client;
        this->zia=obj.zia;
        this->lunaa=obj.lunaa;
        this->ana=obj.ana;
        for(unsigned int i=0;i<obj.dezachizitie.size();i++)
            this->dezachizitie.push_back(obj.dezachizitie[i]);
        for(unsigned int i=0;i<mastiachizitie.size();i++)
            this->mastiachizitie.push_back(obj.mastiachizitie[i]);
        this->total=obj.total;
    }
    return *this;
}
const string &Achizitie::getClient() const {
    return client;
}
void Achizitie::setClient(const string &client) {
    this->client = client;
}
int Achizitie::getZia() const {
    return zia;
}
void Achizitie::setZia(int zia) {
    this->zia = zia;
}
int Achizitie::getLunaa() const {
    return lunaa;
}
void Achizitie::setLunaa(int lunaa) {
    this->lunaa = lunaa;
}
int Achizitie::getAna() const {
    return ana;
}
void Achizitie::setAna(int ana) {
    this->ana = ana;
}
int Achizitie::getTotal() const {
    return total;
}

int Achizitie::getNrClient() const {
    return nrClient;
}

void Achizitie::citire(istream& in) {
    int nrdez, nrmas;
    nrClient=++nrach;
    cout << "\nNume client: ";
    getline(in, client);
    cout<<"Zi achizitie: ";
    in>>zia;
    cout<<"Luna achizitie: ";
    in>>lunaa;
    cout<<"An achizitie: ";
    in>>ana;
    cout<<"Nr. dezinfectanti: ";
    in>>nrdez;
    for(int i=0;i<nrdez;i++){
        string tip;
        cout<<"Tip dezinfectant(antibacterian,antifungic,antivirus): ";
        getline(in, tip);
        if(tip=="antibacterian"){
            Dezinfectant* p = new DezinfectantBacterii;
            cin >> *p;
            if(p->Eficienta()<90) total+=10;
            else if(p->Eficienta()<95) total+=20;
            else if(p->Eficienta()<97.5) total+=30;
            else if(p->Eficienta()<99) total+=40;
            else total+=50;
            dezachizitie.push_back(p);
        }
        else if(tip=="antifungic"){
            Dezinfectant* p = new DezinfectantFungi;
            cin >> *p;
            if(p->Eficienta()<90) total+=10;
            else if(p->Eficienta()<95) total+=20;
            else if(p->Eficienta()<97.5) total+=30;
            else if(p->Eficienta()<99) total+=40;
            else total+=50;
            dezachizitie.push_back(p);
        }
        else if(tip=="antivirus"){
            Dezinfectant* p = new DezinfectantFungi;
            cin >> *p;
            if(p->Eficienta()<90) total+=10;
            else if(p->Eficienta()<95) total+=20;
            else if(p->Eficienta()<97.5) total+=30;
            else if(p->Eficienta()<99) total+=40;
            else total+=50;
            dezachizitie.push_back(p);
        }
    }
    cout<<"\nNr. masti: ";
    in>>nrmas;
    for(int i=0;i<nrmas;i++){
        string tip;
        cout<<"Tip masca(chirurgicala/policarbonat): ";
        getline(in, tip);
        if(tip=="chirurgicala"){
            Masca* p = new MascaChirurgicala;
            cin >> *p;
            if(p->getTipprot()=="ffp1") total+=5;
            else if(p->getTipprot()=="ffp2") total+=10;
            else if(p->getTipprot()=="ffp3") total+=15;
            mastiachizitie.push_back(p);
        }
        else if(tip=="policarbonat"){
            Masca* p = new MascaPolicarbonat;
            cin >> *p;
            total+=20;
            mastiachizitie.push_back(p);
        }
    }
}
void Achizitie::afisare(ostream& out) const {
    out << "\nClient: "<<client<<", achizitia a fost facuta la data "<<zia<<'.'<<lunaa<<'.'<<ana;
    out<<"\nS-au achizitionat "<<dezachizitie.size()<<" dezinfectanti: ";
    for(unsigned int i=0;i<dezachizitie.size();i++)
        out<<*dezachizitie[i];
    out<<"\nS-au achizitionat "<<mastiachizitie.size()<<" masti: ";
    for(unsigned int i=0;i<mastiachizitie.size();i++)
        out<<*mastiachizitie[i];
}
istream& operator>>(istream& in, Achizitie& obj) {
    obj.citire(in);
    return in;
}
ostream& operator<<(ostream& out, const Achizitie& obj) {
    obj.afisare(out);
    return out;
}

Achizitie &Achizitie::operator+=(Masca *masca) {
    mastiachizitie.push_back(masca);
    return *this;
}
string Achizitie::nume()
{
    return client;
}
bool Achizitie::operator==(const Achizitie &obj) const {
    return total == obj.total;
}
bool Achizitie::operator<(const Achizitie &obj) const {
    return total < obj.total;
}
bool Achizitie::operator>(const Achizitie &obj) const {
    return total > obj.total;
}
bool Achizitie::operator!=(const Achizitie &obj) const {
    return !(obj == *this);
}


///----------------------------clasa PRODUCATOR-SINGLETON----------------------------

class Producator { //SINGLETON
private:
    string numeProducator;
    static Producator* instance;
    Producator(string = "");
    vector<Masca*> masti;
    vector<Dezinfectant*> dezinfectanti;
    vector<Achizitie*> achizitii;
public:
    static Producator* getInstance(string);
    Producator(const Producator& obj);
    ~Producator();
    void menu_output();
    void adaugaMasca();
    void adaugaDezinfectant();
    void adaugaAchizitie();
    void afiseazaDezinfectanti();
    void afiseazaMasca();
    void afiseazaAchizitii();
    void afiseazaDezEficient();
    void calculVenitLuna();
    void calculVenitMasca();
    void modificaReteta();
    void clientFidel();
    void ziSlaba();
    void TVA();
    void afiseazaPacienti();
    Producator& operator=(Producator& obj);

};
Producator* Producator::instance = NULL;

Producator::Producator(string numeProducator): numeProducator(numeProducator) {}

Producator* Producator::getInstance(string numeProducator) {
    if(instance == NULL) {
        instance = new Producator(numeProducator);
    }
    return instance;
}
Producator::Producator(const Producator& obj) {
    this->numeProducator= obj.numeProducator;
    for(unsigned int i=0; i<masti.size(); i++)
        this->masti.push_back(obj.masti[i]);
    for(unsigned int i=0; i<dezinfectanti.size(); i++)
        this->dezinfectanti.push_back(obj.dezinfectanti[i]);
    for(unsigned int i=0; i<achizitii.size(); i++)
        this->achizitii.push_back(obj.achizitii[i]);
}

Producator::~Producator() {
    numeProducator="";
    for(unsigned int i=0; i<masti.size(); i++)
        delete masti[i];
    masti.clear();
    for(unsigned int i=0; i<dezinfectanti.size(); i++)
        delete dezinfectanti[i];
    dezinfectanti.clear();
    for(unsigned int i=0; i<achizitii.size(); i++)
        delete achizitii[i];
    achizitii.clear();
}

void Producator::menu_output() {
    cout << "\nPRODUCATOR\n";
    cout << "Producator: " << this->numeProducator << "\n";
    cout << "\n\t\tMENIU:";
    cout << "\n===============================================\n";
    cout << "\n1. Citeste dezinfectant";
    cout << "\n2. Citeste masca";
    cout << "\n3. Citeste achizitie";
    cout << "\n4. Afiseaza dezinfectanti";
    cout << "\n5. Afiseaza masti";
    cout << "\n6. Afiseaza achizitii";
    cout << "\n7. Afiseaza dezinfectant eficient";
    cout << "\n8. Calculeaza venit intr-o luna";
    cout << "\n9. Calculeaza venit masti chirurgicale cu model";
    cout << "\n10. Modifica reteta";
    cout << "\n11. Afiseaza client fidel";
    cout << "\n12. Afiseaza zi cu venit slab";
    cout << "\n13. Calculeaza TVA";
    cout << "\n0. Iesire.";
    cout << "\n";
}

void Producator::adaugaDezinfectant() {
    string tip;
    cout<<"Tip dezinfectant(antibacterian,antifungic,antivirus): ";
    getline(cin, tip);
    try {
        if (tip == "antibacterian") {
            Dezinfectant *p = new DezinfectantBacterii;
            cin >> *p;
            p->Eficienta();
            dezinfectanti.push_back(p);
        } else if (tip == "antifungic") {
            Dezinfectant *p = new DezinfectantFungi;
            cin >> *p;
            p->Eficienta();
            dezinfectanti.push_back(p);
        } else if (tip == "antivirus") {
            Dezinfectant *p = new DezinfectantFungi;
            cin >> *p;
            p->Eficienta();
            dezinfectanti.push_back(p);
        } else
            throw 10;
    }
    catch (bad_alloc var) {
        cout << "Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
}

void Producator::adaugaMasca() {
    string tip;
    cout<<"Tip masca(chirurgicala/policarbonat): ";
    getline(cin, tip);
    try {
        if (tip == "chirurgicala") {
            Masca *p = new MascaChirurgicala;
            cin >> *p;
            masti.push_back(p);
        } else if (tip == "policarbonat") {
            Masca *p = new MascaPolicarbonat;
            cin >> *p;
            masti.push_back(p);
        } else
            throw 10;
    }
    catch (bad_alloc var) {
        cout << "Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
}

void Producator::adaugaAchizitie() {
    Achizitie* ach;
    cin>>*ach;
    achizitii.push_back(ach);
}

void Producator::afiseazaDezinfectanti() {
    cout<<"Dezinfectanti in stoc: "<<dezinfectanti.size();
    cout<<"\nDezinfectanti antibacterieni: ";
    for(unsigned int i=0; i<dezinfectanti.size(); i++) {
        DezinfectantBacterii* p=dynamic_cast<DezinfectantBacterii*>(dezinfectanti[i]);
        if(p)
            cout<<*dezinfectanti[i];
    }
    cout<<"\nDezinfectanti antifungici: ";
    for(unsigned int i=0; i<dezinfectanti.size(); i++) {
        DezinfectantFungi* p=dynamic_cast<DezinfectantFungi*>(dezinfectanti[i]);
        if(p)
            cout<<*dezinfectanti[i];
    }
    cout<<"\nDezinfectanti antivirusuri: ";
    for(unsigned int i=0; i<dezinfectanti.size(); i++) {
        DezinfectantVirusi* p=dynamic_cast<DezinfectantVirusi*>(dezinfectanti[i]);
        if(p)
            cout<<*dezinfectanti[i];
    }
}

void Producator::afiseazaMasca() {
    cout<<"Masti in stoc: "<<masti.size()<<'\n';
    for(unsigned int i=0;i<masti.size();i++)
        cout<<*masti[i];
}

void Producator::afiseazaAchizitii() {
    cout<<"Achizitii: "<<achizitii.size()<<'\n';
    for(unsigned int i=0;i<achizitii.size();i++)
        cout<<*achizitii[i];
}

void Producator::afiseazaDezEficient() {
    double maxef=0;
    int poz;
    for(unsigned int i=0;i<dezinfectanti.size();i++){
        if(dezinfectanti[i]->Eficienta()>maxef){
            maxef=dezinfectanti[i]->Eficienta();
            poz=i;
        }
    }
    cout<<"Dezinfectantul cel mai eficient are eficienta: "<<maxef<<" si este: ";
    cout<<*dezinfectanti[poz];
}

void Producator::calculVenitLuna() {
    cout<<"Luna de calculat venit: ";
    double venit=0;
    int luna;
    cin>>luna;
    for(unsigned int i=0;i<achizitii.size();i++){
        if(achizitii[i]->getLunaa()==luna)
            venit+=achizitii[i]->getTotal();
    }
    cout<<"Venit pe luna respectiva: "<<venit;
}

void Producator::calculVenitMasca() {

}

void Producator::modificaReteta()
{

}

void Producator::clientFidel()
{

}

void Producator::ziSlaba() {

}

void Producator::TVA() {
    double TVA=0;
    cout<<"An: ";
    int an;
    cin>>an;
    for(unsigned int i=0;i<achizitii.size();i++) {
        if (achizitii[i]->getAna() == an)
            TVA += achizitii[i]->getTotal();
    }
    TVA=0.19*TVA;
    cout<<"TVA: "<<TVA;

}


Producator& Producator::operator=(Producator& obj) {
    if (this != &obj) {
        this->numeProducator= obj.numeProducator;
        for(unsigned int i=0; i<masti.size(); i++)
            this->masti.push_back(obj.masti[i]);
        for(unsigned int i=0; i<dezinfectanti.size(); i++)
            this->dezinfectanti.push_back(obj.dezinfectanti[i]);
        for(unsigned int i=0; i<achizitii.size(); i++)
            this->achizitii.push_back(obj.achizitii[i]);
    }
    return *this;
}


///------------------------------MENIU-----------------------------

void menu() {
    int option;
    option = 0;
    Producator *P = P->getInstance("Compania X");
    do {
        P->menu_output();
        cout << "\nIntroduceti numarul actiunii: ";
        cin >> option;
        if(option == 1) {
            P->adaugaDezinfectant();
        }
        else if(option == 2) {
            P->adaugaMasca();
        }
        else if(option == 3) {
            P->adaugaAchizitie();
        }
        else if(option == 4) {
            P->afiseazaDezinfectanti();
        }
        else if(option == 5) {
            P->afiseazaMasca();
        }
        else if(option == 6) {
            P->afiseazaAchizitii();
        }
        else if(option == 7) {
            P->afiseazaDezEficient();
        }
        else if(option == 8) {
            P->calculVenitLuna();
        }
        else if(option == 9) {
            P->calculVenitMasca();
        }
        else if(option == 10) {
            P->modificaReteta();
        }
        else if(option == 11) {
            P->clientFidel();
        }
        else if(option == 12) {
            P->ziSlaba();
        }
        else if(option == 13) {
            P->TVA();
        }
        else if (option == 0) {
            cout << "\nEXIT!\n";
        }
        if (option < 0 || option>13) {
            cout << "\nSelectie invalida\n";
        }
        cout << '\n';
        system("pause");
        system("cls");
    }
    while (option != 0);
}
int main() {
    menu();
    return 0;
}
