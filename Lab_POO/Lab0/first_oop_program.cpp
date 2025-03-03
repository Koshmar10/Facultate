#include <iostream>
#include <vector>
using namespace std;


class Car {
    private:

        string make;
        string model;
        string licensePlate;
        string owner;
        
        int fabricationYear;
        int miles;
        
    public:
    
    //Getters for Car class

    int getFabricationYear(){return this->fabricationYear;};
    int getMiles(){ return this->miles; };

    string getLicencePlate(){ return this->licensePlate; };
    string getOwner(){ return this->owner; };
    string getMake(){ return this->make; };
    string getModel() { return this->model; };

    //Setters for car class

    void setMake(string newMake){this->make = newMake;}
    void setModel(string newModel){this->model = newModel;}
    void setLicencePlate(string newPlate){this->licensePlate = newPlate;}
    void setOwner(string newOwner){this->owner = newOwner;}

    void setFabricationYear(int newYear){this->fabricationYear = newYear;}
    void setMiles(int newMiles){this->miles = newMiles;}
    
    //Data work functions
    
    //Inputin / Outputing data functions
    
    friend istream& operator>>(istream &in, Car &car);
    friend ostream& operator<<(ostream &out, Car&car);
    
    //Misc functions
    friend istream& assignLicensePlate(istream &in){
        string l;
        in>>l;
        if(l == ""){
            this->"caoie";

        };
        return in;
    }
    
    //Constructors
    Car(string make, string model, int fabricationYear, string licensePlate, string owner, int miles);
    Car(const Car &x);
    //~Car();    
};
class DealershipDatabase {
    private:
        vector<Car> carTable;
        int databaseItemCount = carTable.size();

    public:
        
};

istream& operator>>(istream &in, Car &car){
    cout<<"\nCar Make: ";
    in>>car.make;
    cout<<"\nCar Model: ";
    in>>car.model;
    cout<<"\n Car Fabricaion year: ";
    in>>car.fabricationYear;
    cout<<"\nCar milage: ";
    in>>car.miles;
    cout<<"\nEnter license plate: ";
    car.assignLicensePlate(in, car);
    cout<<"\nEnter owner name: ";
    in>>car.owner;
    return in;    
}


ostream& operator<<(ostream &out, Car &car){
    out<<"Make and Model: "<<car.make<<" "<<car.model<<"\n";
    out<<"Fabricated in: "<<car.fabricationYear<<"\n";
    out<<"Miles: "<<car.miles<<"\n";
    out<<"Owner: "<<car.owner<<"\n";
    return out;
}


Car::Car(string make = "", string model = "", int fabricationYear = 0, string licensePlate = "", string owner = "", int miles=0){
    this -> make = make;
    this -> model = model;
    this -> fabricationYear = fabricationYear;
    this -> licensePlate = licensePlate;
    this -> owner = owner;
    this -> miles = miles;

}
Car::Car(const Car &x){
    this -> make = x.make;
    this -> model = x.model;
    this -> fabricationYear = x.fabricationYear;
    this -> licensePlate = x.licensePlate;
    this -> owner = x.owner;
    this -> miles = x.miles;
}

int main(){
    Car petruCar("Audi", "A3", 2009, "CT10UDS", "Mara");
    Car maraCar(petruCar);   
    Car bossCar;
    cin>>bossCar;
    cout<<bossCar;   
    
    return 0;

}