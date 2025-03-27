#include <bits/stdc++.h>
using namespace std;

class Vehicle
{
private:
    string licensePlate;
    string size;

public:
    Vehicle(string plate, string size)
    {
        this->licensePlate = plate;
        this->size = size;
    }
    string getSize()
    {
        return size;
    }
    string getlicensePlate()
    {
        return licensePlate;
    }
};

class ParkingSpots
{
private:
    int spotID;
    string spotSize;
    bool isOccupied;
    Vehicle *parkedVehicle;

public:
    ParkingSpots(int id, string size)
    {
        this->spotID = id;
        this->spotSize = size;
        this->isOccupied = false;
    }
    bool isAvailable()
    {
        return !isOccupied;
    }
    bool canFitVehicle(Vehicle *vehicle)
    {
        return vehicle->getSize() == this->spotSize;
    }
    void parkVehicle(Vehicle *vehicle)
    {
        this->parkedVehicle = vehicle;
        this->isOccupied = true;
    }
    void removeVehicle(Vehicle *vehicle)
    {
        this->parkedVehicle = NULL;
        this->isOccupied = false;
    }
};
class ParkingFloor
{
private:
    int floorNumber;
    vector<ParkingSpots> spots;

public:
    ParkingFloor(int num, int small, int medium, int large)
    {
        this->floorNumber = num;
        int id = 0;
        for (int i = 0; i < small; i++)
        {
            spots.push_back(ParkingSpots(id, "SMALL"));
            id++;
        }
        for (int i = 0; i < medium; i++)
        {
            spots.push_back(ParkingSpots(id, "MEDIUM"));
            id++;
        }
        for (int i = 0; i < large; i++)
        {
            spots.push_back(ParkingSpots(id, "LARGE"));
            id++;
        }
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
    ParkingLot lot(2, 2, 2, 2);
    Vehicle *car1 = new Vehicle("HR-36-1234", "LARGE");
    Vehicle *car2 = new Vehicle("HR-36-1233", "LARGE");

    lot.parkVehicle(car1);
    lot.removeVehicle(car1);
    lot.removeVehicle(car2);

    delete car1;
}