
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <limits>
using namespace std;

// =================================
// BASE CLASS
// =================================

class Vehicle {
protected:
    string vehicleNumber;
    string ownerName;
    string vehicleType;
    time_t entryTime;

public:
    Vehicle(string number, string owner, string type) {
        vehicleNumber = number;
        ownerName = owner;
        vehicleType = type;
        entryTime = time(0);
    }

    string getNumber() const {
        return vehicleNumber;
    }

    string getOwner() const {
        return ownerName;
    }

    string getType() const {
        return vehicleType;
    }

    time_t getEntryTime() const {
        return entryTime;
    }

    virtual double getRate() const = 0;

    virtual ~Vehicle() {}
};

// =================================
// DERIVED CLASSES
// =================================

class Bike : public Vehicle {
public:
    Bike(string n, string o) : Vehicle(n, o, "Bike") {}

    double getRate() const override {
        return 20;
    }
};

class Car : public Vehicle {
public:
    Car(string n, string o) : Vehicle(n, o, "Car") {}

    double getRate() const override {
        return 50;
    }
};

class Truck : public Vehicle {
public:
    Truck(string n, string o) : Vehicle(n, o, "Truck") {}

    double getRate() const override {
        return 80;
    }
};

// =================================
// PARKING MANAGEMENT CLASS
// =================================

class ParkingManager {
private:
    static const int TOTAL_SLOTS = 10;

    Vehicle* vehicles[TOTAL_SLOTS];
    int occupied;

public:

    ParkingManager() {
        occupied = 0;

        for (int i = 0; i < TOTAL_SLOTS; i++) {
            vehicles[i] = nullptr;
        }
    }

    // MODULE 1: REGISTER VEHICLE ENTRY

    void registerVehicle() {

        int index = -1;

        if (occupied == TOTAL_SLOTS) {
            cout << "\nParking is Full!\n";
            return;
        }

        string number, owner;
        int choice;

        cout << "\nEnter Vehicle Number: ";
        cin >> number;

        for (int i = 0; i < TOTAL_SLOTS; i++) {
            if (vehicles[i] != nullptr &&
                vehicles[i]->getNumber() == number) {

                cout << "\nVehicle Already Registered!\n";
                return;
            }
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Owner Name: ";
        getline(cin, owner);

        cout << "\nSelect Vehicle Type:\n";
        cout << "1. Bike\n";
        cout << "2. Car\n";
        cout << "3. Truck\n";

        cout << "Enter Choice: ";
        cin >> choice;

        // Find an available slot

        for (int i = 0; i < TOTAL_SLOTS; i++) {
            if (vehicles[i] == nullptr) {
                index = i;
                break;
            }
        }

        switch (choice) {

            case 1:
                vehicles[index] = new Bike(number, owner);
                break;

            case 2:
                vehicles[index] = new Car(number, owner);
                break;

            case 3:
                vehicles[index] = new Truck(number, owner);
                break;

            default:
                cout << "\nInvalid Vehicle Type!\n";
                return;
        }

        occupied++;

        cout << "\nVehicle Registered Successfully!\n";
        cout << "Parking Slot: " << index + 1 << endl;
    }

    // MODULE 2: DISPLAY AVAILABLE PARKING SLOTS

    void displaySlots() {

        cout << "\n========== PARKING SLOT STATUS ==========\n";

        for (int i = 0; i < TOTAL_SLOTS; i++) {

            cout << "Slot " << i + 1 << " : ";

            if (vehicles[i] != nullptr) {
                cout << "Occupied";
                cout << " (" << vehicles[i]->getNumber() << ")";
            }
            else {
                cout << "Available";
            }

            cout << endl;
        }

        cout << "\nTotal Slots: " << TOTAL_SLOTS;
        cout << "\nOccupied Slots: " << occupied;
        cout << "\nAvailable Slots: " << TOTAL_SLOTS - occupied;
        cout << endl;
    }

    // MODULE 3: VEHICLE EXIT
    // MODULE 4: FEE CALCULATION AND RECEIPT

    void vehicleExit() {

        string number;

        cout << "\nEnter Vehicle Number: ";
        cin >> number;

        int index = -1;

        for (int i = 0; i < TOTAL_SLOTS; i++) {

            if (vehicles[i] != nullptr &&
                vehicles[i]->getNumber() == number) {

                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "\nVehicle Not Found!\n";
            return;
        }

        Vehicle* v = vehicles[index];

        time_t exitTime = time(0);

        double duration =
            difftime(exitTime, v->getEntryTime()) / 3600.0;

        // Minimum 1 hour charge

        int hours = (int)duration;

        if (duration > hours) {
            hours++;
        }

        if (hours == 0) {
            hours = 1;
        }

        double fee = hours * v->getRate();

        // STORE ENTRY TIME

        time_t entry = v->getEntryTime();

        // GENERATE RECEIPT

        cout << "\n====================================\n";
        cout << "          PARKING RECEIPT\n";
        cout << "====================================\n";

        cout << "Vehicle Number : " << v->getNumber() << endl;
        cout << "Owner Name     : " << v->getOwner() << endl;
        cout << "Vehicle Type   : " << v->getType() << endl;

        cout << "Entry Time     : " << ctime(&entry);

        cout << "Exit Time      : " << ctime(&exitTime);

        cout << fixed << setprecision(2);

        cout << "Duration       : " << duration << " Hours\n";
        cout << "Charged Hours  : " << hours << endl;
        cout << "Rate Per Hour  : Rs. " << v->getRate() << endl;

        cout << "Total Fee      : Rs. " << fee << endl;

        cout << "====================================\n";
        cout << "          THANK YOU!\n";
        cout << "====================================\n";

        // REMOVE VEHICLE AFTER EXIT

        delete vehicles[index];

        vehicles[index] = nullptr;

        occupied--;

        cout << "\nVehicle Exit Successfully!\n";
    }

    // DESTRUCTOR

    ~ParkingManager() {

        for (int i = 0; i < TOTAL_SLOTS; i++) {
            delete vehicles[i];
        }
    }
};

// =================================
// MAIN FUNCTION
// =================================

int main() {

    ParkingManager parking;

    int choice;

    do {

        cout << "\n\n====================================\n";
        cout << "       PARKING MANAGEMENT SYSTEM\n";
        cout << "====================================\n";

        cout << "1. Register Vehicle Entry\n";
        cout << "2. Display Available Parking Slots\n";
        cout << "3. Record Vehicle Exit & Generate Receipt\n";
        cout << "4. Exit\n";

        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                parking.registerVehicle();
                break;

            case 2:
                parking.displaySlots();
                break;

            case 3:
                parking.vehicleExit();
                break;

            case 4:
                cout << "\nThank You For Using Parking System!\n";
                break;

            default:
                cout << "\nInvalid Choice! Try Again.\n";
        }

    } while (choice != 4);

    return 0;
}
