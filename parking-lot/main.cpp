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
};
class ParkingFloor
{
private:
    int floorNumber;
    vector<ParkingSpots> spots;
    void addSpots(int id, int cnt, VehicleSize size)
    {
        for (int i = 0; i < cnt; i++)
        {
            spots.push_back(ParkingSpots(id, size));
            id++;
        }
    }

public:
    ParkingFloor(int num, int small, int medium, int large)
    {
        this->floorNumber = num;
        int id = 0;
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
};
class ParkingLot
{
private:
    vector<ParkingFloor> floors;
    unordered_map<string, ParkingSpots *> parkedVehicles;

public:
    ParkingLot(int numFloors, int small, int medium, int large)
    {
        for (int i = 0; i < numFloors; i++)
        {
            floors.push_back(ParkingFloor(i, small, medium, large));
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
};
int main()
{
    ParkingLot lot(2, 2, 2, 0);
    Vehicle *car1 = new Car("1234");
    Vehicle *truck1 = new Truck("1233");

    lot.parkVehicle(car1);
    lot.removeVehicle(car1);
    lot.parkVehicle(truck1);

    delete car1;
    delete truck1;
}