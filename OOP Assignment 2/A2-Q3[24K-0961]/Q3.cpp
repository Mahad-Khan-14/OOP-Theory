#include <iostream>
#include <string>
using namespace std;

class Vehicle
{
protected:
    string vehicleID;
    static int activeDeliveries;

public:
    Vehicle(string id) : vehicleID(id) { activeDeliveries++; }
    virtual ~Vehicle() { activeDeliveries--; }
    virtual void calculateRoute() const = 0;
    virtual void estimatedDeliveryTime() const = 0;
    virtual void command(string action, int packageID) const = 0;
    virtual void command(string action, int packageID, string urgencyLevel) const
    {
        cout << "Processing " << action << " for package " << packageID << " with urgency: " << urgencyLevel << endl;
    }
    friend bool operator==(const Vehicle &v1, const Vehicle &v2);
    string getVehicleID() const { return vehicleID; }
};

int Vehicle::activeDeliveries = 0;

class RamzanDrone : public Vehicle
{
public:
    RamzanDrone(string id) : Vehicle(id) {}
    void calculateRoute() const override
    {
        cout << vehicleID << " calculating high-speed aerial route..." << endl;
    }
    void estimatedDeliveryTime() const override
    {
        cout << vehicleID << " estimated time: 15 minutes" << endl;
    }
    void command(string action, int packageID) const override
    {
        cout << "RamzanDrone executing " << action << " for package " << packageID << " at high speed." << endl;
    }
};

class RamzanTimeShip : public Vehicle
{
public:
    RamzanTimeShip(string id) : Vehicle(id) {}

    void calculateRoute() const override
    {
        cout << vehicleID << " verifying historical consistency before proceeding..." << endl;
    }

    void estimatedDeliveryTime() const override
    {
        cout << vehicleID << " estimated time: Variable (depends on timeline accuracy)" << endl;
    }

    void command(string action, int packageID) const override
    {
        cout << "RamzanTimeShip processing " << action << " for package " << packageID << " with historical accuracy." << endl;
    }

    void command(string action, int packageID, string urgencyLevel) const override
    {
        cout << "RamzanTimeShip processing " << action << " for package " << packageID;
        if (urgencyLevel == "urgent")
            cout << " with strict historical validation." << endl;
        else
            cout << " under normal conditions." << endl;
    }
};

class RamzanHyperPod : public Vehicle
{
public:
    RamzanHyperPod(string id) : Vehicle(id) {}
    void calculateRoute() const override
    {
        cout << vehicleID << " navigating underground high-speed tunnel network..." << endl;
    }
    void estimatedDeliveryTime() const override
    {
        cout << vehicleID << " estimated time: 30 minutes" << endl;
    }
    void command(string action, int packageID) const override
    {
        cout << "RamzanHyperPod executing " << action << " for bulk package " << packageID << "." << endl;
    }
};

bool operator==(const Vehicle &v1, const Vehicle &v2)
{
    return v1.vehicleID == v2.vehicleID;
}

class AIConflictResolver
{
public:
    static Vehicle *resolveConflict(Vehicle *v1, Vehicle *v2)
    {
        cout << "Resolving conflict between " << v1->getVehicleID() << " and " << v2->getVehicleID() << "..." << endl;
        return v1;
    }
};

int main()
{
    string name = "Mahad";
    string rollNo = "K240961";
    string sec = "BCS-2C";
    cout << "Name: " << name << endl
         << "Roll Num: " << rollNo << endl
         << "Section: " << sec << endl;

    RamzanDrone drone("Drone-1");
    RamzanTimeShip timeShip("TimeShip-1");
    RamzanHyperPod hyperPod("HyperPod-1");

    drone.calculateRoute();
    drone.estimatedDeliveryTime();
    drone.command("Deliver", 101);

    timeShip.calculateRoute();
    timeShip.estimatedDeliveryTime();
    timeShip.command("Deliver", 102, "urgent");

    hyperPod.calculateRoute();
    hyperPod.estimatedDeliveryTime();
    hyperPod.command("Deliver", 103);

    Vehicle *bestVehicle = AIConflictResolver::resolveConflict(&drone, &timeShip);
    cout << "Best vehicle selected: " << bestVehicle->getVehicleID() << endl;

    return 0;
}
