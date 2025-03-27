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
                cout << "Your Vehicle Parked Successfully" << endl;
                return;
            }
        }
        cout << "Sorry no vacant spots" << endl;
    }
};
int main()
{
    ParkingLot lot(2, 2, 2, 2);
    Vehicle *car1 = new Vehicle("HR-36-1234", "LARGE");
    lot.parkVehicle(car1);
    delete car1;
}