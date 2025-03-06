#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Student Class
class Student
{
private:
    int studentID;
    string name;
    bool cardActive;

public:
    // Constructor
    Student(int id, string n) : studentID(id), name(n), cardActive(false) {}

    // Getters
    int getStudentID() const
    {
        return studentID;
    }

    string getName() const
    {
        return name;
    }

    bool isCardActive() const
    {
        return cardActive;
    }

    // Pay semester fee to activate card
    void paySemesterFee()
    {
        cardActive = true;
        cout << "Semester fee paid. Card activated for " << name << " (ID: " << studentID << ").\n";
    }

    // Tap card to record attendance
    void tapCard()
    {
        if (cardActive)
        {
            cout << name << " (ID: " << studentID << ") tapped card. Attendance recorded.\n";
        }
        else
        {
            cout << name << " (ID: " << studentID << ") has an inactive card. Please pay the semester fee.\n";
        }
    }
};

// Route Class
class Route
{
private:
    int routeID;
    vector<string> stops;

public:
    // Constructor
    Route(int id) : routeID(id) {}

    // Add a stop to the route
    void addStop(const string &stop)
    {
        stops.push_back(stop);
    }

    // Display all stops on the route
    void displayStops() const
    {
        cout << "Route " << routeID << " Stops:\n";
        for (const auto &stop : stops)
        {
            cout << "- " << stop << "\n";
        }
    }

    // Get route ID
    int getRouteID() const
    {
        return routeID;
    }
};

// Bus Class
class Bus
{
private:
    int busID;
    Route *assignedRoute;
    vector<Student *> studentsOnBoard;

public:
    // Constructor
    Bus(int id) : busID(id), assignedRoute(nullptr) {}

    // Get bus ID
    int getBusID() const
    {
        return busID;
    }

    // Assign a route to the bus
    void assignRoute(Route *route)
    {
        assignedRoute = route;
        cout << "Route " << route->getRouteID() << " assigned to Bus " << busID << ".\n";
    }

    // Record attendance when a student taps their card
    void recordAttendance(Student *student)
    {
        if (student->isCardActive())
        {
            studentsOnBoard.push_back(student);
            student->tapCard();
        }
        else
        {
            cout << "Cannot record attendance. Card is inactive.\n";
        }
    }
};

// TransportSystem Class
class TransportSystem
{
private:
    vector<Student> students;
    vector<Route> routes;
    vector<Bus> buses;

public:
    // Register a new student
    void registerStudent(int id, string name)
    {
        students.emplace_back(id, name);
        cout << "Student " << name << " (ID: " << id << ") registered.\n";
    }

    // Add a new route
    void addRoute(int id)
    {
        routes.emplace_back(id);
        cout << "Route " << id << " added.\n";
    }

    // Add a new bus
    void addBus(int id)
    {
        buses.emplace_back(id);
        cout << "Bus " << id << " added.\n";
    }

    // Display system details
    void displaySystemDetails() const
    {
        cout << "\nTransport System Details:\n";
        cout << "Students:\n";
        for (const auto &student : students)
        {
            cout << "- " << student.getName() << " (ID: " << student.getStudentID() << ")\n";
        }

        cout << "\nRoutes:\n";
        for (const auto &route : routes)
        {
            route.displayStops();
        }

        cout << "\nBuses:\n";
        for (const auto &bus : buses)
        {
            cout << "- Bus " << bus.getBusID() << "\n";
        }
    }

    // Get student by ID
    Student *getStudent(int id)
    {
        for (auto &student : students)
        {
            if (student.getStudentID() == id)
            {
                return &student;
            }
        }
        return nullptr;
    }

    // Get route by ID
    Route *getRoute(int id)
    {
        for (auto &route : routes)
        {
            if (route.getRouteID() == id)
            {
                return &route;
            }
        }
        return nullptr;
    }

    // Get bus by ID
    Bus *getBus(int id)
    {
        for (auto &bus : buses)
        {
            if (bus.getBusID() == id)
            {
                return &bus;
            }
        }
        return nullptr;
    }
};

int main()
{
    string name = "M.MAHAD KHAN";
    string Rollnum = "24K-0961";
    string sec = "BCS-2C";

    cout << "Name: " << name << endl
         << "Roll NUmber: " << Rollnum << endl
         << "Section: " << sec << endl
         << endl;

    TransportSystem system;

    // Register students
    system.registerStudent(1, "Alice");
    system.registerStudent(2, "Bob");

    // Add routes
    system.addRoute(101);
    system.addRoute(102);

    // Add stops to routes
    Route *route101 = system.getRoute(101);
    route101->addStop("Stop A");
    route101->addStop("Stop B");

    Route *route102 = system.getRoute(102);
    route102->addStop("Stop X");
    route102->addStop("Stop Y");

    // Add buses
    system.addBus(201);
    system.addBus(202);

    // Assign routes to buses
    Bus *bus201 = system.getBus(201);
    bus201->assignRoute(route101);

    Bus *bus202 = system.getBus(202);
    bus202->assignRoute(route102);

    // Students pay semester fees
    Student *alice = system.getStudent(1);
    alice->paySemesterFee();

    Student *bob = system.getStudent(2);
    bob->paySemesterFee();

    // Record attendance
    bus201->recordAttendance(alice);
    bus202->recordAttendance(bob);

    // Display system details
    system.displaySystemDetails();

    return 0;
}