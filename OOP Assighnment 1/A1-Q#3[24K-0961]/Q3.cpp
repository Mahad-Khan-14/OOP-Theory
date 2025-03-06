#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class LicenseType
{
    Learner,
    Intermediate,
    Full
};

class Vehicle
{
private:
    std::string model;
    double rentalPricePerDay;
    LicenseType requiredLicense;

public:
    Vehicle(std::string m, double price, LicenseType license)
        : model(m), rentalPricePerDay(price), requiredLicense(license) {}

    std::string getModel() const
    {
        return model;
    }

    double getRentalPrice() const
    {
        return rentalPricePerDay;
    }

    LicenseType getRequiredLicense() const
    {
        return requiredLicense;
    }

    void displayDetails() const
    {
        std::cout << "Model: " << model << ", Price: $" << rentalPricePerDay << "/day, ";
        std::cout << "Required License: ";
        switch (requiredLicense)
        {
        case LicenseType::Learner:
            std::cout << "Learner";
            break;
        case LicenseType::Intermediate:
            std::cout << "Intermediate";
            break;
        case LicenseType::Full:
            std::cout << "Full";
            break;
        }
        std::cout << "\n";
    }
};

class User
{
private:
    std::string name;
    int age;
    std::string contactNumber;
    LicenseType licenseType;
    std::string userID;

public:
    User(std::string n, int a, std::string contact, LicenseType license, std::string id)
        : name(n), age(a), contactNumber(contact), licenseType(license), userID(id) {}

    void updateDetails(std::string n, int a, std::string contact, LicenseType license)
    {
        name = n;
        age = a;
        contactNumber = contact;
        licenseType = license;
    }

    LicenseType getLicenseType() const
    {
        return licenseType;
    }

    std::string getUserID() const
    {
        return userID;
    }

    void displayDetails() const
    {
        std::cout << "User ID: " << userID << ", Name: " << name << ", Age: " << age << ", ";
        std::cout << "Contact: " << contactNumber << ", License Type: ";
        switch (licenseType)
        {
        case LicenseType::Learner:
            std::cout << "Learner";
            break;
        case LicenseType::Intermediate:
            std::cout << "Intermediate";
            break;
        case LicenseType::Full:
            std::cout << "Full";
            break;
        }
        std::cout << "\n";
    }
};

class VehicleRentalSystem
{
private:
    std::vector<Vehicle *> vehicles;
    std::vector<User> users;

public:
    void addVehicle(Vehicle *vehicle)
    {
        vehicles.push_back(vehicle);
    }

    void registerUser(std::string name, int age, std::string contact, LicenseType license, std::string userID)
    {
        users.emplace_back(name, age, contact, license, userID);
        std::cout << "User registered successfully!\n";
    }

    void updateUserDetails(std::string userID, std::string name, int age, std::string contact, LicenseType license)
    {
        for (auto &user : users)
        {
            if (user.getUserID() == userID)
            {
                user.updateDetails(name, age, contact, license);
                std::cout << "User details updated successfully!\n";
                return;
            }
        }
        std::cout << "User not found!\n";
    }

    void displayAvailableVehicles() const
    {
        std::cout << "\nAvailable Vehicles:\n";
        for (const auto &vehicle : vehicles)
        {
            vehicle->displayDetails();
        }
    }

    void rentVehicle(std::string userID, std::string model)
    {
        User *user = nullptr;
        for (auto &u : users)
        {
            if (u.getUserID() == userID)
            {
                user = &u;
                break;
            }
        }

        if (!user)
        {
            std::cout << "User not found!\n";
            return;
        }

        Vehicle *vehicleToRent = nullptr;
        for (const auto &vehicle : vehicles)
        {
            if (vehicle->getModel() == model)
            {
                vehicleToRent = vehicle;
                break;
            }
        }

        if (!vehicleToRent)
        {
            std::cout << "Vehicle not found!\n";
            return;
        }

        if (user->getLicenseType() >= vehicleToRent->getRequiredLicense())
        {
            std::cout << "Rental successful!\n";
            std::cout << "User: " << userID << " has rented the vehicle: " << model << "\n";
            std::cout << "Rental Price: $" << vehicleToRent->getRentalPrice() << "/day\n";
        }
        else
        {
            std::cout << "You are not eligible to rent this vehicle.\n";
        }
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

    VehicleRentalSystem system;

    system.addVehicle(new Vehicle("Toyota Corolla", 50.0, LicenseType::Learner));
    system.addVehicle(new Vehicle("Honda Civic", 70.0, LicenseType::Intermediate));
    system.addVehicle(new Vehicle("Ford Mustang", 120.0, LicenseType::Full));

    system.registerUser("Alice", 25, "123-456-7890", LicenseType::Learner, "U001");
    system.registerUser("Bob", 30, "987-654-3210", LicenseType::Full, "U002");

    system.displayAvailableVehicles();

    system.rentVehicle("U001", "Toyota Corolla");
    system.rentVehicle("U001", "Ford Mustang");
    system.rentVehicle("U002", "Ford Mustang");

    system.updateUserDetails("U001", "Alice Smith", 26, "123-456-7890", LicenseType::Intermediate);

    system.rentVehicle("U001", "Honda Civic");

    return 0;
}