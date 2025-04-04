#include <iostream>
#include <string>
using namespace std;

#define MAX_USERS 10
#define MAX_ROUTES 10
#define MAX_BUSES 10

class TransportUser
{
protected:
    int userID;
    string name;
    bool cardActive;

public:
    TransportUser(int id = 0, string n = "") : userID(id), name(n), cardActive(false) {}
    virtual void payTransportFee() = 0;
    virtual void tapCard() const
    {
        if (cardActive)
            cout << name << " (ID: " << userID << ") tapped card. Access granted.\n";
        else
            cout << name << " (ID: " << userID << ") has an inactive card.\n";
    }
    bool isCardActive() const { return cardActive; }
    int getUserID() const { return userID; }
    string getName() const { return name; }
};

class Student : public TransportUser
{
public:
    Student(int id = 0, string n = "") : TransportUser(id, n) {}
    void payTransportFee() override
    {
        cardActive = true;
        cout << "Semester fee paid. Card activated for Student " << name << " (ID: " << userID << ").\n";
    }
};

class Teacher : public TransportUser
{
public:
    Teacher(int id = 0, string n = "") : TransportUser(id, n) {}
    void payTransportFee() override
    {
        cardActive = true;
        cout << "Monthly fee paid. Card activated for Teacher " << name << " (ID: " << userID << ").\n";
    }
};

class Staff : public TransportUser
{
public:
    Staff(int id = 0, string n = "") : TransportUser(id, n) {}
    void payTransportFee() override
    {
        cardActive = true;
        cout << "Monthly fee paid. Card activated for Staff " << name << " (ID: " << userID << ").\n";
    }
};

class Route
{
private:
    int routeID;
    string stops[5];
    int stopCount;

public:
    Route(int id = 0) : routeID(id), stopCount(0) {}
    void addStop(const string &stop)
    {
        if (stopCount < 5)
            stops[stopCount++] = stop;
    }
    void displayStops() const
    {
        cout << "Route " << routeID << " Stops:\n";
        for (int i = 0; i < stopCount; i++)
            cout << "- " << stops[i] << "\n";
    }
    int getRouteID() const { return routeID; }
};

class Bus
{
private:
    int busID;
    Route *assignedRoute;
    TransportUser *passengers[MAX_USERS];
    int passengerCount;

public:
    Bus(int id = 0) : busID(id), assignedRoute(nullptr), passengerCount(0) {}

    int getBusID() const
    {
        return busID;
    }

    void assignRoute(Route *route)
    {
        assignedRoute = route;
        cout << "Route " << route->getRouteID() << " assigned to Bus " << busID << ".\n";
    }

    void recordAttendance(TransportUser *user)
    {
        if (user->isCardActive() && passengerCount < MAX_USERS)
        {
            passengers[passengerCount++] = user;
            user->tapCard();
        }
        else
        {
            cout << "Cannot record attendance. Card is inactive or bus is full.\n";
        }
    }
};

class TransportSystem
{
private:
    Student students[MAX_USERS];
    Teacher teachers[MAX_USERS];
    Staff staffMembers[MAX_USERS];
    Route routes[MAX_ROUTES];
    Bus buses[MAX_BUSES];
    int studentCount, teacherCount, staffCount, routeCount, busCount;

public:
    TransportSystem() : studentCount(0), teacherCount(0), staffCount(0), routeCount(0), busCount(0) {}

    void registerStudent(int id, string name)
    {
        if (studentCount < MAX_USERS)
            students[studentCount++] = Student(id, name);
    }
    void registerTeacher(int id, string name)
    {
        if (teacherCount < MAX_USERS)
            teachers[teacherCount++] = Teacher(id, name);
    }
    void registerStaff(int id, string name)
    {
        if (staffCount < MAX_USERS)
            staffMembers[staffCount++] = Staff(id, name);
    }
    void addRoute(int id)
    {
        if (routeCount < MAX_ROUTES)
            routes[routeCount++] = Route(id);
    }
    void addBus(int id)
    {
        if (busCount < MAX_BUSES)
            buses[busCount++] = Bus(id);
    }

    Route *getRoute(int id)
    {
        for (int i = 0; i < routeCount; i++)
            if (routes[i].getRouteID() == id)
                return &routes[i];
        return nullptr;
    }
    Bus *getBus(int id)
    {
        for (int i = 0; i < busCount; i++)
            if (buses[i].getBusID() == id)
                return &buses[i];
        return nullptr;
    }
    TransportUser *getUser(int id)
    {
        for (int i = 0; i < studentCount; i++)
            if (students[i].getUserID() == id)
                return &students[i];
        for (int i = 0; i < teacherCount; i++)
            if (teachers[i].getUserID() == id)
                return &teachers[i];
        for (int i = 0; i < staffCount; i++)
            if (staffMembers[i].getUserID() == id)
                return &staffMembers[i];
        return nullptr;
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

    TransportSystem system;
    system.registerStudent(1, "Alice");
    system.registerTeacher(2, "Dr. Bob");
    system.registerStaff(3, "Mr. John");

    system.addRoute(101);
    system.addRoute(102);

    Route *route101 = system.getRoute(101);
    route101->addStop("Stop A");
    route101->addStop("Stop B");

    system.addBus(201);
    system.addBus(202);

    Bus *bus201 = system.getBus(201);
    bus201->assignRoute(route101);

    TransportUser *alice = system.getUser(1);
    alice->payTransportFee();
    bus201->recordAttendance(alice);

    return 0;
}
