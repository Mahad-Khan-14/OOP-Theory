
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
using namespace std;

const int MAX_USERS = 100;
const int MAX_VEHICLES = 50;
const int MAX_ROUTES = 50;
const int MAX_DRIVERS = 50;

enum UserType
{
    STUDENT,
    FACULTY
};

class BookingException : public exception
{
    string message;

public:
    BookingException(string msg) : message(msg) {}
    const char *what() const noexcept override { return message.c_str(); }
};

class User
{
public:
    string name;
    UserType type;
    bool paymentDone;
    int bookedVehicleID;
    int seatNumber;

    User(string n, UserType t) : name(n), type(t), paymentDone(false), bookedVehicleID(-1), seatNumber(-1) {}
    virtual int calculateFare(bool isAC) const = 0;
    void makePayment() { paymentDone = true; }
};

class Student : public User
{
public:
    Student(string n) : User(n, STUDENT) {}
    int calculateFare(bool isAC) const override { return isAC ? 100 : 80; }
};

class Faculty : public User
{
public:
    Faculty(string n) : User(n, FACULTY) {}
    int calculateFare(bool isAC) const override { return isAC ? 150 : 120; }
};

class Driver
{
public:
    int id;
    string name;
    bool assigned;

    Driver(int i, string n) : id(i), name(n), assigned(false) {}
};

class Route
{
public:
    int id;
    string source, destination;
    int duration;

    Route(int i, string s, string d, int dur) : id(i), source(s), destination(d), duration(dur) {}
};

class Vehicle
{
public:
    int id;
    bool isAC;
    int totalSeats;
    UserType seatType[50];
    string seatBookedBy[50];
    Driver *driver;
    Route *route;

    Vehicle(int i, bool ac, int seats, Driver *d, Route *r) : id(i), isAC(ac), totalSeats(seats), driver(d), route(r)
    {
        for (int j = 0; j < totalSeats; j++)
        {
            seatType[j] = (j % 2 == 0) ? STUDENT : FACULTY;
            seatBookedBy[j] = "";
        }
        if (driver)
            driver->assigned = true;
    }

    bool bookSeat(User *user)
    {
        if (!user->paymentDone)
            throw BookingException("Payment not completed.");
        for (int i = 0; i < totalSeats; i++)
        {
            if (seatType[i] == user->type && seatBookedBy[i] == "")
            {
                seatBookedBy[i] = user->name;
                user->bookedVehicleID = id;
                user->seatNumber = i + 1;
                return true;
            }
        }
        throw BookingException("No available seats for user type.");
    }

    void display() const
    {
        cout << "Vehicle ID: " << id << ", AC: " << (isAC ? "Yes" : "No")
             << ", Driver: " << (driver ? driver->name : "None")
             << ", Route: " << route->source << " to " << route->destination << endl;
    }
};

template <typename T, int SIZE>
class EntityList
{
    T *items[SIZE];
    int count;

public:
    EntityList() : count(0) {}
    bool add(T *item)
    {
        if (count >= SIZE)
            return false;
        items[count++] = item;
        return true;
    }
    T *get(int index) { return (index >= 0 && index < count) ? items[index] : nullptr; }
    int getCount() const { return count; }
    T *findById(int id)
    {
        for (int i = 0; i < count; i++)
            if (items[i]->id == id)
                return items[i];
        return nullptr;
    }
    T *findByName(string name)
    {
        for (int i = 0; i < count; i++)
            if (items[i]->name == name)
                return items[i];
        return nullptr;
    }
    T *operator[](int index) { return items[index]; }
};

EntityList<User, MAX_USERS> users;
EntityList<Driver, MAX_DRIVERS> drivers;
EntityList<Route, MAX_ROUTES> routes;
EntityList<Vehicle, MAX_VEHICLES> vehicles;

User *createUser(string name, string typeStr)
{
    if (typeStr == "student")
        return new Student(name);
    else if (typeStr == "faculty")
        return new Faculty(name);
    else
        return nullptr;
}

void saveToFile()
{
    ofstream fout("drivers.txt");
    for (int i = 0; i < drivers.getCount(); i++)
        fout << drivers[i]->id << "," << drivers[i]->name << "," << drivers[i]->assigned << endl;
    fout.close();

    fout.open("routes.txt");
    for (int i = 0; i < routes.getCount(); i++)
        fout << routes[i]->id << "," << routes[i]->source << "," << routes[i]->destination << "," << routes[i]->duration << endl;
    fout.close();

    fout.open("users.txt");
    for (int i = 0; i < users.getCount(); i++)
    {
        fout << users[i]->name << "," << users[i]->type << "," << users[i]->paymentDone << ","
             << users[i]->bookedVehicleID << "," << users[i]->seatNumber << endl;
    }
    fout.close();
}

void menu()
{
    int choice;
    do
    {
        cout << "\n1. Register User\n2. Add Driver\n3. Add Route\n4. Add Vehicle\n5. Make Payment\n6. Book Seat\n7. Save to File\n8. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1)
        {
            string name, type;
            cout << "Enter name and type (student/faculty): ";
            cin >> name >> type;
            User *u = createUser(name, type);
            if (u && users.add(u))
                cout << "User registered.\n";
            else
                cout << "Failed to register user.\n";
        }
        else if (choice == 2)
        {
            int id;
            string name;
            cout << "Enter driver ID and name: ";
            cin >> id >> name;
            if (drivers.findById(id))
            {
                cout << "Driver ID already exists!\n";
                continue;
            }
            drivers.add(new Driver(id, name));
        }
        else if (choice == 3)
        {
            int id, dur;
            string src, dest;
            cout << "Enter route ID, source, destination, duration: ";
            cin >> id >> src >> dest >> dur;
            if (routes.findById(id))
            {
                cout << "Route ID already exists!\n";
                continue;
            }
            routes.add(new Route(id, src, dest, dur));
        }
        else if (choice == 4)
        {
            int id, seats, routeID, driverID;
            bool ac;
            cout << "Enter vehicle ID, AC(1/0), seats, routeID, driverID: ";
            cin >> id >> ac >> seats >> routeID >> driverID;
            Route *r = routes.findById(routeID);
            Driver *d = drivers.findById(driverID);
            if (!r || !d)
            {
                cout << "Invalid route or driver ID.\n";
                continue;
            }
            vehicles.add(new Vehicle(id, ac, seats, d, r));
        }
        else if (choice == 5)
        {
            string name;
            cout << "Enter user name: ";
            cin >> name;
            User *user = users.findByName(name);
            if (!user)
            {
                cout << "User not found.\n";
                continue;
            }
            for (int i = 0; i < vehicles.getCount(); i++)
                vehicles[i]->display();
            int vid;
            cout << "Enter vehicle ID: ";
            cin >> vid;
            Vehicle *v = nullptr;
            for (int i = 0; i < vehicles.getCount(); i++)
                if (vehicles[i]->id == vid)
                    v = vehicles[i];
            if (!v)
            {
                cout << "Vehicle not found.\n";
                continue;
            }
            int fare = user->calculateFare(v->isAC);
            cout << "Fare: Rs." << fare << ". Confirm payment? (y/n): ";
            char c;
            cin >> c;
            if (c == 'y')
            {
                user->makePayment();
                cout << "Payment successful.\n";
            }
        }
        else if (choice == 6)
        {
            string name;
            cout << "Enter user name: ";
            cin >> name;
            User *user = users.findByName(name);
            if (!user)
            {
                cout << "User not found.\n";
                continue;
            }
            for (int i = 0; i < vehicles.getCount(); i++)
                vehicles[i]->display();
            int vid;
            cout << "Enter vehicle ID: ";
            cin >> vid;
            Vehicle *v = nullptr;
            for (int i = 0; i < vehicles.getCount(); i++)
                if (vehicles[i]->id == vid)
                    v = vehicles[i];
            if (!v)
            {
                cout << "Vehicle not found.\n";
                continue;
            }
            try
            {
                if (v->bookSeat(user))
                    cout << "Seat booked successfully.\n";
            }
            catch (const BookingException &e)
            {
                cout << "Booking failed: " << e.what() << endl;
            }
        }
        else if (choice == 7)
        {
            saveToFile();
            cout << "Data saved to files.\n";
        }
    } while (choice != 8);
}

int main()
{
    menu();
    return 0;
}
