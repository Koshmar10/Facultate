/*
DESCRIERE PROIECT
Proiectul este o interfata de acces catre o baza de date a unei reprezentante auto
*/
#include<iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;
class Car; // Forward declaration
class Database;

class Owner {
    private:
        int id;
        string cnp;
        string nume;
        vector<Car*> ownedCars;
        Database* database;
    public:
    // Constructor
    Owner(int id=-1, string cnp="", string nume="", vector<Car*> ownedCars={})
    {
        this->id = id;
        this->cnp=cnp;
        this->nume=nume;
        this->ownedCars=ownedCars;
    };

    // Copy constructor
    Owner(const Owner& other)
    {
        this->id = other.id;
        this->cnp = other.cnp;
        this->nume = other.nume;
        this->ownedCars = other.ownedCars;
    };

    ~Owner() {
        for (Car* car : ownedCars) {
             
        }
        ownedCars.clear();
    } // Destructor
    void removeCar(Car* car){
        ownedCars.erase(std::remove(ownedCars.begin(), ownedCars.end(), car), ownedCars.end());
       
    }
    // Setters and Getters
    void setId(int id) { this->id = id; }
    void setCnp(string cnp) { this->cnp = cnp; }
    void setNume(string nume) { this->nume = nume; }
    void setOwnedCars(vector<Car*> ownedCars) { this->ownedCars = ownedCars; }

    int getId() { return id; }
    string getCnp() { return cnp; }
    string getNume() { return nume; }
    vector<Car*> getOwnedCars() { return ownedCars; }
    
    // Operator overloads
    friend istream& operator>>(istream& in, Owner& owner);
    friend ostream& operator<<(ostream& out, Owner& owner);
    bool operator==(const Owner& other) const {
        return this->cnp == other.cnp;
    }
    

};


class Car {
    private:
        int id;
        string brand;
        string model;
        string year;
        float price;
        int owner_id;
        Owner* owner;
        Database* database;
    public:
    // Constructor
    Car(int id=-1, string brand="", string model="", string year="", float price=0, int owner_id=-1, Owner* owner = NULL){
        this->id=id;
        this->brand=brand;
        this->model=model;
        this->year=year;
        this->price=price;
        this->owner_id=owner_id;
        this->owner = owner;
    }

    // Copy constructor
    Car(const Car& other)
        : id(other.id), brand(other.brand), model(other.model), year(other.year), price(other.price), owner_id(other.owner_id), owner(other.owner) {}

    // Assignment operator
    Car& operator=(const Car& other) {
        if (this != &other) {
            id = other.id;
            brand = other.brand;
            model = other.model;
            year = other.year;
            price = other.price;
            owner_id = other.owner_id;
            owner = other.owner;
        }
        return *this;
    }

    // Destructor
    ~Car() {
        if (this->owner) {
            this->owner->removeCar(this); // Remove from owner's vector
        }
        
    }

    // Setters and Getters
    void setId(int id) { this->id = id; }
    void setBrand(string brand) { this->brand = brand; }
    void setModel(string model) { this->model = model; }
    void setYear(string year) { this->year = year; }
    void setPrice(float price) { this->price = price; }
    void setOwnerId(int owner_id) { this->owner_id = owner_id; }
    void setOwner(Owner* owner) { this->owner = owner; }

    int getId() const { return id; }
    string getBrand() const { return brand; }
    string getModel() const { return model; }
    string getYear() const { return year; }
    float getPrice() const { return price; }
    int getOwnerId() const { return owner_id; }
    Owner* getOwner() const { return owner; }

    // Operator overloads
    friend istream& operator>>(istream& in, Car &car);
    friend ostream& operator<<(ostream& out, Car &car);
};


class Database {
    private:
        vector<Owner*> owners;
        vector<Car*> cars;
    public:
        // Database constructor
        Database(vector<Owner*> owners={}, vector<Car*> cars={})
            : owners(owners), cars(cars) {}
        // Copy constructor
        Database(const Database& other) {
            for (auto owner : other.owners) {
                owners.push_back(new Owner(*owner));
            }
            for (auto car : other.cars) {
                cars.push_back(new Car(*car));
            }
        }

        // Destructor
        ~Database() {
            for (auto owner : owners) {
                delete owner;
            }
            owners.clear();
            for (auto car : cars) {
                delete car;
            }
            cars.clear();
        }

        // Setters
        void setOwners(vector<Owner*> owners) { this->owners = owners; }
        void setCars(vector<Car*> cars) { this->cars = cars; }

        // Getters
        vector<Owner*> getOwners() const { return owners; }
        vector<Car*> getCars() const { return cars; }

        void populateDatabase(string c, string o);
        void updateIndexes();
        
        void addOwner(Owner* owner);
        void addCar(Car* car);
        void changeOwnership(int idCar, int idOwner);
        
        
        
        void removeOwner(int ownerId);
        void removeCar(int carId);
        
        void updateFreeSpace();
        void listCars(string outFile="", string filter = "-");
        void listOwners(string outFile="", string filter = "-");

        friend Database operator+(Database& db1, Database& db2);
        
        Database& operator=(const Database& other) {
            if (this != &other) {
                // Clear existing data
                for (auto owner : owners) {
                    delete owner;
                }
                owners.clear();
                for (auto car : cars) {
                    delete car;
                }
                cars.clear();

                // Deep copy of other database
                for (auto owner : other.owners) {
                    owners.push_back(new Owner(*owner));
                }
                for (auto car : other.cars) {
                    cars.push_back(new Car(*car));
                }
            }
            return *this;
        }
        Database& operator+=( Car* car){
            this->addCar(car);
            return *this;
        }
        Database& operator+=(Owner* owner){
            this->addOwner(owner);
            return *this;
        }

};

// Database Class Functions

void Database::populateDatabase(string c, string o) {
    if (c=="" || o==""){
        return;
    }
    string line;
    string value;
    vector<string> row;
    bool firstRowPass = false;

    ifstream carFile(c);
    while(getline(carFile, line)){
        stringstream sline(line);
        row.clear();
        while(getline(sline, value, ',')){
            row.push_back(value);
        }
        if (firstRowPass){
            Car* car = new Car(0, row[0], row[1], row[2], stof(row[3]), stoi(row[4]), NULL);
            car->setId(this->cars.size());
            this->addCar(car);
        }
        firstRowPass=true;
    }
    carFile.close();
    cout<<"gata masini\n";
    firstRowPass=false;
    ifstream ownerFile(o);
    while(getline(ownerFile, line)){
        stringstream sline(line);
        row.clear();
        while(getline(sline, value, ',')){
            row.push_back(value);
        }
        if (firstRowPass){
            Owner* owner = new Owner(-1, row[0], row[1], {});
            owner->setId(this->owners.size());
            this->addOwner(owner);
            for (auto car : cars){
                if (car->getOwnerId() == owner->getId()){
                    vector<Car*> ownerCars = owner->getOwnedCars();
                    ownerCars.push_back(car);
                    owner->setOwnedCars(ownerCars);
                    car->setOwner(owner);
                }
            }            
        }
        firstRowPass=true;
    }
    ownerFile.close();
}

void Database::updateIndexes() {
    int id=0;
    for (auto& car :cars){
        car->setId(id);
        id+=1;
    }
    id=0;
    for(auto& owner : owners){
        owner->setId(id);
        for (auto& car : owner->getOwnedCars()){
            car->setOwnerId(id);
        }
        id+=1;
    }

}

void Database::addOwner(Owner* owner) {
    bool canAddOwner = true;
    for (auto& existingOwner : owners){
        if (*existingOwner == *owner)
        {
            canAddOwner = false;
            break;
        }
    }
    if (canAddOwner){
        owners.push_back(owner);
        updateIndexes();
    }else{
        cout<<"Owner:\n";
        cout<<*owner;
        cout<<"Was already inside the database\n";

    }
}

void Database::removeOwner(int ownerId){
    //removing a woner should remove all of his cars from the database
    for (auto it = owners.begin(); it != owners.end(); ++it) {
        if ((*it)->getId() == ownerId) {
            for(auto& car : (*it)->getOwnedCars()){
                this->removeCar(car->getId());
                
            }
            delete *it;
            owners.erase(it);
            break;
        }
    }
    updateIndexes();
}
void Database::removeCar(int carId){
    for (auto it = cars.begin(); it != cars.end(); ++it) {
        if ((*it)->getId() == carId) {
            delete *it;
            cars.erase(it);
            break;
        }
    }
    updateIndexes();
}

void Database::changeOwnership(int idCar, int idOwner){
    Owner* changeOwner = nullptr;
    for(auto& owner: owners){
        if (owner->getId() == idOwner){
            changeOwner = owner;
            break;
        }
    }

    Car* carToChange = nullptr;
    for (auto& car : cars){
        if(car->getId() == idCar){
            carToChange = car;
            break;
        }
    }

    if (carToChange && changeOwner) {
        Owner* prevOwner = carToChange->getOwner();
        if (prevOwner) {
            prevOwner->removeCar(carToChange);
        }
        

        carToChange->setOwner(changeOwner);
        carToChange->setOwnerId(changeOwner->getId());
        vector<Car*> nextOwnerCars = changeOwner->getOwnedCars();
        nextOwnerCars.push_back(carToChange);
        changeOwner->setOwnedCars(nextOwnerCars);
    }

    cout << *carToChange;
    cout << *changeOwner;
}

void Database::addCar(Car* car) {
    int carOwnerId = car->getOwnerId();
    for (auto& owner: owners){
        if (owner->getId() == carOwnerId){
            car->setOwner(owner);
            vector<Car*> ownerCars = owner->getOwnedCars();
            ownerCars.push_back(car);
            owner->setOwnedCars(ownerCars);
            break;
        }
    }
    cars.push_back(car);
    updateIndexes();
}

void Database::listCars(string outFile, string filter) {
    if (outFile == "") {
        for (auto car : this->cars) {
            cout << *car;
        }
    } else {
        ofstream out(outFile);
        for (auto car : this->cars) {
            out << *car;
        }
    }
}

    
void Database::listOwners(string outFile, string filter) {
    if (outFile!=""){
        ofstream out(outFile);
        if(filter == "no-cars"){
            for (auto owner: this->owners){
                out << "\nOwner ID: " << owner->getId();
                out << "\nOwner CNP: " << owner->getCnp();
                out << "\nOwner Name: " << owner->getNume();
                out<<"\n";
                
        }
    }
    else{
            for (auto owner : this->owners) {
            out << *owner;
            }
        }
    }
    else{
        ostream &out =cout;
        if(filter == "no-cars"){
            for (auto owner: this->owners){
                out << "\nOwner ID: " << owner->getId();
                out << "\nOwner CNP: " << owner->getCnp();
                out << "\nOwner Name: " << owner->getNume();
                out<<"\n";
                
        }
    }
    else{
            for (auto owner : this->owners) {
            out << *owner;
            }
        }
    }
    
}
Database operator+(Database& db1, Database& db2) {
    Database* newDb = new Database(db1);
    for (auto& owner : db2.owners) {
        newDb->addOwner(owner);
    }
    for (auto& car : db2.cars) {
        newDb->addCar(car);
    }
    newDb->updateIndexes();
    return *newDb;
}

// Car Class Functions
istream& operator>>(istream& in, Car& car) {
    cout << "\nCar ID: ";
    in >> car.id;
    cout << "Car Brand: ";
    in >> car.brand;
    cout << "Car Model: ";
    in >> car.model;
    cout << "Car Year: ";
    in >> car.year;
    cout << "Car Price: ";
    in >> car.price;
    cout << "Owner ID: ";
    in >> car.owner_id;
    return in;
}

ostream& operator<<(ostream& out, Car& car) {
    out << "\nCar ID: " << car.id;
    out << "\nCar Brand: " << car.brand;
    out << "\nCar Model: " << car.model;
    out << "\nCar Year: " << car.year;
    out << "\nCar Price: " << car.price;
    out << "\nOwner ID: " << car.owner_id;
    out << "\n";
    return out;
}

// Owner Class Functions
istream& operator>>(istream& in, Owner& owner) {
    cout << "\nOwner ID: ";
    in >> owner.id;
    cout << "Owner CNP: ";
    in >> owner.cnp;
    cout << "Owner Name: ";
    in >> owner.nume;
    return in;
}

ostream& operator<<(ostream& out, Owner& owner) {
    out << "\nOwner ID: " << owner.id;
    out << "\nOwner CNP: " << owner.cnp;
    out << "\nOwner Name: " << owner.nume;
    out << "\nCars: \n";
    for (auto car : owner.getOwnedCars()) {
        out << *car;
    }
    out << "\n";
    return out;
}

void menu(){
    cout<<"=====================================================\n";
    cout<<"For Option Show cars type: show-cars\n";
    cout<<"For Option Show Owners type: show-owners\n";
    cout<<"For Option Filter Cars type: filter-cars\n";
    cout<<"For Option Filter Owners type: filter-owners\n";
    cout<<"For Option Database Operations type: database-operations\n";
    cout<<"=====================================================\n";
}
void databaseMenu(){
    cout<<"=====================================================\n";
    cout<<"For Option Add Car type: add-car\n";
    cout<<"For Option Add Owner type: add-owner\n";
    cout<<"For Option Remove Car type: rm-car\n";
    cout<<"For Option Remove Owner type: rm-owner\n"; 
    cout<<"For Option find Owner type: find-owner\n";
    cout<<"For Option Join with another Database type: join-with\n";
    cout<<"=====================================================\n";
}
void showAvailableDatabases(vector<Database> x){
    int i=0;
    for(auto& database: x){
        cout<<"index 1: db"<<i<<" ";
        i++;
    }
}

int main() {
    Database db1 =  Database();
    Database db2 =  Database();
    /*
    Database db3 = Database();
    //db1.removeCar(3);
    //db2=db1;
    //db1.listCars();
    
    db2+= new Car(100, "Audi", "A3", "2010", 4000, 0, NULL);
    db2+= new Owner(10, "1231231313", "Mara Mihai", {});
    db2+= new Car(120, "BMW", "M3", "2023", 150000, 2, NULL);
    //db2.removeCar(3);
    db2.listOwners("", "");
    db2.listCars();
    //db1.getOwners()[0]+= Car(100, "BMW", "M8",// code for database operations "2022", 150000, 0, NULL);
    //db3.listOwners("output");
    */
    db1.populateDatabase("cars1.csv", "owners1.csv");
    db2.populateDatabase("cars.csv", "owners.csv");

    bool stop=false;
    string cmd;
    Database activeDb = db1;
    vector<Database> databases = {db1, db2};
    while( !stop ){
        menu();
        cout<<"Introdu urmatoarea comanda:";
        cin>>cmd;
        if (cmd == "show-cars") {
            activeDb.listCars();
        } else if (cmd == "show-owners") {
            activeDb.listOwners("","no-cars");
        }
        else if(cmd == "show-owner-cars"){
            activeDb.listOwners("", "");
        }
        else if(cmd == "filter-owners"){
            string ans="";
            cout<<"Select filters: -carCount ...more soon\n";
            cin>>ans;
            //sort by car count
            vector<Owner*> sortedVector;
            for(auto& owner : activeDb.getOwners()){
                auto it = sortedVector.begin();
                while (it != sortedVector.end() && owner->getOwnedCars().size() < (*it)->getOwnedCars().size()) {
                    ++it;
                }
                sortedVector.insert(it, owner);
            }
            for(auto& owner: sortedVector){
                cout << *owner;
            }

              
        }
        else if(cmd == "filter-cars") {
            string ans="";
            cout<<"Select filters: -price -year \n";
            cin>>ans;
            string filter = ans;
            cout<<"Ascending / descending order(A/D)\n";
            string order;
            cin>>order;
            vector<Car*> sortedVector;
            if (filter == "-price"){
                if (order == "A"){

                    for(auto& car : activeDb.getCars()){
                        auto it = sortedVector.begin();
                        while (it != sortedVector.end() && car->getPrice() > (*it)->getPrice()) {
                            ++it;
                        }
                        sortedVector.insert(it, car);
                    }

                }
                if(order == "D"){
                    for(auto& car : activeDb.getCars()){
                        auto it = sortedVector.begin();
                        while (it != sortedVector.end() && car->getPrice() > (*it)->getPrice()) {
                            ++it;
                        }
                        sortedVector.insert(it, car);
                    }
                }
            }
            if(filter == "-year"){
                if (order == "A"){
                    for(auto& car : activeDb.getCars()){
                        auto it = sortedVector.begin();
                        while (it != sortedVector.end() && stoi(car->getYear()) > stoi((*it)->getYear())) {
                            ++it;
                        }
                        sortedVector.insert(it, car);
                    }
                }
                if(order == "D"){
                    for(auto& car : activeDb.getCars()){
                        auto it = sortedVector.begin();
                        while (it != sortedVector.end() && stoi(car->getYear()) < stoi((*it)->getYear())) {
                            ++it;
                        }
                        sortedVector.insert(it, car);
                    }
                }
            }
            for(auto& owner: sortedVector){
                cout << *owner;
            }

        }
        else if (cmd == "database-operations") {
            bool stop1=false;
            while(!stop1){
                databaseMenu();
                cin>>cmd;
                if (cmd == "add-car"){
                    Car* inputcar = new Car;
                    cin>>*inputcar;
                    activeDb.addCar(inputcar);
                }
                else if (cmd == "add-owner"){
                    Owner* inputOwner = new Owner;
                    cin>>*inputOwner;
                    activeDb.addOwner(inputOwner);
                }
                else if(cmd == "rm-car"){
                    int id;
                    cout<<"Give the car id you want to remove ";
                    cin>>id;
                    activeDb.removeCar(id);
                }
                else if(cmd == "rm-owner"){
                    int id;
                    cout<<"Give the owner id you want to remove ";
                    cin>>id;
                    activeDb.removeOwner(id);
                }
                else if(cmd == "find-owner"){

                }
                else if(cmd == "join-with"){
                    string ans;
                    bool confirm= false;
                    int chosenDbIndex;
                    
                    cout<<"Available to join\n";
                    showAvailableDatabases(databases);
                    cout<<"\n";
                    while(!confirm){
                        cout<<"Choose Db\n";
                        cin>>chosenDbIndex;
                        Database chosenDb = databases[chosenDbIndex];
                        cout<<"See database contents before joining(y/n)\n";
                        cin>>ans;
                        if (ans=="y"){
                            chosenDb.listOwners("", "");
                        }
                        cout<<"Confirm Join?\n";
                        cin>>ans;
                        if (ans=="y"){
                            activeDb = activeDb+chosenDb;
                            confirm = true;
                            cout<<"Join Complete\n";
                            activeDb.listOwners();
                        }
                        
                    }


                }
                else if(cmd == "stop"){
                    stop1 =true; 
                }

                
            }

        } else {
            cout << "Unknown command\n";
            stop=true;
        }
    }
    
    return 0;
}
