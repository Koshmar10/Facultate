#include<iostream>
#include <vector>
#include <typeinfo>
using namespace std;


class Item {
    int cost;
    int id;
    public:
    Item(int id, int cost = 100) :id(id), cost(cost){};
    virtual ~Item(){};

    int get_id() const {return this->id;}
    int get_cost() const {return this->cost;}
    virtual int upgrade_cost()=0;
    virtual void upgrade() = 0;

    bool operator<(  Item* other)  {
        return upgrade_cost() > other->upgrade_cost();
    }

};


class Zid : public Item {
    private: 
    float lungime;
    float inaltime;
    float grosime;
    public:
    Zid(int id) : Item(id, 300), inaltime(2), lungime(1), grosime(0.5){};
    ~Zid(){};

    int upgrade_cost(){
        int cost = 100 * this->grosime * this->lungime * this->inaltime;
        
        return cost;
    }
    void upgrade() {
        this->inaltime+=1;
        this->grosime+=1;
        this->lungime+=1;
    }


};
class Turn  : public Item{
    private: 
    int putere_laser;
    public:
    Turn(int id) : Item(id, 500), putere_laser(1000) {}
    ~Turn(){};
    int upgrade_cost(){
        int cost = 500 * this->putere_laser;
        
        return cost;
    }
    void upgrade(){
        this->putere_laser+=500;
    }
};


class Robot : public Item {
    protected:
    int damage;
    int nivel;
    int viata;
    public:
    Robot(int id, int cost) : Item(id, cost), nivel(1), damage(100), viata(100) {}
    ~Robot(){};
    int upgrade_cost(){ return 0;};
    void upgrade(){};
};
class RobotAerian : public Robot {
    int autonomie;
    public:
    RobotAerian(int id): Robot(id, 100), autonomie(10){};
    ~RobotAerian(){};

    int upgrade_cost(){
        int cost = 50* this->autonomie;
        return cost;
    };
    void upgrade(){
        this->autonomie+=1;
        this->nivel+=1;
        this->damage+=25;
    };

};
class RobotTerestru: public Robot {
    int nr_gloante;
    bool are_scut;
    public:
    RobotTerestru(int id): Robot(id, 50), nr_gloante(500), are_scut(false){};
    ~RobotTerestru(){};

    int upgrade_cost(){
        int cost = 10* this->nr_gloante;
        return cost;
    };
    void upgrade(){
        this->nr_gloante+=100;
        this->nivel+=1;
        this->damage+=25;
    };
};

class GameInstance {
    int nr_puncte;
    static int next_id;
    vector<Item*> inventar;
    public:
    GameInstance(): nr_puncte(50000), inventar({}){};
    ~GameInstance(){
        
        /*
        for(auto& item : inventar){
            delete item;
            }
            */ 
        };
        static void set_next_id(int i){next_id = i;}

    void buy(){
        cout<<"\n"<<nr_puncte<<"\n";
        cout<<"1 - zid \n2 - turn \n3- robot\n";
        int x; cin>>x;
        Item* newItem;
        if (x == 3) {
            cout<<"1 - aerian 2-terestru";
            cin>>x;
            if (x==1){
                newItem = new RobotAerian(next_id+1);
            }
            else if (x==2){
                newItem = new RobotTerestru(next_id+1);
            }
        }
        else{
            if (x==1){
                newItem = new Zid(next_id+1);
            }
            else if (x==2){
                newItem = new Turn(next_id+1);
            }
        }
        if (this->nr_puncte >= newItem->get_cost()){
            if (inventar.empty()){
                inventar.push_back(newItem);
            }
            else{
                
                int i = this->inventar.size() - 1;
                while (i >= 0 && *inventar[i] < newItem) {
                    i -= 1;
                }
                inventar.insert(inventar.begin() + i + 1, newItem);
            }

            this->nr_puncte -= newItem->get_cost();
            next_id+=1;
        }
    };
    
    void upgrade(int id){
        if (nr_puncte >= inventar[id]->upgrade_cost()){
            nr_puncte -= inventar[id]->upgrade_cost();
            inventar[id]->upgrade();
        }
    };
    void show_items(){
        for (auto& item: inventar)
        {
            cout << item->get_id() <<" "<< typeid(*item).name() << " " << item->upgrade_cost() << endl;
        }
    }

    void sell(int id){}

    void show_robots(){
        for (auto& item : inventar){
            if (auto r = dynamic_cast<Robot*>(item)){
                cout << r->get_id() <<" "<< typeid(*r).name() << " " << r->upgrade_cost() << endl;
            }
        }
    }
    };




int main()
{
    GameInstance::set_next_id(0);
    GameInstance game = GameInstance();
    while (true) {
        game.buy();
        cout<<"\n";
        cout<<"What to show 1-all 2-robots";
        int x;
        cin>>x;
        if (x ==1){

          
            game.show_items();
        }
        else if( x==2)
        game.show_robots();
        cout<<"\n";   
    }
    return 0;
}

// initialize static member
// initialize static member
int GameInstance::next_id = -1;

// define missing destructors

// stub out GameInstance methods