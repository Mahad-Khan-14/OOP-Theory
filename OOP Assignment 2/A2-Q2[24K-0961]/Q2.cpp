#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Ghost
{
protected:
    string worker;
    int scareLevel;

public:
    Ghost(string worker) : worker(worker)
    {
        scareLevel = rand() % 10 + 1;
    }
    virtual ~Ghost() {}
    virtual void haunt() const = 0;
    int getScareLevel() const { return scareLevel; }

    friend ostream &operator<<(ostream &os, const Ghost &g)
    {
        os << "Ghost played by " << g.worker << " | Scare Level: " << g.scareLevel;
        return os;
    }
};

class Poltergeist : public Ghost
{
public:
    Poltergeist(string worker) : Ghost(worker) {}
    void haunt() const override
    {
        cout << worker << " moves objects violently!" << endl;
    }
};

class Banshee : public Ghost
{
public:
    Banshee(string worker) : Ghost(worker) {}
    void haunt() const override
    {
        cout << worker << " screams loudly!" << endl;
    }
};

class ShadowGhost : public Ghost
{
public:
    ShadowGhost(string worker) : Ghost(worker) {}
    void haunt() const override
    {
        cout << worker << " whispers creepily!" << endl;
    }
};

class ShadowPoltergeist : public Ghost
{
public:
    ShadowPoltergeist(string worker) : Ghost(worker) {}
    void haunt() const override
    {
        cout << worker << " whispers creepily and moves objects violently!" << endl;
    }
};

class Visitor
{
    string name;
    int bravery;

public:
    Visitor(string name, int bravery) : name(name), bravery(bravery) {}
    void react(int scare) const
    {
        if (scare < bravery - 3)
            cout << name << " laughs at the ghost!" << endl;
        else if (scare > bravery + 3)
            cout << name << " screams and runs away!" << endl;
        else
            cout << name << " looks shaky and nervous..." << endl;
    }
};

class HauntedHouse
{
    string name;
    Ghost *ghosts[3];
    int ghostCount;

public:
    HauntedHouse(string name) : name(name), ghostCount(0) {}
    ~HauntedHouse()
    {
        for (int i = 0; i < ghostCount; i++)
            delete ghosts[i];
    }
    void addGhost(Ghost *g)
    {
        if (ghostCount < 3)
            ghosts[ghostCount++] = g;
    }
    void simulateHaunting() const
    {
        cout << "--- Welcome to " << name << "! ---" << endl;
        for (int i = 0; i < ghostCount; i++)
        {
            cout << *ghosts[i] << endl;
            ghosts[i]->haunt();
        }
        cout << "-----------------------------" << endl;
    }

    friend void visit(Visitor visitors[], int visitorCount, const HauntedHouse &house);
};

void visit(Visitor visitors[], int visitorCount, const HauntedHouse &house)
{
    cout << "Visitors are entering " << house.name << "..." << endl;
    for (int i = 0; i < visitorCount; i++)
    {
        for (int j = 0; j < house.ghostCount; j++)
        {
            visitors[i].react(house.ghosts[j]->getScareLevel());
        }
    }
    cout << "--- The visit is over ---\n";
}

int main()
{
    string name = "Mahad";
    string rollNo = "K240961";
    string sec = "BCS-2C";
    cout << "Name: " << name << endl
         << "Roll Num: " << rollNo << endl
         << "Section: " << sec << endl;

    srand(time(0));

    HauntedHouse house1("Spooky Mansion");
    house1.addGhost(new Poltergeist("Alice"));
    house1.addGhost(new Banshee("Bob"));
    house1.addGhost(new ShadowGhost("Charlie"));

    HauntedHouse house2("Eerie Manor");
    house2.addGhost(new ShadowPoltergeist("David"));
    house2.addGhost(new Poltergeist("Eve"));
    house2.addGhost(new Banshee("Frank"));

    Visitor visitors[] = {
        Visitor("Mike", 3),
        Visitor("Sara", 6),
        Visitor("John", 9)};
    int visitorCount = sizeof(visitors) / sizeof(visitors[0]);

    house1.simulateHaunting();
    visit(visitors, visitorCount, house1);

    house2.simulateHaunting();
    visit(visitors, visitorCount, house2);

    return 0;
}
