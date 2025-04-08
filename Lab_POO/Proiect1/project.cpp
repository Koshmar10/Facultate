/*
DESCRIERE PROIECT
Proiectul este o interfata de acces catre o baza de date a unei reprezentante auto
*/
#include<iostream>
#include <vector>
using namespace std;

class Car {
    private:
        int id;
        string brand;
        string model;
        string year;
        float price;
        int owner_id;
    public:
    //Constructor
    Car(
        int id=0,
        string brand ="",
        string model ="",
        string year ="",
        float price = 0,
        int owner_id= -1
    )
    {  
        this->id=id, this->brand=brand,
        this->model=model, this->year=year, 
        this->price=price, this->owner_id=owner_id;
    }
    ~Car();
    // Setters
    void setId(int id) {this->id = id;}
    void setBrand(string brand) {this->brand = brand;}
    void setModel(string model) {this->model = model;}
    void setYear(string year) {this->year = year;}
    void setPrice(float price) {this->price = price;}
    void setOwnerId(int owner_id) {this->owner_id = owner_id;}
    
    // operator overloads
    friend istream& operator>>(istream& in, Car& car);
    friend ostream& operator<<(ostream& out, Car& car);
};
class Owner{
    private:
        int id;
        string cnp;
        string nume;
        vector<int> car_ids;
    public:
};
class Databese{
    private:
        vector<Owner> owners;
        vector<Car> cars;
    public:
        //Database constructor
        Databese(vector<Owner> owners = {},  vector<Car> cars = {}){
            this->owners=owners;
            this->cars = cars;
        };
        void populateDatabase();

        void addOwner(Owner owner);
        void addCar(Car car);

        void listCars(string filter = "-");
        void listOwners(string filter = "-");
};


//Class Functions
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
    cout << "\nCar ID: ";
    out << car.id;
    cout << "Car Brand: ";
    out << car.brand;
    cout << "Car Model: ";
    out << car.model;
    cout << "Car Year: ";
    out << car.year;
    cout << "Car Price: ";
    out << car.price;
    cout << "Owner ID: ";
    out << car.owner_id;
    return out;
}

int main()
{
    return 0;
}