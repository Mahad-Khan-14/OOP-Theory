#include <iostream>
#include <cstring>
using namespace std;

const int MAX_ASSIGNMENTS = 10;
const int MAX_STUDENTS = 10;
const int MAX_PROJECTS = 2;

unsigned long hashPassword(const string &password)
{
    unsigned long hash = 5381;
    for (char c : password)
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

class User
{
protected:
    string name, ID, email;
    string permissions[5];
    int permCount;
    unsigned long hashed_password;

public:
    User(string _name, string _id, string _email, string password, string perms[], int _permCount)
    {
        name = _name;
        ID = _id;
        email = _email;
        hashed_password = hashPassword(password);
        permCount = _permCount;
        for (int i = 0; i < _permCount; i++)
        {
            permissions[i] = perms[i];
        }
    }

    virtual void display()
    {
        cout << "Name: " << name << "\nID: " << ID << "\nEmail: " << email << endl;
    }

    bool authenticate(string password)
    {
        return hashPassword(password) == hashed_password;
    }

    bool hasPermission(string action)
    {
        for (int i = 0; i < permCount; i++)
        {
            if (permissions[i] == action)
                return true;
        }
        return false;
    }

    virtual void accessLab()
    {
        if (hasPermission("full_lab_access"))
            cout << name << " has full lab access.\n";
        else if (hasPermission("manage_students"))
            cout << name << " has limited TA lab access.\n";
        else
            cout << name << " has basic lab access.\n";
    }

    virtual ~User() {}
};

class Student : public User
{
protected:
    int assignments[MAX_ASSIGNMENTS];

public:
    Student(string _name, string _id, string _email, string password)
        : User(_name, _id, _email, password, new string[1]{"submit assignment"}, 1)
    {
        memset(assignments, 0, sizeof(assignments));
    }

    void display() override
    {
        cout << "[Student Info]" << endl;
        User::display();
        cout << "Assignments submitted: ";
        for (int i = 0; i < MAX_ASSIGNMENTS; i++)
            cout << assignments[i] << " ";
        cout << endl;
    }

    void assignAssignment(int index)
    {
        if (index >= 0 && index < MAX_ASSIGNMENTS)
            assignments[index] = 0;
    }

    void submitAssignment(int index)
    {
        if (index >= 0 && index < MAX_ASSIGNMENTS)
            assignments[index] = 1;
    }
};

class TA : public Student
{
private:
    Student *assignedStudents[MAX_STUDENTS];
    int studentCount;
    string projects[MAX_PROJECTS];
    int projectCount;

public:
    TA(string _name, string _id, string _email, string password)
        : Student(_name, _id, _email, password)
    {
        permissions[0] = "view projects";
        permissions[1] = "manage_students";
        permCount = 2;
        studentCount = 0;
        projectCount = 0;
    }

    void display() override
    {
        cout << "[TA Info]" << endl;
        User::display();
        cout << "Managing " << studentCount << " students and " << projectCount << " projects.\n";
    }

    void assignStudent(Student *student)
    {
        if (studentCount < MAX_STUDENTS && hasPermission("manage_students"))
        {
            assignedStudents[studentCount++] = student;
            cout << "Student assigned to TA.\n";
        }
        else
        {
            cout << "Cannot assign more students.\n";
        }
    }

    void startProject(string project)
    {
        if (projectCount < MAX_PROJECTS)
        {
            projects[projectCount++] = project;
            cout << "Started project: " << project << endl;
        }
        else
        {
            cout << "Cannot start more than 2 projects.\n";
        }
    }

    void viewProjects()
    {
        cout << "Projects:\n";
        for (int i = 0; i < projectCount; i++)
            cout << "- " << projects[i] << endl;
    }
};

class Professor : public User
{
public:
    Professor(string _name, string _id, string _email, string password)
        : User(_name, _id, _email, password, new string[2]{"assign projects", "full_lab_access"}, 2) {}

    void display() override
    {
        cout << "[Professor Info]" << endl;
        User::display();
    }

    void assignProjectToTA(TA *ta, string project)
    {
        if (hasPermission("assign projects"))
        {
            ta->startProject(project);
        }
        else
        {
            cout << "You don't have permission to assign projects.\n";
        }
    }
};

void authenticateAndPerformAction(User *user, string password, string action)
{
    if (!user->authenticate(password))
    {
        cout << "Authentication failed.\n";
        return;
    }
    cout << "Authenticated successfully.\n";
    if (user->hasPermission(action))
    {
        cout << "Action '" << action << "' is allowed.\n";
        user->accessLab();
    }
    else
    {
        cout << "Action '" << action << "' is NOT permitted.\n";
    }
}

int main()
{
    string name = "Mahad";
    string rollNo = "K240961";
    string sec = "BCS-2C";
    cout << "Name: " << name << endl
         << "Roll Num: " << rollNo << endl
         << "Section: " << sec << endl;

    Student s1("Alice", "S001", "alice@uni.edu", "pass123");
    s1.assignAssignment(0);
    s1.submitAssignment(0);

    TA ta1("Bob", "T001", "bob@uni.edu", "pass456");
    ta1.assignStudent(&s1);
    ta1.startProject("AI Research");

    Professor prof1("Dr. Smith", "P001", "smith@uni.edu", "prof789");
    prof1.assignProjectToTA(&ta1, "Cybersecurity");

    s1.display();
    cout << endl;
    ta1.display();
    cout << endl;
    prof1.display();
    cout << endl;

    authenticateAndPerformAction(&s1, "pass123", "submit assignment");
    authenticateAndPerformAction(&ta1, "pass456", "manage_students");
    authenticateAndPerformAction(&prof1, "prof789", "assign projects");

    return 0;
}
