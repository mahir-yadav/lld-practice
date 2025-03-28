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
};
class Car : public Vehicle
{
public:
    Car(string plate)
    {
        this->setLicensePlate(plate);
        this->setSize(VehicleSize::MEDIUM);
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
};
class Truck : public Vehicle
{
public:
    Truck(string plate)
    {
        this->setLicensePlate(plate);
        this->setSize(VehicleSize::LARGE);
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
        cout << "Spot Id: " << spotID << " Spot Size: " << VehicleSizeToString(spotSize) << endl;
        if (isAvailable())
        {
            cout << "Available" << endl;
        }
        else
        {
            cout << "Not Available " << parkedVehicle->getlicensePlate() << " has parked" << endl;
        }
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
        cout << "Floor number is " << floorNumber << endl;
        cout << "Spots available are " << endl;
        for (auto &it : spots)
        {
            it.display();
        }
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
    void parkVehicle(Vehicle *vehicle)
    {
        for (auto &floor : floors)
        {
            ParkingSpots *spot = floor.findSpot(vehicle);
            if (spot)
            {
                spot->parkVehicle(vehicle);
                parkedVehicles[vehicle->getlicensePlate()] = spot;
                cout << "Your Vehicle Parked Successfully" << endl;
                return;
            }
        }
        cout << "Sorry no vacant spots" << endl;
    }
    void removeVehicle(Vehicle *vehicle)
    {
        string plate = vehicle->getlicensePlate();
        if (parkedVehicles.find(plate) != parkedVehicles.end())
        {
            ParkingSpots *spot = parkedVehicles[plate];
            spot->removeVehicle(vehicle);
            parkedVehicles.erase(plate);
            cout << "Your vehicle successfully exited" << endl;
        }
        else
        {
            cout << "No such vehicle is present in parking lot" << endl;
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
    Vehicle *car1 = new Car("1234");
    Vehicle *truck1 = new Truck("1233");
    Vehicle *bike1 = new Bike("1235");
    Vehicle *bike2 = new Bike("1236");
    Vehicle *bike3 = new Bike("1240");
    Vehicle *bike4 = new Bike("1244");
    Vehicle *car2 = new Car("1237");

    // lot.display();
    lot.parkVehicle(car1);
    lot.removeVehicle(car1);
    lot.parkVehicle(bike1);
    lot.parkVehicle(bike2);
    lot.parkVehicle(bike3);
    lot.parkVehicle(bike4);
    lot.parkVehicle(car2);
    lot.parkVehicle(truck1);

    lot.display();
    delete car1;
    delete car2;
    delete bike1;
    delete bike2;
    delete bike3;
    delete bike4;
    delete truck1;
}