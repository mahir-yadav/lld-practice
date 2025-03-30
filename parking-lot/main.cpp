#include <bits/stdc++.h>
using namespace std;
enum class VehicleSize
{
    SMALL,
    MEDIUM,
    LARGE
};

class Vehicle
{
private:
    string licensePlate;
    VehicleSize size;

public:
    Vehicle() {}
    Vehicle(string plate, VehicleSize size)
    {
        this->licensePlate = plate;
        this->size = size;
    }
    VehicleSize getSize()
    {
        return size;
    }
    string getlicensePlate()
    {
        return licensePlate;
    }
    void setLicensePlate(string plate)
    {
        this->licensePlate = plate;
    }
    void setSize(VehicleSize size)
    {
        this->size = size;
    }
    virtual string getType() = 0;
};
class Car : public Vehicle
{
public:
    Car(string plate)
    {
        this->setLicensePlate(plate);
        this->setSize(VehicleSize::MEDIUM);
    }
    string getType() override
    {
        return "Car";
    }
};
class Bike : public Vehicle
{
public:
    Bike(string plate)
    {
        this->setLicensePlate(plate);
        this->setSize(VehicleSize::SMALL);
    }
    string getType() override
    {
        return "Bike";
    }
};
class Truck : public Vehicle
{
public:
    Truck(string plate)
    {
        this->setLicensePlate(plate);
        this->setSize(VehicleSize::LARGE);
    }
    string getType() override
    {
        return "Truck";
    }
};
class ParkingSpots
{
private:
    int spotID;
    VehicleSize spotSize;
    Vehicle *parkedVehicle;

public:
    ParkingSpots(int id, VehicleSize size)
    {
        this->spotID = id;
        this->spotSize = size;
        this->parkedVehicle = NULL;
    }
    ~ParkingSpots()
    {
        if (parkedVehicle)
        {
            delete parkedVehicle;
        }
    }
    bool isAvailable()
    {
        return parkedVehicle == NULL;
    }
    bool canFitVehicle(Vehicle *vehicle)
    {
        return vehicle->getSize() <= this->spotSize;
    }
    void parkVehicle(Vehicle *vehicle)
    {
        this->parkedVehicle = vehicle;
    }
    void removeVehicle(Vehicle *vehicle)
    {
        this->parkedVehicle = NULL;
    }
    string VehicleSizeToString(VehicleSize size)
    {
        if (size == VehicleSize::SMALL)
            return "SMALL";
        else if (size == VehicleSize::MEDIUM)
            return "MEDIUM";
        else if (size == VehicleSize::LARGE)
            return "LARGE";
        else
            return "ERROR";
    }
    void display()
    {

        cout << "Spot Id: " << spotID << "( Spot Size: " << VehicleSizeToString(spotSize) << " ) ";
        if (isAvailable())
        {
            cout << "[ Available ]" << endl;
        }
        else
        {
            cout << "[Occupied by [" << parkedVehicle->getType() + " , " + parkedVehicle->getlicensePlate() << "] ]" << endl;
        }
    }
    Vehicle *getParkedVehicle()
    {
        return parkedVehicle;
    }
};
class ParkingFloor
{
private:
    int floorNumber;
    vector<ParkingSpots> spots;
    void addSpots(int &id, int cnt, VehicleSize size)
    {
        for (int i = 0; i < cnt; i++)
        {
            spots.push_back(ParkingSpots(id, size));
            id++;
        }
    }

public:
    ParkingFloor(int num, int &id, int small, int medium, int large)
    {
        this->floorNumber = num;
        addSpots(id, small, VehicleSize::SMALL);
        addSpots(id, medium, VehicleSize::MEDIUM);
        addSpots(id, large, VehicleSize::LARGE);
    }
    ParkingSpots *findSpot(Vehicle *vehicle)
    {
        for (auto &spot : spots)
        {
            if (spot.isAvailable() && spot.canFitVehicle(vehicle))
            {
                return &spot;
            }
        }
        return NULL;
    }
    void display()
    {
        cout << "Floor number : " << floorNumber << endl;
        for (auto &it : spots)
        {
            it.display();
        }
    }
};
class VehicleFactory
{
public:
    static Vehicle *createVehicle(string type, string plate)
    {
        if (type == "Car")
            return new Car(plate);
        if (type == "Bike")
            return new Bike(plate);
        if (type == "Truck")
            return new Truck(plate);
        throw invalid_argument("Unknown invalid argument: " + type);
    }
};
class ParkingLot
{
private:
    vector<ParkingFloor> floors;
    unordered_map<string, ParkingSpots *> parkedVehicles;

public:
    ParkingLot(int numFloors, int small, int medium, int large)
    {
        int id = 1;
        for (int i = 1; i <= numFloors; i++)
        {
            floors.push_back(ParkingFloor(i, id, small, medium, large));
        }
    }
    // ~ParkingLot()
    // {
    //     for (auto &it : parkedVehicles)
    //     {
    //         it->removeVehicle();
    //     }
    //     parkedVehicles.clear();
    // }
    void parkVehicle(string type, string plate)
    {
        Vehicle *vehicle = VehicleFactory::createVehicle(type, plate);
        for (auto &floor : floors)
        {
            ParkingSpots *spot = floor.findSpot(vehicle);
            if (spot)
            {
                spot->parkVehicle(vehicle);
                parkedVehicles[vehicle->getlicensePlate()] = spot;
                cout << vehicle->getType() << " [" << vehicle->getlicensePlate() << "] " << " Parked Successfully" << endl;
                return;
            }
        }
        cout << "Sorry no vacant spots" << endl;
        delete vehicle;
    }
    void removeVehicle(string plate)
    {

        if (parkedVehicles.find(plate) != parkedVehicles.end())
        {
            ParkingSpots *spot = parkedVehicles[plate];
            Vehicle *vehicle = spot->getParkedVehicle();
            spot->removeVehicle(vehicle);
            parkedVehicles.erase(plate);
            cout << vehicle->getType() << " [" << vehicle->getlicensePlate() << "] " << " successfully exited" << endl;
        }
        else
        {
            cout << " [" << plate << "] " << "is not present in parking lot" << endl;
        }
    }
    void display()
    {
        for (auto &it : floors)
        {
            it.display();
            cout << "-----------------" << endl;
        }
    }
};
int main()
{
    ParkingLot lot(2, 2, 1, 1);

    // lot.display();
    lot.parkVehicle("Car", "1234");
    lot.removeVehicle("1234");
    lot.parkVehicle("Bike", "1235");
    lot.parkVehicle("Bike", "1236");
    lot.parkVehicle("Bike", "1240");
    lot.parkVehicle("Bike", "1244");
    lot.parkVehicle("Car", "1237");
    lot.parkVehicle("Truck", "1233");
    lot.removeVehicle("1244");

    lot.display();
}

// OOPS Concepts
//  1.Encapsulation
//  In vehicle class size and license plate are private and provided public methods to access them.
//  2.Inheritance
//  car,bike,truck inherit from vehicle class
//  3.polymorphism
// getType() override in car,truck,bike
// 4.Abstraction
//  parkvehicle and removevehicle functions

// Design Pattern
//  1.Factory
//  instead of creating manually
//  Vehicle *car1 = new Car("1234");
//  Vehicle *truck1 = new Truck("1233");
//  we can do vehicle *car=VehicleFactory::createVehicle("Car","1234")
