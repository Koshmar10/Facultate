#include<iostream>
#include <vector>
using namespace std;

class Masca{
    protected: 
    string tip_protectie;
    public:
    Masca(string tp= "") : tip_protectie(tp){};
    virtual ~Masca(){};
    Masca(const Masca& m) : tip_protectie(m.tip_protectie){};

    virtual double cost() = 0;
    
};

class MascaChirurgicala : public Masca{
    string culoare;
    int nr_pliuri;
    bool model;
    public: 
    MascaChirurgicala(string tp ="", string cul = "", int nrp = 0, bool m = false )
    : Masca(tp), culoare(cul), nr_pliuri(nrp), model(m){};
    MascaChirurgicala(const MascaChirurgicala& o): Masca(o), nr_pliuri(o.nr_pliuri), culoare(o.culoare), model(o.model){};
    ~MascaChirurgicala(){};
    
    double cost(){
        double cost = 0;
        if (this->tip_protectie == "ffp1") 
            cost = 5;
        if (this->tip_protectie == "ffp2") 
            cost = 10;
        if (this->tip_protectie == "ffp3") 
            cost = 15;
        if (model)
            cost += cost * 0.5;
        return cost;
        
    }
    bool get_model() const{ return model;}
    friend istream& operator>>(istream& in, MascaChirurgicala& m){
        cout<<"\nTip protectie: "; in>>m.tip_protectie;
        cout<<"\nCuloare: "; in>>m.culoare;
        cout<<"\nNumar Pliuri: "; in>>m.nr_pliuri;
        string opt;
        cout<<"Model(da/nu): "; in>>opt;
        if (opt== "da"){m.model =true;}
        else m.model = false;
        
    }
};
class MascaPolicarbonat : public Masca{
    string tip_prindere;
    public:
    MascaPolicarbonat(string tip_prindere="")
    : Masca("ffp0"), tip_prindere(tip_prindere){};
    MascaPolicarbonat(const MascaPolicarbonat& o): Masca(o), tip_prindere(o.tip_prindere){};
    ~MascaPolicarbonat(){};
    double cost() {
        return 20;
    }

    friend istream& operator>>(istream& in, MascaPolicarbonat& m){
        cout<<"\nTip Prindere: "; in>>m.tip_prindere;
        
    }
};
class Dezinfectant{
    protected:
        vector<string> ingrediente;
        vector<string> suprafete;
    public:
    Dezinfectant(int i = {}, int s = {}) : ingrediente(i), suprafete(i){};
    Dezinfectant(const Dezinfectant& d): ingrediente(d.ingrediente), suprafete(d.suprafete){};
    virtual ~Dezinfectant(){};
    virtual double eficienta() =0;
    int cost() {
        double eff = eficienta(); 
        if (eff < 90.0) return 10;
        if (eff < 95.0) return 20;
        if (eff < 97.5) return 30;
        if (eff < 99.0) return 40;
        if (eff < 99.99) return 50;
    }
    
};
class DezinfectantAntiBacterian: public Dezinfectant{
    long nr_bacterii;
    public:
    DezinfectantAntiBacterian(long nr_bacterii= 0, int i = {}, int s = {}) :Dezinfectant(i, s), nr_bacterii(nr_bacterii){};
    DezinfectantAntiBacterian(const DezinfectantAntiBacterian& d): Dezinfectant(d), nr_bacterii(d.nr_bacterii){};
    ~DezinfectantAntiBacterian(){};
    double eficienta() {
        long total = 1;
        for (int i =0; i<9; i++){total*=10;}      
        return this->nr_bacterii / total;
    }
    friend istream& operator>>(istream& in, DezinfectantAntiBacterian& d){
        cout<<"\nIngrediente(scrie gata cand termini):\n";
        string ing ="";
        while (ing != "gata")
        {
            in>>ing;
            d.ingrediente.push_back(ing);
        }
        cout<<"\nSuprafete aplicabile(scrie gata cand termini):\n";
        ing ="";
        while (ing != "gata")
        {
            in>>ing;
            d.suprafete.push_back(ing);
        }
        cout<<"\nnr bacterii ucisi: "; in>>d.nr_bacterii;
    }

};
class DezinfectantAnitFungic : public Dezinfectant{
    long nr_fungi;
    public:
    DezinfectantAnitFungic(long nr_fungi= 0, int i = {}, int s = {}) :Dezinfectant(i, s), nr_fungi(nr_fungi){};
    DezinfectantAnitFungic(const DezinfectantAnitFungic& d): Dezinfectant(d), nr_fungi(d.nr_fungi){};
    ~DezinfectantAnitFungic(){};
    double eficienta() {
        double total = 1.5;
        for (int i =0; i<6; i++){total*=10;}      
        return (double)this->nr_fungi / total;
    }
    friend istream& operator>>(istream& in, DezinfectantAnitFungic& d){
        cout<<"\nIngrediente(scrie gata cand termini):\n";
        string ing ="";
        while (ing != "gata")
        {
            in>>ing;
            d.ingrediente.push_back(ing);
        }
        cout<<"\nSuprafete aplicabile(scrie gata cand termini):\n";
        ing ="";
        while (ing != "gata")
        {
            in>>ing;
            d.suprafete.push_back(ing);
        }
        cout<<"\nnr fungi ucisi: "; in>>d.nr_fungi;
    }
};

class DezinfectantAntiVirusi: public Dezinfectant{
    long nr_virusuri;
    public:
    DezinfectantAntiVirusi(long nr_virusuri= 0, int i = {}, int s = {}) :Dezinfectant(i, s), nr_virusuri(nr_virusuri){};
    DezinfectantAntiVirusi(const DezinfectantAntiVirusi& d): Dezinfectant(d), nr_virusuri(d.nr_virusuri){};
    ~DezinfectantAntiVirusi(){};
    double eficienta() {
        long total = 1;
        for (int i =0; i<8; i++){total*=10;}      
        return this->nr_virusuri / total;
    }
    friend istream& operator>>(istream& in, DezinfectantAntiVirusi& d){
        cout<<"\nIngrediente(scrie gata cand termini):\n";
        string ing ="";
        while (ing != "gata")
        {
            in>>ing;
            d.ingrediente.push_back(ing);
        }
        cout<<"\nSuprafete aplicabile(scrie gata cand termini):\n";
        ing ="";
        while (ing != "gata")
        {
            in>>ing;
            d.suprafete.push_back(ing);
        }
        cout<<"\nnr virusuri ucise: "; in>>d.nr_virusuri;
    }
};
class Achizitie{
    string data;
    string nume_client;
    vector<Masca*> masti;
    vector<Dezinfectant*> dezinfectanti;
    float cost;
    public:
    Achizitie(string d="", string nume="", vector<Masca*> m ={}, vector<Dezinfectant*> dez = {})
    :data(d), nume_client(nume), masti(m), dezinfectanti(dez){
        this->cost =0;
        for (auto& m : this->masti){
            cost+=m->cost();
        }
        for (auto& d : this->dezinfectanti){
            cost+=d->cost();
        }
    };
    Achizitie(const Achizitie&  o) : data(o.data), nume_client(o.nume_client){
        this->masti = {};
        this->dezinfectanti = {};
        for (auto& m : o.masti) {
            if (auto* chirurgicala = dynamic_cast<MascaChirurgicala*>(m)) {
            this->masti.push_back(new MascaChirurgicala(*chirurgicala));
            } else if (auto* policarbonat = dynamic_cast<MascaPolicarbonat*>(m)) {
            this->masti.push_back(new MascaPolicarbonat(*policarbonat));
            }
        }
        for (auto& d : o.dezinfectanti) {
            if (auto* antibacterian = dynamic_cast<DezinfectantAntiBacterian*>(d)) {
            this->dezinfectanti.push_back(new DezinfectantAntiBacterian(*antibacterian));
            } else if (auto* antifungic = dynamic_cast<DezinfectantAnitFungic*>(d)) {
            this->dezinfectanti.push_back(new DezinfectantAnitFungic(*antifungic));
            } else if (auto* antivirus = dynamic_cast<DezinfectantAntiVirusi*>(d)) {
            this->dezinfectanti.push_back(new DezinfectantAntiVirusi(*antivirus));
            }
        }
    }
    ~Achizitie(){
        for(auto& masca : masti){
            if (masca)
            delete masca;
        }
        masti.clear();
        for(auto& dezinfectant : dezinfectanti){
            if (dezinfectant)
            delete dezinfectant;
        }
        dezinfectanti.clear();
    }
    string get_nume() const {return nume_client;}
    string get_data() const {return data;}
    vector<Masca*> get_masti() const {return masti;}
    vector<Dezinfectant*> get_dezinfectanti() const {return dezinfectanti;}
    void adauga_masca(){
        string opt;
        cout<<"\nTip masca : "; cin>>opt;
        if (opt == "textila"){
            MascaChirurgicala m;
            cin>>m;
            this->masti.push_back(new MascaChirurgicala(m));
        }
        else{
            MascaPolicarbonat m;
            cin>>m;
            this->masti.push_back(new MascaPolicarbonat(m));
        }
    }
    void adauga_dezinfectant() {
        string opt;
        cout<<"\nTip dezinfectant(anti-bacterian/fungic/virusuri): "; cin>> opt;
        if (opt == "anti-bacterian"){
            DezinfectantAntiBacterian d;
            cin>>d;
            dezinfectanti.push_back(new DezinfectantAntiBacterian(d));
        }
        else if(opt == "anti-fungic"){
            DezinfectantAnitFungic d;
            cin>>d;
            dezinfectanti.push_back(new DezinfectantAnitFungic(d));
        }
        else{
            DezinfectantAntiVirusi d;
            cin>>d;
            dezinfectanti.push_back(new DezinfectantAntiVirusi(d));
        }
    }

    friend istream& operator>>(istream& in, Achizitie& a){
        cout<<"\nDaata Achizitie: "; in>>a.data;
        cout<<"\nNume client: "; in>>a.nume_client;
        int nr_masti, nr_dezinfectante;
        cout<<"\nCate masti au fost achizitionate: "; in>>nr_masti;
        cout<<"\nCate masti au fost achizitionate: "; in>>nr_dezinfectante;
        for (int i=0; i < nr_masti; i++){
            a.adauga_masca();
        } 
        for (int i =0; i < nr_dezinfectante; i++){
            a.adauga_dezinfectant();
        } 
    }

};
class Arhiva{
    private:
    static int next_id;
    vector<Achizitie*> achizitii;
    vector<Masca*> masti;
    vector<Dezinfectant*> dezinfectanti;
    public:
    Arhiva(vector<Achizitie*> a ={}):achizitii(a){};
    ~Arhiva(){
        for(auto& a : achizitii){
            if (a)
            delete a;
        }
        achizitii.clear();
        for(auto& m : masti){
            if (m)
            delete m;
        }
        masti.clear();
        for(auto& d : dezinfectanti){
            if (d)
            delete d;
        }
        dezinfectanti.clear();
        
    }
    void adauga_masca(){
        string opt;
        cout<<"\nTip masca : "; cin>>opt;
        if (opt == "textila"){
            MascaChirurgicala m;
            cin>>m;
            this->masti.push_back(new MascaChirurgicala(m));
        }
        else{
            MascaPolicarbonat m;
            cin>>m;
            this->masti.push_back(new MascaPolicarbonat(m));
        }
    }
    void adauga_dezinfectant() {
        string opt;
        cout<<"\nTip dezinfectant(anti-bacterian/fungic/virusuri): "; cin>> opt;
        if (opt == "anti-bacterian"){
            DezinfectantAntiBacterian d;
            cin>>d;
            dezinfectanti.push_back(new DezinfectantAntiBacterian(d));
        }
        else if(opt == "anti-fungic"){
            DezinfectantAnitFungic d;
            cin>>d;
            dezinfectanti.push_back(new DezinfectantAnitFungic(d));
        }
        else{
            DezinfectantAntiVirusi d;
            cin>>d;
            dezinfectanti.push_back(new DezinfectantAntiVirusi(d));
        }
    }
    void adauga_achizitie(){
        Achizitie a;
        cin>>a;
        achizitii.push_back(new Achizitie(a));
    }
    void best_dezinfectant(){
        Dezinfectant* best;
        double max_eff = 0;
        for(auto& d : dezinfectanti){
            if (d->eficienta() > max_eff){
                max_eff = d->eficienta();
                best = d;
            }

        }
        cout<<best;
    }
    void venit_masti_model(){
        double cost=0;
        for (auto& achizitie: achizitii){
            for(auto& m : achizitie->get_masti()){
                if (auto aux =dynamic_cast<MascaChirurgicala*>(m)){
                    if (aux->get_model()){
                        cost+=aux->cost();
                    }
                }
            }
        }
    }

    

};
int Arhiva::next_id = 0;
int main()
{
    int input;
    Arhiva arhiva = Arhiva();
    while (input!=-1){
        cout<<"\n1. Adaugă un nou dezinfectant în stoc\n2. Adaugă o nouă mască în stoc\n3. Adaugă o nouă achiziție\n4. Afișează dezinfectantul cel mai eficient\n5. Calculează venitul dintr-o anumită lună\n6. Calculează venitul obținut din măștile chirurgicale cu model.\n7. Modifică rețeta \n9. Afișează ziua cu cele mai slabe venituri, de la deschidere până în prezent\n";
        cin>>input;
        if (input == 1){
            arhiva.adauga_dezinfectant();
        }
        if (input == 2){
            arhiva.adauga_masca();
        }
        if (input == 3){
            arhiva.adauga_achizitie();
        }
    }
    return 0;
}