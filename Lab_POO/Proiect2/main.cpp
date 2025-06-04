#include<iostream>
#include <queue>
#include <string>
#include <vector>
#include <iomanip>
 #include <cstdlib>
    #include <ctime>
#include <algorithm> // Necesar pentru std::min si std::max
using namespace std;

template <typename T>
class ValoareLimitata {
private:
    T valoareCurenta;
    T valoareMinima;
    T valoareMaxima;

public:
    ValoareLimitata(T min, T max, T initiala)
        : valoareMinima(min), valoareMaxima(max) {
        setValoare(initiala); // Folosim setter-ul pentru a valida valoarea initiala
    }

    T getValoare() const {
        return valoareCurenta;
    }

    T getValoareMinima() const {
        return valoareMinima;
    }

    T getValoareMaxima() const {
        return valoareMaxima;
    }

    void setValoare(T nouaValoare) {
        // Clamp the value within the defined min and max
        valoareCurenta = std::max(valoareMinima, std::min(nouaValoare, valoareMaxima));
    }

    void afiseazaDetalii() const {
        cout << "Valoare: " << valoareCurenta 
             << " (Min: " << valoareMinima 
             << ", Max: " << valoareMaxima << ")" << endl;
    }
};


class ProductionModule;
class EnergyModule; 
class FarmModule;
class ResearchModule;
class LifeSupportModule;
class StorageModule;
class SpaceStation;
class BlackHole;


class FewResorces : public exception {
    private:
        string error_msg;
    public:
        FewResorces(string msg) : error_msg(msg) {}
        FewResorces(const FewResorces& other) : error_msg(other.error_msg) {} // Copy constructor
        ~FewResorces(){};
        void display(){
            cout << "\n" << error_msg << "\n";
        }
};
class UpgradeCap : public exception {
    private: 
        string error_msg;
    public:
        UpgradeCap(string msg) : error_msg(msg){};
        UpgradeCap(const UpgradeCap& other) : error_msg(other.error_msg) {} // Copy constructor
        void display() {
            cout<<"\n "<<this->error_msg<< " \n";
        }

};

class Storage {
    private:
        ValoareLimitata<float> oxygen;
        float food;
        float energy;
        float tech;
    public:
        Storage(float initial_tech = 400, float initial_oxygen = 0, float food=0, float energy=0) 
        : tech(initial_tech), // Exemplu: max 10000 tech
          oxygen(0.0f, 1000.0f, initial_oxygen), // Exemplu: max 1000 oxygen
          food(food), energy(energy){};
       
        Storage(const Storage& other) // Copy constructor
            : oxygen(other.oxygen), food(other.food), energy(other.energy), tech(other.tech) {}

        void set_oxygen(float x) { this->oxygen.setValoare(x); }
        void set_food(float x) {this->food = x;};
        void set_energy(float x) {this->energy = x;};
        void set_tech(float x ) {this->tech =x;};

        int get_oxygen() const { return static_cast<int>(this->oxygen.getValoare()); } 
        int get_food() const {return this->food;};
        int get_energy() const {return this->energy;};
        int get_tech() const {return this->tech;};
    };
    class Module {
        protected:
        int buy_cost;
        ValoareLimitata<int> level;
        int upgrade_cost;
        string name;
        int moduleID; 
        private:
        static int nextModuleID; 
        public:
        Module(int buy_cost = 100,
            int initial_level = 1,
            int upgrade_cost = 150,
            string name = "default")
            : buy_cost(buy_cost), 
            level(1, 3, initial_level), // Min 1, Max 3
            upgrade_cost(upgrade_cost), name(name), moduleID(nextModuleID++) {} // Assign and increment ID
            
            Module(const Module& other) // Copy constructor
            : buy_cost(other.buy_cost), level(other.level), upgrade_cost(other.upgrade_cost), name(other.name), moduleID(nextModuleID++) {}
            
            virtual ~Module() {};
            
            void set_buy_cost(int new_cost) { this->buy_cost = new_cost; }
            void set_level(int new_level) { this->level.setValoare(new_level); }
        void set_upgrade_cost(int new_cost) { this->upgrade_cost = new_cost; }
        
        int get_buy_cost(){ return this->buy_cost;}
        int get_upgrade_cost() const { return this->upgrade_cost; }
        int get_level() const { return this->level.getValoare(); }
        int get_module_id() const { return this->moduleID; } // Getter for the ID
        
        static int get_total_modules_created() { return nextModuleID; } // Static method
        
        virtual void display_info()=0;
        virtual bool upgrade() { return false; }
        virtual bool repair(Storage& storage) { return false; }
        virtual void usage() {};
        virtual void production_output(Storage& s) {};
    };
    
    // Initialize the static member outside the class definition
    int Module::nextModuleID = 0;
    
    
    class ConsumptionModule : public Module {
    protected:
        int consumption;
    public: 
        ConsumptionModule(int buy_cost = 200, int level = 1, int upgrade_cost = 280, string name = "Consumption", int consumption = 20)
            : Module(buy_cost, level, upgrade_cost, name), consumption(consumption) {}
        
        ConsumptionModule(const ConsumptionModule& other) // Copy constructor
            : Module(other), consumption(other.consumption) {}

        void display_info(){
           
            cout << left << setw(5) << this->moduleID // Display Module ID
                    << left << setw(15) << this->name 
                    << left << setw(10) << this->level.getValoare() 
                    << left << setw(15) << this->buy_cost         // No consumption
                    << left << setw(15) << this->upgrade_cost// No production
                    << left << setw(10) << this->consumption 
                    << left << setw(15) << "-" 
                    << left << setw(15) << "-" << "\n";
            }
        bool upgrade() {
            try {
                if (level.getValoare() == level.getValoareMaxima()) {
                    throw UpgradeCap("Level 3 is max level cannot upgrade further");
                }
                this ->level.setValoare(this->level.getValoare() + 1);
                this -> upgrade_cost =this->buy_cost + 50 * this->level.getValoare() + this->level.getValoare()*30;
                this ->consumption -=5;
                return true;
            } catch (UpgradeCap e) {
                e.display();
                return false;
            }
        }
        void usage(){};
        
};

class LifeSupportModule : public ConsumptionModule {
    private:
        float efficiency;
    public:
        LifeSupportModule(float efficiency = 1.0) : ConsumptionModule(200, 1, 280, "Life", 20), efficiency(efficiency) {};
        LifeSupportModule(const LifeSupportModule& other) // Copy constructor
            : ConsumptionModule(other), efficiency(other.efficiency) {}
        ~LifeSupportModule(){};
        float get_efficiency() const {return this->efficiency;};    
        void set_efficiency(float v) {this->efficiency = v;}; 
            void display_info() {
                cout << left << setw(5) << this->moduleID // Display Module ID
                << left << setw(15) << this->name 
                << left << setw(10) << this->level.getValoare() 
                << left << setw(15) << this->buy_cost         // No consumption
                << left << setw(15) << this->upgrade_cost// No production
                << left << setw(10) << this->consumption
                << left << setw(15) << "-"
                << left << setw(15) << "-" <<"\n" ;
        
            }
            bool upgrade(){
                try {
                    if (level.getValoare() == level.getValoareMaxima()) {
                        throw UpgradeCap("Level 3 is max level cannot upgrade further");
                    }
                    level.setValoare(level.getValoare() + 1);
                    this -> upgrade_cost =this->buy_cost + 50 * this->level.getValoare() + this->level.getValoare()*30;
                    this->consumption-=5;
                    return true;
                }
                catch (UpgradeCap e){
                    e.display();
                    return false;

                }
    
            }
            void usage(){
                if (efficiency>0.1){
                    efficiency-=0.1;
                    this->consumption += this->consumption*efficiency;
                }
            } 
            void production_output(Storage &s){
                s.set_food(s.get_food()-this->consumption);
                s.set_oxygen(s.get_oxygen()-this->consumption);
            }
            
                bool repair(Storage& storage) override {
                    if (efficiency < 1.0f) { // Only proceed if efficiency is degraded
                        if (storage.get_tech() < 50) {
                            cout << "\nNot enough tech points to repair Life Support Module. Cost: 50 Tech Points.\n";
                            return false;
                        }
                        storage.set_tech(storage.get_tech() - 50);
                        this->efficiency = 1.0f;
                        // Base consumption for LifeSupportModule: initial 20, decreases by 5 per level up.
                        // Level 1: 20; Level 2: 15; Level 3: 10
                        this->consumption = 20 - (this->level.getValoare() - 1) * 5;
                        cout << "\nLife Support Module repaired successfully. Efficiency restored and consumption reset.\n";
                        return true;
                    } else {
                        cout << "\nLife Support Module efficiency is already optimal. No repair needed.\n";
                        return false; // No repair action taken
                    }
                }
            
    };

class ProductionModule : public Module {
    protected:
        float production;
    public:
        ProductionModule(int buy_cost = 200, int level = 1 , int upgrade_cost = 300, string name = "Production", float production = 40) : Module(buy_cost, level, upgrade_cost, name), production(production){};
        ProductionModule(const ProductionModule& other) // Copy constructor
            : Module(other), production(other.production) {}

        ~ProductionModule() {};
        int get_production() const {return this->production;}
        void set_production(float new_production) {
            this->production = new_production;
        }

        void display_info() {
            cout << left << setw(5) << this->moduleID // Display Module ID
            << left << setw(15) << this->name 
            << left << setw(10) << this->level.getValoare() 
            << left << setw(15) << this->buy_cost         // No consumption
            << left << setw(15) << this->upgrade_cost// No production
            << left << setw(10) << "-"
            << left << setw(15) << this->production
            << left << setw(15) << "-" << "\n" ;
    
        } 
        bool upgrade() {
            try {
                if (level.getValoare() == level.getValoareMaxima()) {
                    throw UpgradeCap("Level 3 is max level cannot upgrade further");
                }
            level.setValoare(level.getValoare() + 1);
            this -> upgrade_cost =this->buy_cost + 50 * this->level.getValoare() + this->level.getValoare()*40;
            this->production+=10;
            return true;
            }catch (UpgradeCap e){
                e.display();
                return false;
            }

        }
        void usage(){};
    };

class EnergyModule : public ProductionModule {
    private:
        bool online;
        float efficiency;
    public:
        EnergyModule(string name = "Energy", bool online = true, float efficiency = 1.0)
            : ProductionModule(200, 1, 300, name, 40), online(online), efficiency(efficiency) {}
        EnergyModule(const EnergyModule& other) // Copy constructor
            : ProductionModule(other), online(other.online), efficiency(other.efficiency) {}
        ~EnergyModule(){};
    void set_online(bool val){this->online =val;};
    void set_efficiency(float val){this->efficiency =val;};
    float get_efficiency() const {return this->efficiency;};    
    void usage() { if (this->efficiency > 0.1) {
        this-> efficiency -=0.1;
        this-> production *= efficiency;}};
        void display_info() override {
            cout << left << setw(5) << this->moduleID // Display Module ID
                 << left << setw(15) << name
                 << left << setw(10) << level.getValoare()
                 << left << setw(15) << buy_cost
                 << left << setw(15) << upgrade_cost
                 << left << setw(10) << "-"           // consumption
                 << left << setw(15) << production
                 << left << setw(10) << (online ? "on" : "off")<<"\n";
        }
    void production_output(Storage& s){
        s.set_energy(s.get_energy() + this->production);

    }
    bool is_online() const { return this->online; }
    void update_production_quant(){
        this-> production = production* efficiency;
    }

    bool repair(Storage& storage) override {
        if (efficiency < 1.0f) { // Only proceed if efficiency is degraded
            if (storage.get_tech() < 50) {
                cout << "\nNot enough tech points to repair Energy Module. Cost: 50 Tech Points.\n";
                return false;
            }
            storage.set_tech(storage.get_tech() - 50);
            this->efficiency = 1.0f;
            // Base production for EnergyModule: initial 40, increases by 10 per level up.
            // Level 1: 40; Level 2: 50; Level 3: 60
            this->production = 40 + (this->level.getValoare() - 1) * 10;
            cout << "\nEnergy Module repaired successfully. Efficiency restored and production reset.\n";
            return true;
        } else {
            cout << "\nEnergy Module efficiency is already optimal. No repair needed.\n";
            return false; // No repair action taken
        }
    }
};

class FarmModule : public ProductionModule {
    private:
        bool online;
        float efficiency;
    public:
        FarmModule(string name = "Farm", bool online = true, float efficiency = 1.0)
            : ProductionModule(200, 1, 300, name, 40), online(online), efficiency(efficiency) {}
        FarmModule(const FarmModule& other) // Copy constructor
            : ProductionModule(other), online(other.online), efficiency(other.efficiency) {}
        ~FarmModule(){};
    void set_online(bool val){this->online =val;};
    void set_efficiency(float val){this->efficiency =val;};
    float get_efficiency() const {return this->efficiency;};    
    void production_output(Storage& s){
        s.set_energy(s.get_energy()-10);
        s.set_food(s.get_food() + this->production);
        s.set_oxygen(s.get_oxygen() + this->production);
    }
    void usage(){
        if (this->efficiency > 0.1) {
            this-> efficiency -=0.1;
            this-> production = production* efficiency;
        }
    }
    void display_info() override {
        cout << left << setw(5) << this->moduleID // Display Module ID
             << left << setw(15) << name
             << left << setw(10) << level.getValoare()
             << left << setw(15) << buy_cost
             << left << setw(15) << upgrade_cost
             << left << setw(10) << "10 E"        // farm “consumption”
             << left << setw(15) << production
             << left << setw(10) << (online ? "on" : "off")<<"\n";
    }
    bool is_online() const { return this->online; }
    void update_production_quant(){
        this-> production = production* efficiency;
    }

    bool repair(Storage& storage) override {
        if (efficiency < 1.0f) { // Only proceed if efficiency is degraded
            if (storage.get_tech() < 50) {
                cout << "\nNot enough tech points to repair Farm Module. Cost: 50 Tech Points.\n";
                return false;
            }
            storage.set_tech(storage.get_tech() - 50);
            this->efficiency = 1.0f;
            // Base production for FarmModule: initial 40, increases by 10 per level up.
            // Level 1: 40; Level 2: 50; Level 3: 60
            this->production = 40 + (this->level.getValoare() - 1) * 10;
            cout << "\nFarm Module repaired successfully. Efficiency restored and production reset.\n";
            return true;
        } else {
            cout << "\nFarm Module efficiency is already optimal. No repair needed.\n";
            return false; // No repair action taken
        }
    }
};

class ResearchModule: public ProductionModule {
    private:
        bool online;
        float efficiency;
    public:
        ResearchModule(string name = "Research", bool online = true, float efficiency = 1.0)
            : ProductionModule(200, 1, 300, name, 100), online(online), efficiency(efficiency) {}
        ResearchModule(const ResearchModule& other) // Copy constructor
            : ProductionModule(other), online(other.online), efficiency(other.efficiency) {}
        ~ResearchModule(){};    
    void set_online(bool val){this->online =val;};  
    void set_efficiency(float val){this->efficiency =val;};
    float get_efficiency() const {return this->efficiency;};    
    void production_output(Storage& s){
        s.set_energy(s.get_energy()-20);
        s.set_tech(s.get_tech() + this->production);
        
    }   
    void usage(){
        if (this->efficiency > 0.1) {
            this-> efficiency -=0.1;
            this-> production = production* efficiency;
        }
    }       
    void update_production_quant(){
        this-> production = production* efficiency;
    }
    void display_info() override {
        cout << left << setw(5) << this->moduleID // Display Module ID
             << left << setw(15) << name
             << left << setw(10) << level.getValoare()
             << left << setw(15) << buy_cost
             << left << setw(15) << upgrade_cost
             << left << setw(10) << "20 E"        // research “consumption”
             << left << setw(15) << production
             << left << setw(10) << (online ? "on" : "off")<<"\n";
    }
    bool is_online() const { return this->online; }

    bool repair(Storage& storage) override { // Added override and Storage parameter
        if (efficiency < 1.0f) { // Only proceed if efficiency is degraded
            if (storage.get_tech() < 50) {
                cout << "\nNot enough tech points to repair Research Module. Cost: 50 Tech Points.\n";
                return false;
            }
            storage.set_tech(storage.get_tech() - 50);
            this->efficiency = 1.0f;
            // Base production for ResearchModule: initial 100, increases by 20 per level up.
            // Level 1: 100; Level 2: 120; Level 3: 140
            this->production = 100 + (this->level.getValoare() - 1) * 20;
            cout << "\nResearch Module repaired successfully. Efficiency restored and production reset.\n";
            return true;
        } else {
            cout << "\nResearch Module efficiency is already optimal. No repair needed.\n";
            return false; // No repair action taken
        }
    }
};  
class SpaceStation {
    private:
        Storage storage;
        vector<Module*> modules;

    public:
        SpaceStation(Storage storage = Storage(), vector<Module*> modules = {})
            {
                vector<Module*> m = {new EnergyModule, new LifeSupportModule, new FarmModule, new ResearchModule};
                Storage s = Storage();
                this->storage = s;
                this->modules = m;
            };
        
        SpaceStation(const SpaceStation& other) : storage(other.storage) { // Copy constructor
            for (const Module* mod : other.modules) {
                if (dynamic_cast<const EnergyModule*>(mod)) {
                    this->modules.push_back(new EnergyModule(*dynamic_cast<const EnergyModule*>(mod)));
                } else if (dynamic_cast<const LifeSupportModule*>(mod)) {
                    this->modules.push_back(new LifeSupportModule(*dynamic_cast<const LifeSupportModule*>(mod)));
                } else if (dynamic_cast<const FarmModule*>(mod)) {
                    this->modules.push_back(new FarmModule(*dynamic_cast<const FarmModule*>(mod)));
                } else if (dynamic_cast<const ResearchModule*>(mod)) {
                    this->modules.push_back(new ResearchModule(*dynamic_cast<const ResearchModule*>(mod)));
                } // Add other module types if necessary
            }
        }

        SpaceStation& operator=(const SpaceStation& other); // Assignment operator declaration

        ~SpaceStation(){
            /*
                for ( auto& m : this->modules){
            delete m;
             }
            */
        };

        void set_modules(vector<Module*> n){this-> modules = n;};
        void set_storage(Storage s){this->storage = s;};
        vector<Module*>& get_modules() {
            return this->modules;
        }
        Storage& get_storage() {
            return this->storage;
        }

        int get_tech_points() const { return this->storage.get_tech(); }

        void status(){
            cout <<"Tech: "<<this->storage.get_tech()
                 << " Energy: "<<this->storage.get_energy()
                 << " Oxygen: "<<this->storage.get_oxygen()
                 << " Food: " <<this->storage.get_food() << "\n";

            cout << left << setw(5) << "ID" // Added column for Module ID
                 << left << setw(15) << "Name" 
                 << left << setw(10) << "Level" 
                 << left << setw(10) << "BuyCost" 
                 << left << setw(15) << "UpgradeCost" 
                 << left << setw(15) << "Consumption" 
                 << left << setw(15) << "Production"
                 << left << setw(10) << "Online" << "\n";

            cout << string(5 + 15 + 10 + 10 + 15 + 15 + 15 + 15 + 10, '-') << "\n"; // Adjusted string width

            for (Module* m : this->modules) {
                m->display_info();
            }
        }
        
        void add_module(Module* mod){
            try {
                if (this->storage.get_tech() < mod->get_buy_cost())
                    throw FewResorces("not enough tech points");
                this->storage.set_tech(this->storage.get_tech()- mod->get_buy_cost());
                this->modules.push_back(mod);
            }
            catch (FewResorces e){
                e.display();
            }
        }
        void upgrade_module(int index) {
            if (!(index >= 0 && index < this->modules.size())){
                cout<<"\nINvalid index\n";
                return;
            }else{
                try {
                    auto to_upgrade = this -> modules[index];
                    if (this -> storage.get_tech() < to_upgrade->get_upgrade_cost()){
                        throw FewResorces("Upreade is too expensive");
                    } 
                    else {
                        
                        bool succeded = to_upgrade -> upgrade();
                        if (succeded)
                            this->storage.set_tech(this->get_tech_points()-to_upgrade->get_upgrade_cost());
                        
                        
                    }
                }
                catch( FewResorces e){
                    e.display();
                }
            }
        }
        void state_update(int days) {
            this->update_production();
            this->handle_degradation(days);
        };
        void update_production() {
            for(Module * m : this->modules){
                m->production_output(this->storage);
            }
        };
        void handle_degradation(int day){
            if (day != 0 && day % 10 == 0){
                for (Module * m : this->modules){
                    m->usage();
                }
            }
        };
        bool repair(int indx){
            
                if (indx < 0 || indx >= modules.size()) {
                    cout << "\nInvalid index\n";
                    return false;
                }
                Module* m = modules[indx];
                bool success = m->repair(this->storage);
                if (success) {
                    cout << "\nModule repaired successfully\n";
                } else {
                    cout << "\nModule repair failed or not needed\n";
                }
                return success;
            
        }
};

SpaceStation& SpaceStation::operator=(const SpaceStation& other) { // Assignment operator implementation
    if (this == &other) { // Check for self-assignment
        return *this;
    }

    // Clean up existing resources
    for (Module* mod : modules) {
        delete mod;
    }
    modules.clear();

    // Copy storage
    this->storage = other.storage; // Assumes Storage has a well-behaved assignment operator or copy constructor

    // Deep copy modules
    for (const Module* mod : other.modules) {
        if (dynamic_cast<const EnergyModule*>(mod)) {
            this->modules.push_back(new EnergyModule(*dynamic_cast<const EnergyModule*>(mod)));
        } else if (dynamic_cast<const LifeSupportModule*>(mod)) {
            this->modules.push_back(new LifeSupportModule(*dynamic_cast<const LifeSupportModule*>(mod)));
        } else if (dynamic_cast<const FarmModule*>(mod)) {
            this->modules.push_back(new FarmModule(*dynamic_cast<const FarmModule*>(mod)));
        } else if (dynamic_cast<const ResearchModule*>(mod)) {
            this->modules.push_back(new ResearchModule(*dynamic_cast<const ResearchModule*>(mod)));
        } // Add other module types if necessary
    }

    return *this;
}


class Hazard {
    protected:
       string name;
       string description;
       int modules_affeced;
   public:
       Hazard(string name="", string description="", int modules_affected=0) :
       name(name), description(description), modules_affeced(modules_affected) {};
       Hazard(const Hazard& other) // Copy constructor
        : name(other.name), description(other.description), modules_affeced(other.modules_affeced) {}
       virtual ~Hazard() {};
    
        string getName() const { return name; }
        void setName(const string &newName) { name = newName; }
        
        string getDescription() const { return description; }
        void setDescription(const string &newDescription) { description = newDescription; }
        
        int getModulesAffected() const { return modules_affeced; }
        void setModulesAffected(int count) { modules_affeced = count; }
    virtual void trigger_hazard(SpaceStation &station) = 0;

    virtual void asses_damage(){
        cout<<"Event happend: "<<this->name<<"\n";
        cout<<"Effect: "<<this->description<<"\n";
    }

};

class BlackHole : public Hazard {
    public:
     BlackHole(): Hazard("Black Hole", "Destroyed 2 modules", 2){};
     BlackHole(const BlackHole& other) : Hazard(other) {} // Copy constructor
     ~BlackHole(){};
    /*wipes out 2 modules that are not vital*/
    void trigger_hazard(SpaceStation &station) override{
        //cout<<"\ntriggered\n";
        
        srand(static_cast<unsigned int>(time(nullptr)));
        int removed = 0;
        auto& mods = station.get_modules();
        int modules_count =  mods.size();
        while (removed < 2 && !mods.empty()) {
            int idx = rand() % mods.size(); // Random index from 0 to mods.size()-1
            if (dynamic_cast<LifeSupportModule*>(mods[idx]) == nullptr) {
                delete mods[idx];
                mods.erase(mods.begin() + idx);
                removed++;
            }
        }
        //station.set_modules(mods);
        asses_damage();
        
    }
    void asses_damage(){
        cout<<"Event happend: "<<this->name<<"\n";
        cout<<"Effect: "<<this->description<<"\n";
    }
};

class SolarFlare: public Hazard {
    public:
    SolarFlare():Hazard("Solar Flare", "Lost 3 days of energy", 1){};
    SolarFlare(const SolarFlare& other) : Hazard(other) {} // Copy constructor
    ~SolarFlare(){};

    void trigger_hazard(SpaceStation &station) override {
        auto& mods = station.get_modules();
        int i= 0;
        float energy_production=0;
        for (auto& m : mods){
            auto em = dynamic_cast<EnergyModule*>(m);
            if (em != nullptr){
                energy_production += em->get_production() ;
            }
        }
        EnergyModule* em = dynamic_cast<EnergyModule*>(mods[i]);
        float remove  = energy_production * 3;
        Storage& st_ref = station.get_storage();
        st_ref.set_energy(st_ref.get_energy()-remove);
        asses_damage();
    }
    
};
class AsteroidField: public Hazard {
    public:
    /*halfens the efficiency for 2 modules and sets one ofline*/
    AsteroidField() : Hazard("Asteroid Field", "One module went offline and 2 suffered efficiency reduction", 3){};
    AsteroidField(const AsteroidField& other) : Hazard(other) {} // Copy constructor
    ~AsteroidField(){};

    void trigger_hazard(SpaceStation &station)
        {
        auto& mods = station.get_modules();
            vector<int> online_indices;
            for (int i = 0; i < mods.size(); i++) {
                if (dynamic_cast<EnergyModule*>(mods[i]) ||
                    dynamic_cast<FarmModule*>(mods[i]) ||
                    dynamic_cast<ResearchModule*>(mods[i]))
                    online_indices.push_back(i);
            }
            if (!online_indices.empty()) {
                int rnd = rand() % online_indices.size();
                int idx = online_indices[rnd];
                if (auto em = dynamic_cast<EnergyModule*>(mods[idx]))
                    em->set_online(false);
                else if (auto fm = dynamic_cast<FarmModule*>(mods[idx]))
                    fm->set_online(false);
                else if (auto rm = dynamic_cast<ResearchModule*>(mods[idx]))
                    rm->set_online(false);
                mods.erase(mods.begin() + idx);
            }
            int cnt = 2;
            while(!online_indices.empty() && cnt != 0){
                int rnd = rand() % online_indices.size();
                int idx = online_indices[rnd];
                if (auto em = dynamic_cast<EnergyModule*>(mods[idx])){
                    em->set_efficiency(em->get_efficiency() / 2);
                    online_indices.erase(online_indices.begin() + idx);}
                else if (auto fm = dynamic_cast<FarmModule*>(mods[idx])){

                    fm->set_efficiency(fm->get_efficiency() / 2);
                    online_indices.erase(online_indices.begin() + idx);
                }
                else if (auto rm = dynamic_cast<ResearchModule*>(mods[idx])){

                    rm->set_efficiency(rm->get_efficiency() / 2);
                    online_indices.erase(online_indices.begin() + idx);
                }
                cnt -= 1;
            }
             
        }
    
};
class PirateEncounter: public Hazard {
    public:
    PirateEncounter() : Hazard("Pirate Encounter", "Space pirates steal 1/4 the tech and 1/2 food", 0){};
    PirateEncounter(const PirateEncounter& other) : Hazard(other) {} // Copy constructor
    ~PirateEncounter() {};

    void trigger_hazard(SpaceStation &station){
       Storage &s = station.get_storage();
       s.set_food(s.get_food()/2);
       s.set_tech(s.get_tech()* 1/4);
       asses_damage();
    }

};

class Simulation {
    private:
        int days;
        SpaceStation station;
        queue<Hazard*> hazards;
        static Simulation* instance; // Static instance pointer

        // Private constructor
        Simulation (int days = 0, SpaceStation station = SpaceStation()){
            int possible_hazards=4;
            queue<Hazard*> h;
            for (int i =0; i < 50; i++){
                int rnd = rand() % possible_hazards;
                if (rnd == 0) {
                    h.push(new BlackHole());
                } else if (rnd == 1) {
                    h.push(new SolarFlare());
                } else if (rnd == 2) {
                    h.push(new AsteroidField());
                } else if (rnd == 3) {
                    h.push(new PirateEncounter());
                }
            }
            this->hazards = h;
            this->days =days;
            this->station = station; 
        };

        Simulation(const Simulation&) = delete;
        Simulation& operator=(const Simulation&) = delete;

    public:
        static Simulation* getInstance() { 
            if (instance == nullptr) {
                instance = new Simulation(); 
            }
            return instance;
        }

        static void destroyInstance() { 
            delete instance;
            instance = nullptr;
        }

    ~Simulation() { 
        while(!hazards.empty()){
            delete hazards.front();
            hazards.pop();
        }
    }

    void set_spaceship(const SpaceStation &s){
        this -> station = s;
    }

    Hazard* trigger_hazard(){
        Hazard* h = hazards.front();
                hazards.pop();
        return h;
    }
    void run(){
       // this->station.status();
        while (!hazards.empty()) {
            if (this->days !=0){

                auto chance = rand() % 3;
                if (chance==0){
                    auto triggered = trigger_hazard();
                    triggered->trigger_hazard(this->station);
                    //triggered->asses_damage();;
                }
                else{
                    cout<<"No evvent occured\n";
                }
            }
            cout<<"Days: "<<this->days<<"\n";
            this->station.status();
            string player_action;
            cin>>player_action;
            action(player_action);
            this->station.state_update(this->days);
            days+=1;
            
        }
    }   
    void action(string act){
        if (act == "buy"){
            if (act == "buy") {
                cout << "Life Support Mod(life): " 
                     << LifeSupportModule().get_buy_cost() << "\n";
                cout << "Energy Mod(energy): " 
                     << EnergyModule().get_buy_cost() << "\n";
                cout << "Farm Mod(farm): " 
                     << FarmModule().get_buy_cost() << "\n";
                cout << "Research Mod(research): " 
                     << ResearchModule().get_buy_cost() << "\n";
                     
                string to_buy;
                bool ok = true;
                while (ok){

                    cin>>to_buy;
                    if (to_buy == "life") {
                        this->station.add_module(new LifeSupportModule);
                        ok=false;
                    } else if (to_buy == "energy") {
                        this->station.add_module(new EnergyModule);
                        ok=false;
                    } else if (to_buy == "farm") {
                        this->station.add_module(new FarmModule);
                        ok=false;
                    } else if (to_buy == "research") {
                        this->station.add_module(new ResearchModule);
                        ok=false;
                    } else {
                    cout << "Unknown module type try again\n";
                }
                }
            }
        }
        else if (act == "upgrade"){
            bool ok = true;
            int indx;
            while(ok){ 
                cout<<"inde: ";cin>>indx;
                if (indx >= 0 && indx<= this->station.get_modules().size()){
                    station.upgrade_module(indx);
                    ok = false;
                }
                else{
                    cout<<"Cannot upgradetry another one\n";
                }

            }
        }
        else if (act == "repair"){
            {
                bool ok = true;
                int indx;
                while (ok) {
                    cout << "Index to repair: ";
                    cin >> indx;
                    if (indx >= 0 && indx < station.get_modules().size()) {
                        station.repair(indx);
                        ok = false;
                    } else {
                        cout << "Invalid index, try another one\n";
                    }
                }
            }
        }
        else {

        }
    }


};

Simulation* Simulation::instance = nullptr; // Initialize static instance

int main()
{
    SpaceStation s; // Create and configure SpaceStation as before
    //s.add_module(new EnergyModule);
    //s.add_module(new LifeSupportModule);

    Simulation* sim = Simulation::getInstance(); // Get the singleton instance
    sim->set_spaceship(s); // Configure the simulation with the created station
    sim->run();

    Simulation::destroyInstance(); // Clean up the singleton instance before program exit
    return 0; // Added return 0 for main
}

/*
class StorageModule : public Module {
    private:
    int storage_space;
    int occupied_space;
    public:
    StorageModule(
        int buy_cost = 150,
        int level = 1,
        int upgrade_cost = 210,
        string name = "Storage",
                   int storage_space = 400,
                   int occupied_space = 0
                ) : Module(buy_cost, level, upgrade_cost, name), storage_space(storage_space), occupied_space(occupied_space){};
                
               void display_info() {
                   cout << left << setw(5) << this->moduleID // Display Module ID
                   << left << setw(15) << this->name 
                   << left << setw(10) << this->level 
                   << left << setw(15) << this->buy_cost         // No consumption
                   << left << setw(15) << this->upgrade_cost// No production
                   << left << setw(10) << "-"
                   << left << setw(15) << "-"
                   << left << setw(15) << to_string(this->occupied_space)+"/"+to_string(this->storage_space) << "\n";
                   
               } 
               bool upgrade() {
                try {
                       if (level == 3) {
                        throw UpgradeCap("Level 3 is max level cannot upgrade further");
                    }
                    this->level+=1;
                    this->upgrade_cost = this->buy_cost + 50* this->level + 10 * level;
                   this->storage_space+=100;
                   return true;
                }
                catch( UpgradeCap e){
                       e.display();
                       return false;
                    }
                }
                
                
                */