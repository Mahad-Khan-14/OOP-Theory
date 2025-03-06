#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>

using namespace std;

class Mentor;
class Skill;

class Student
{
private:
    std::string studentID;
    std::string name;
    int age;
    std::vector<std::string> sportsInterests;
    Mentor *mentorAssigned;

public:
    Student(std::string id, std::string n, int a)
        : studentID(id), name(n), age(a), mentorAssigned(nullptr) {}

    void registerForMentorship(Mentor *m);
    void viewMentorDetails() const;
    void updateSportsInterest(const std::string &sport);

    std::string getName() const
    {
        return name;
    }
};

class Mentor
{
private:
    std::string mentorID;
    std::string name;
    std::vector<std::string> sportsExpertise;
    int maxLearners;
    std::vector<Student *> assignedLearners;

public:
    Mentor(std::string id, std::string n, int max)
        : mentorID(id), name(n), maxLearners(max) {}

    bool assignLearner(Student *s);
    void removeLearner(Student *s);
    void viewLearners() const;
    void provideGuidance() const;

    std::string getName() const
    {
        return name;
    }

    std::vector<std::string> getSportsExpertise() const
    {
        return sportsExpertise;
    }
};

class Sport
{
private:
    std::string sportID;
    std::string name;
    std::string description;
    std::vector<Skill *> requiredSkills;

public:
    Sport(std::string id, std::string n, std::string desc)
        : sportID(id), name(n), description(desc) {}

    void addSkill(Skill *s);
    void removeSkill(Skill *s);

    std::string getName() const
    {
        return name;
    }
};

class Skill
{
private:
    std::string skillID;
    std::string skillName;
    std::string description;

public:
    Skill(std::string id, std::string name, std::string desc)
        : skillID(id), skillName(name), description(desc) {}

    void showSkillDetails() const
    {
        std::cout << "Skill: " << skillName << ", Description: " << description << std::endl;
    }

    void updateSkillDescription(const std::string &newDesc)
    {
        description = newDesc;
        std::cout << "Skill description updated for " << skillName << std::endl;
    }

    std::string getSkillName() const
    {
        return skillName;
    }
};

void Student::registerForMentorship(Mentor *m)
{
    if (m->assignLearner(this))
    {
        mentorAssigned = m;
        std::cout << name << " has been assigned to mentor " << m->getName() << std::endl;
    }
    else
    {
        std::cout << "Mentor " << m->getName() << " is at full capacity." << std::endl;
    }
}

void Student::viewMentorDetails() const
{
    if (mentorAssigned)
    {
        std::cout << "Mentor Details: " << mentorAssigned->getName() << ", Expertise: ";
        for (const auto &expertise : mentorAssigned->getSportsExpertise())
        {
            std::cout << expertise << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "No mentor assigned." << std::endl;
    }
}

void Student::updateSportsInterest(const std::string &sport)
{
    sportsInterests.push_back(sport);
    std::cout << name << " has added " << sport << " to their interests." << std::endl;
}

bool Mentor::assignLearner(Student *s)
{
    if (assignedLearners.size() < maxLearners)
    {
        assignedLearners.push_back(s);
        return true;
    }
    return false;
}

void Mentor::removeLearner(Student *s)
{
    auto it = std::find(assignedLearners.begin(), assignedLearners.end(), s);
    if (it != assignedLearners.end())
    {
        assignedLearners.erase(it);
        std::cout << s->getName() << " has been removed from " << name << "'s mentorship." << std::endl;
    }
}

void Mentor::viewLearners() const
{
    std::cout << "Learners assigned to " << name << ":" << std::endl;
    for (const auto &learner : assignedLearners)
    {
        std::cout << learner->getName() << std::endl;
    }
}

void Mentor::provideGuidance() const
{
    std::cout << name << " is providing guidance to their learners." << std::endl;
}

void Sport::addSkill(Skill *s)
{
    requiredSkills.push_back(s);
    std::cout << "Skill " << s->getSkillName() << " added to " << name << std::endl;
}

void Sport::removeSkill(Skill *s)
{
    auto it = std::find(requiredSkills.begin(), requiredSkills.end(), s);
    if (it != requiredSkills.end())
    {
        requiredSkills.erase(it);
        std::cout << "Skill " << s->getSkillName() << " removed from " << name << std::endl;
    }
}

int main()
{
    string name = "M.MAHAD KHAN";
    string Rollnum = "24K-0961";
    string sec = "BCS-2C";

    cout << "Name: " << name << endl
         << "Roll NUmber: " << Rollnum << endl
         << "Section: " << sec << endl;

    Mentor mentor("M001", "Ali", 3);
    Student student("S001", "Saad", 20);
    Sport sport("SP001", "Tennis", "A racket sport");
    Skill skill("SK001", "Forehand", "Basic tennis stroke");

    sport.addSkill(&skill);

    student.updateSportsInterest("Tennis");

    student.registerForMentorship(&mentor);

    student.viewMentorDetails();

    mentor.provideGuidance();

    mentor.viewLearners();

    mentor.removeLearner(&student);

    return 0;
}