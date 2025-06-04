#include<iostream>
#include<string>
#include <vector>
#include <fstream>
struct Comanda{
    protected: 
    int id;
    std::string nume_client;
    std::string adresa_client;
    float pret_final;
    float timp_livrare;
    //produsul este asociad cantitati cu acelasi index
    std::vector<std::string> denumire_produse;
    std::vector<std::string> cantitate_produs;
    public:
    
    Comanda(int id=-1, std::string nc="", std::string ac="", float pf=0, float tl=0, std::vector<std::string> dp = {}, std::vector<std::string> cp = {}) 
    :id(id), nume_client(nc), adresa_client(ac), pret_final(pf), timp_livrare(tl), denumire_produse(dp), cantitate_produs(cp){};
    
    Comanda(const Comanda& other):id(other.id), nume_client(other.nume_client), adresa_client(other.adresa_client), pret_final(other.pret_final), timp_livrare(other.timp_livrare), denumire_produse(other.denumire_produse), cantitate_produs(other.cantitate_produs){};
    virtual ~Comanda(){};

    std::vector<std::string> get_prduse() const {return denumire_produse; }
    int get_id() const {return id;}
    std::string get_nume_client() const {return nume_client;}

    // Virtual print method for polymorphic display
    virtual void print(std::ostream& out) const {
        out << "ID: " << id; // Basic info, derived classes will add more
        out << "\nNume Client: " << nume_client;
        out << "\nAdresa Client: " << adresa_client;
        out << "\nTimp livrare: " << timp_livrare;
        out << "\nProduse : ";
        if (denumire_produse.empty()) {
            out << "N/A";
        } else {
            for(size_t i = 0; i < denumire_produse.size(); ++i){
                out << denumire_produse[i] << "->" << cantitate_produs[i] << (i == denumire_produse.size() - 1 ? "" : ", ");
            }
        }
        out << "\nPret Final: " << pret_final;
        // Derived classes should call this and add their specific info, or reimplement fully.
        // For simplicity here, each derived class will handle its full output format.
    }

    void read_base(std::istream& in){
        std::cout<<"\nNume Client: "; in>> nume_client;
        std::cout<<"\nAdresa Client: "; in>>adresa_client;
        int nr_produse;
        std::cout<<"\nNumar Produse: "; in>>nr_produse;
        denumire_produse.clear(); // Clear previous products
        cantitate_produs.clear(); // Clear previous quantities
        for (int i=0; i<nr_produse; i++){
            std::string produs_item; // Use a different name to avoid shadowing
            std::string cant_item_str;
            std::cout<<"\n Denumire: "; in>>produs_item;
            std::cout<<" Cantitate: "; in>>cant_item_str; // Read as string, assuming cantitate_produs is vector<string>
            denumire_produse.push_back(produs_item);
            cantitate_produs.push_back(cant_item_str);
        }
        std::cout<<"\nPret FInal: "; in>>pret_final;
        std::cout<<"\nTimp livrare: "; in>>timp_livrare;
    }

    bool operator<(const Comanda& other){
        return pret_final < other.pret_final;
    }
};

// Global operator<< to enable polymorphic printing via virtual function
inline std::ostream& operator<<(std::ostream& out, const Comanda& c){
    c.print(out); // Calls the appropriate virtual print method
    return out;
}

class ComandaMancare : public Comanda{
    protected:
        std::string locatie;
    public:
    ComandaMancare(int id=-1, std::string nc="", std::string ac="", float pf=0, float tl=0, std::vector<std::string> dp = {}, std::vector<std::string> cp = {}, std::string locatie="") 
    :Comanda(id, nc, ac, pf, tl,dp,cp), locatie(locatie){};
    
    ComandaMancare(const ComandaMancare& other): Comanda(other), locatie(other.locatie){};
    ~ComandaMancare(){};

    // Override print for ComandaMancare specific details
    void print(std::ostream& out) const override {
        // This is a base for FastFood and Restaurant, so it might not be directly printed often.
        // If it is, it should have its own complete format.
        // For now, assume derived FastFood/Restaurant will provide full output.
        // If ComandaMancare objects are directly stored and printed, this needs full formatting.
        Comanda::print(out); // Example: call base and add specific
        out << "\nLocal: " << locatie;
    }

    friend std::istream& operator>>(std::istream& in , ComandaMancare& c){
        c.read_base(in);
        std::cout<<"\nLocatie: "; in>>c.locatie;
        return in;
    }
};
class ComandaFastFood : public ComandaMancare{
    private:
    //scat la suta se reduce din comanda
    float discount;
    public:
    ComandaFastFood(int id=-1, std::string nc="", std::string ac="", float pf=0, float tl=0, std::vector<std::string> dp = {}, std::vector<std::string> cp = {}, std::string locatie="", float disc = 0) 
    :ComandaMancare(id, nc, ac, pf, tl,dp,cp, locatie), discount(disc){};
    
    ComandaFastFood(const ComandaFastFood& other): ComandaMancare(other), discount(other.discount){};
    ~ComandaFastFood(){};

    // Override print method
    void print(std::ostream& out) const override {
        out << "Comanda mancare, fast food, " << "ID" << get_id();
        out << "\nNume Client: " << nume_client;
        out << "\nAdresa Client: " << adresa_client;
        out << "\nLocal: " << locatie;
        out << "\nTimp livrare: " << timp_livrare;
        out << "\nProduse : ";
        if (denumire_produse.empty()) {
            out << "N/A";
        } else {
            for(size_t i = 0; i < denumire_produse.size(); ++i){
                out << denumire_produse[i] << "->" << cantitate_produs[i] << (i == denumire_produse.size() - 1 ? "" : ", ");
            }
        }
        out << "\nDiscont: " << discount << " lei"; // Assuming discount is a fixed amount in lei
        out << "\nPret FInal: " << pret_final << std::endl;
    }

    friend std::istream& operator>>(std::istream& in , ComandaFastFood& c){
        c.read_base(in);
        std::cout<<"\nLocatie: "; in>>c.locatie;
        std::cout<<"\nDiscount: "; in>>c.discount;
        return in;
    }
};
class ComandaRestaurant : public ComandaMancare{
    private:
    bool tacamuri;
    public:
    ComandaRestaurant(int id=-1, std::string nc="", std::string ac="", float pf=0, float tl=0, std::vector<std::string> dp = {}, std::vector<std::string> cp = {}, std::string locatie="", bool tacamuri = false) 
    :ComandaMancare(id, nc, ac, pf, tl,dp,cp, locatie), tacamuri(tacamuri){};
    
    ComandaRestaurant(const ComandaRestaurant& other): ComandaMancare(other), tacamuri(other.tacamuri){};
    ~ComandaRestaurant(){};

    // Override print method
    void print(std::ostream& out) const override {
        out << "Comanda mancare, restaurant, " << "ID" << get_id();
        out << "\nNume Client: " << nume_client;
        out << "\nAdresa Client: " << adresa_client;
        out << "\nLocal: " << locatie;
        out << "\nTimp livrare: " << timp_livrare;
        out << "\nProduse : ";
        if (denumire_produse.empty()) {
            out << "N/A";
        } else {
            for(size_t i = 0; i < denumire_produse.size(); ++i){
                 out << denumire_produse[i] << "->" << cantitate_produs[i] << (i == denumire_produse.size() - 1 ? "" : ", ");
            }
        }
        out << "\nTacamuri: " << (tacamuri ? "Da" : "Nu");
        out << "\nPret FInal: " << pret_final << std::endl;
    }

    friend std::istream& operator>>(std::istream& in , ComandaRestaurant& c){
        c.read_base(in);
        std::cout<<"\nLocatie: "; in>>c.locatie;
        std::string r;
        std::cout<<"\nTacamuri(y/n): "; in>>r;
        if (r =="y"){
            c.tacamuri = true;
        }else{
            c.tacamuri = false;
        }
        return in;
    }
};
class ComandaMedicamente: public Comanda{
    protected:
    std::vector<bool> antibiotice;
    public:
    ComandaMedicamente(int id=-1, std::string nc="", std::string ac="", float pf=0, float tl=0, std::vector<std::string> dp = {}, std::vector<std::string> cp = {}, std::vector<bool> anti={}) 
    :Comanda(id, nc, ac, pf, tl,dp,cp), antibiotice(anti){};
    
    ComandaMedicamente(const ComandaMedicamente& other): Comanda(other), antibiotice(other.antibiotice){};
    ~ComandaMedicamente(){};

    int nr_antibiotice() const {
        int nr=0;
        for (bool x : antibiotice){
            if (x)
            nr+=1;
        }
        return nr;
    }
    friend std::istream& operator>>(std::istream& in , ComandaMedicamente& c){
        c.read_base(in);
        for (std::string tig : c.get_prduse()){
            std::string r;
            std::cout<<"\n Medicamentele"<<tig<<" sunt antibiotice(y/n): "; in>>r;
            if (r == "y")
            c.antibiotice.push_back(true);
            else
            c.antibiotice.push_back(false);
        
        }
        return in;
    }
    // Override print method
    void print(std::ostream& out) const override {
        out << "Comanda medicamente, " << "ID" << get_id();
        out << "\nNume Client: " << nume_client;
        out << "\nAdresa Client: " << adresa_client;
        out << "\nTimp livrare: " << timp_livrare;
        out << "\nProduse : ";
        if (denumire_produse.empty()) {
            out << "N/A";
        } else {
            for(size_t i = 0; i < denumire_produse.size(); ++i){
                // Ensure antibiotice vector is correctly sized and populated during input
                bool is_antibiotic = (i < antibiotice.size()) ? antibiotice[i] : false;
                out << denumire_produse[i] << "(" << (is_antibiotic ? "Antibiotic" : "Non-Antibiotic") << ")"
                    << "->" << cantitate_produs[i] << (i == denumire_produse.size() - 1 ? "" : ", ");
            }
        }
        out << "\nPret FInal: " << pret_final << std::endl;
    }

    friend std::istream& operator>>(std::istream& in , ComandaMedicamente& c){
        c.read_base(in);
        for (std::string tig : c.get_prduse()){
            std::string r;
            std::cout<<"\n Medicamentele"<<tig<<" sunt antibiotice(y/n): "; in>>r;
            if (r == "y")
            c.antibiotice.push_back(true);
            else
            c.antibiotice.push_back(false);
        
        }
        return in;
    }
};
class ComandaTigari: public Comanda{
    protected:
    std::vector<bool> tigari_clasice;
    public:
    ComandaTigari(int id=-1, std::string nc="", std::string ac="", float pf=0, float tl=0, std::vector<std::string> dp = {}, std::vector<std::string> cp = {}, std::vector<bool> tig={}) 
    :Comanda(id, nc, ac, pf, tl,dp,cp), tigari_clasice(tig){};
    
    ComandaTigari(const ComandaTigari& other): Comanda(other), tigari_clasice(other.tigari_clasice){};
    ~ComandaTigari(){};

    // Override print method
    void print(std::ostream& out) const override {
        out << "Comanda tigari, " << "ID" << get_id();
        out << "\nNume Client: " << nume_client;
        out << "\nAdresa Client: " << adresa_client;
        out << "\nTimp livrare: " << timp_livrare;
        out << "\nProduse : ";
        if (denumire_produse.empty()) {
            out << "N/A";
        } else {
            for(size_t i = 0; i < denumire_produse.size(); ++i){
                 // Ensure tigari_clasice vector is correctly sized and populated during input
                bool is_classic = (i < tigari_clasice.size()) ? tigari_clasice[i] : false;
                out << denumire_produse[i] << "(" << (is_classic ? "Clasic" : "Non-Clasic") << ")"
                    << "->" << cantitate_produs[i] << (i == denumire_produse.size() - 1 ? "" : ", ");
            }
        }
        out << "\nPret FInal: " << pret_final << std::endl;
    }

    friend std::istream& operator>>(std::istream& in , ComandaTigari& c){
        c.read_base(in);
        for (std::string tig : c.get_prduse()){
            std::string r;
            std::cout<<"\n Tigariele "<<tig<<" Sunt clasice(y/n): "; in>>r;
            if (r == "y")
            c.tigari_clasice.push_back(true);
            else
            c.tigari_clasice.push_back(false);
        
        }
        return in;
    }
};

class ManagerComenzi{
    private:
    static ManagerComenzi* manager;
    static int nextId;
    std::vector<Comanda*> comenzi;
    ManagerComenzi(std::vector<Comanda*> c = {}) : comenzi(c){};
    ~ManagerComenzi() {
        for (Comanda*& c : comenzi){
            if (c)
                delete c;
        }
    }
    public:
    static ManagerComenzi* Instance(){
        if (manager){
            return manager;
        }
        else{
            manager = new ManagerComenzi;
            return manager;
        }
    }
    ManagerComenzi(const ManagerComenzi& other) = delete;
    ManagerComenzi& operator=(const ManagerComenzi&) = delete;
    //opereatiile pe comenzi
    void adaugare_comanda(){
        std::cout<<"\ntip comanda(mancare 1 medicamente 2 tigari 3): ";
        int x;    
        std::cin>>x;
            if (x==1){
                int y;
                std::cout<<"\nRestaurant 1 sau FastFood 2"; std::cin>>y;
                if (y==1){
                    ComandaRestaurant cmd = ComandaRestaurant(nextId++);
                    std::cin>>cmd;
                    comenzi.push_back(new ComandaRestaurant(cmd));
                }else if(y==2){
                    ComandaFastFood cmd = ComandaFastFood(nextId++);
                    std::cin>>cmd;
                    comenzi.push_back(new ComandaFastFood(cmd));
                }
            }else if(x==2){
                ComandaMedicamente cmd = ComandaMedicamente(nextId++);
                    std::cin>>cmd;
                comenzi.push_back(new ComandaMedicamente(cmd));
            }else if(x==3){
                ComandaTigari cmd = ComandaTigari(nextId++);
                    std::cin>>cmd;
                comenzi.push_back(new ComandaTigari(cmd));

            }
    }
    void citire_comenzi(){
        std::cout<<"\ncitire din fisier(2) sau consola(1): ";
        int x, nr;
        std::cin>>x;
        if (x == 1){
            std::cout<<"\nNUmar de fisiere de citit:"; std::cin>>nr;
            for(int i =0; i<nr; i++){
                Comanda* cmd;
                std::cout<<"\ntip comanda(mancare 1 medicamente 2 tigari 3): ";
                std::cin>>x;
                if (x==1){
                    int y;
                    std::cout<<"\nRestaurant 1 sau FastFood 2"; std::cin>>y;
                    if (y==1){
                        ComandaRestaurant cmd = ComandaRestaurant(nextId++);
                        std::cin>>cmd;
                        comenzi.push_back(new ComandaRestaurant(cmd));
                    }else if(y==2){
                        ComandaFastFood cmd = ComandaFastFood(nextId++);
                        std::cin>>cmd;
                        comenzi.push_back(new ComandaFastFood(cmd));
                    }
                }else if(x==2){
                    ComandaMedicamente cmd = ComandaMedicamente(nextId++);
                        std::cin>>cmd;
                    comenzi.push_back(new ComandaMedicamente(cmd));
                }else if(x==3){
                    ComandaTigari cmd = ComandaTigari(nextId++);
                        std::cin>>cmd;
                    comenzi.push_back(new ComandaTigari(cmd));

                }

            }
        }
        else if(x==2){
            std::string nume_fis;
            std::cout<<"\nNUmar de fisiere de citit:"; std::cin>>nr;
            std::cout<<"\nNumele fisierului:"; std::cin>>nume_fis;
            std::ifstream file(nume_fis);
            std::cout<<"\nNUmar de fisiere de citit:"; std::cin>>nr;
            for(int i =0; i<nr; i++){
                Comanda* cmd;
                std::cout<<"\ntip comanda(mancare 1 medicamente 2 tigari 3): ";
               file>>x;
                if (x==1){
                    int y;
                    std::cout<<"\nRestaurant 1 sau FastFood 2";file>>y;
                    if (y==1){
                        ComandaRestaurant cmd = ComandaRestaurant(nextId++);
                       file>>cmd;
                        comenzi.push_back(new ComandaRestaurant(cmd));
                    }else if(y==2){
                        ComandaFastFood cmd = ComandaFastFood(nextId++);
                       file>>cmd;
                        comenzi.push_back(new ComandaFastFood(cmd));
                    }
                }else if(x==2){
                    ComandaMedicamente cmd = ComandaMedicamente(nextId++);
                       file>>cmd;
                    comenzi.push_back(new ComandaMedicamente(cmd));
                }else if(x==3){
                    ComandaTigari cmd = ComandaTigari(nextId++);
                       file>>cmd;
                    comenzi.push_back(new ComandaTigari(cmd));

                }

            }
        
    }
}
    void afisare_comenzi(){
        if (comenzi.empty()) {
            std::cout << "\nNicio comanda de afisat.\n";
            return;
        }
        std::cout << "\n--- Lista Comenzi ---\n";
        for (Comanda* c_ptr : comenzi){ // Use a different name for the loop variable
            if (c_ptr) {
                std::cout << *c_ptr; // Dereference pointer, invokes the global operator<< for Comanda&
                                     // This then calls the virtual print method of the actual object.
                std::cout << "--------------------------\n"; // Separator
            }
        }
    }
    /*
    template<class T>
    void afisare_comenzi(T tip){
        for (Comanda* c : comenzi){
            if(typeid(c).name() == t){
                std::cout<<c;
            }
        }
    }
    */
    void stergere_comanda(int id){
        int poz=-1, index;
        for(Comanda* c : comenzi){
            if (c->get_id() == id){
                poz = index;
            }
            index+=1;
        }
        if (poz ==-1){
            std::cout<<"\n comanda nu exista\n";
        }
        else{
            Comanda* c = comenzi[poz];
            comenzi.erase(comenzi.begin()+poz, comenzi.begin()+poz+1);
            delete c;
        }
    }
    void cautare_comanda(int id){
        int poz=-1, index;
        for(Comanda* c : comenzi){
            if (c->get_id() == id){
                poz = index;
            }
            index+=1;
        }
        if (poz ==-1){
            std::cout<<"\n comanda nu exista\n";
        }
        else{
            std::cout<<comenzi[poz];
        }
    }
    void cautare_comanda(std::string nume){
        int poz=-1, index;
        for(Comanda* c : comenzi){
            if (c->get_nume_client() == nume){
                poz = index;
            }
            index+=1;
        }
        if (poz ==-1){
            std::cout<<"\n comanda nu exista\n";
        }
        else{
            std::cout<<comenzi[poz];
        }
    }
    void ordonare_pret(bool descending){
        if(descending){
            for (int i=0; i< comenzi.size(); i++){
                for (int j =i+1; j<comenzi.size(); j++){
                    if (comenzi[i]< comenzi[j]){
                        Comanda* aux = comenzi[i];
                        comenzi[i] = comenzi[j];
                        comenzi[j] = aux;
                    }
                }
            }
        }else{
            for (int i=0; i< comenzi.size(); i++){
                for (int j =i+1; j<comenzi.size(); j++){
                    if (comenzi[j]< comenzi[i]){
                        Comanda* aux = comenzi[i];
                        comenzi[i] = comenzi[j];
                        comenzi[j] = aux;
                    }
                }
            }
        }
    }
    void gestionare(){
        
        int mancare=0, medicamente=0, tigari=0, med_antibiotic=0 ;
        for (Comanda* c : comenzi){
            if (auto x = dynamic_cast<ComandaMancare*>(c))    
                mancare++;
            if (auto x = dynamic_cast<ComandaMedicamente*>(c)){
                medicamente +=1;
                if (x->nr_antibiotice() >=1){
                    med_antibiotic+=1;
                }
            }
            if (auto x = dynamic_cast<ComandaTigari*>(c)){
                tigari+=1;
            }
        }
        std::cout<<"\nComenzi mancare: "<<mancare;
        std::cout<<"\nComenzi medicamente: "<< medicamente<<"Comenzi cu antibiotice: "<<med_antibiotic;
        std::cout<<"\nComenzi tigari: "<<tigari;
    }
    void show_menu(){
        std::cout<<"\n1. Citire comenzi (ce permite citirea a n comenzi)\n2. Adăugare comandă (ce permite adăugarea unei comenzi noi)\n3. Afișează comenzile\n4. Ștergere comandă după ID\n5. Căutare comandă după ID\n6. Căutare comandă după numele clientului\n7. Ordonare comenzi după preț în mod descrescător\n8. Ordonare comenzi după preț în mod crescător.\n9. Gestionare comenzi\n";
    }
    bool apply_command(int op){
        bool ok = true;
        if (op == 1){
            citire_comenzi();

        }
        else if (op == 2){
            adaugare_comanda();
        }
        else if (op == 3){
            afisare_comenzi();
        }
        else if (op == 4){
            int id ;
            std::cout<<"\nId comanda: "; std::cin>> id;
            stergere_comanda(id);
        }
        else if (op == 5){
            int id ;
            std::cout<<"\nId comanda: "; std::cin>> id;
            cautare_comanda(id);
        }
        else if (op == 6){
            std::string nume;
            std::cout<<"\nNUme client: "; std::cin>> nume;
            cautare_comanda(nume);
        }
        else if (op == 7){
            ordonare_pret(true);
        }
        else if (op == 8){
            ordonare_pret(false);
        }
        else if (op == 9){
            gestionare();
        }
        else {
           ok = false;
        }
        return ok;

    }
    void run(){
        //main loop-ul aplicatiei
        bool ok = true;
        int option;
        while (ok)
        {
            show_menu();
            std::cin>>option;
            //functia care apeleaza comanzile
            ok = apply_command(option);
        }
    }

};



ManagerComenzi* ManagerComenzi::manager = nullptr;
int ManagerComenzi::nextId = 0;


int main()
{
    ManagerComenzi* manager = ManagerComenzi::Instance();
    manager->run();
    return 0;
}