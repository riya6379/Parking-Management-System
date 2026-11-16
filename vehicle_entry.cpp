#include "vehicle_entry.h"
#include "slot_management.h"
#include "utils.h"
#include "vehicle_exit.h"
#include <iostream>

Vehicle* registerVehicle(ParkingLot& lot, const std::string& number, const std::string& owner,
                         VehicleType type, std::string& err, std::time_t entryTime) {
    std::string num = normalizeNumber(number);
    if (!isValidVehicleNumber(num)) { err = "Invalid vehicle number (use 4-12 letters/digits)."; return nullptr; }
    if (owner.empty())              { err = "Owner name cannot be empty."; return nullptr; }
    if (findVehicle(lot, num))      { err = "Vehicle " + num + " is already parked."; return nullptr; }

    int slot = allocateSlot(lot);
    if (slot == -1) { err = "Parking is full. No slot available."; return nullptr; }

    Vehicle* v = new Vehicle{num, owner, type, entryTime, slot, nullptr};
    // append at the end of the linked list (keeps entry order)
    if (!lot.vehicles) lot.vehicles = v;
    else {
        Vehicle* cur = lot.vehicles;
        while (cur->next) cur = cur->next;
        cur->next = v;
    }
    return v;
}

void registerVehicleInteractive(ParkingLot& lot) {
    std::cout << "\n--- Vehicle Entry Registration ---\n";
    if (availableSlots(lot) == 0) { std::cout << "Parking is full. No slot available.\n"; return; }

    std::string number = readLine("Vehicle number (e.g. RJ14 AB 1234): ");
    std::string owner = readLine("Owner name: ");
    for (auto& c : owner) if (c == '|') c = '/';   // '|' is the file delimiter
    std::cout << "Vehicle type: 1. Bike  2. Car  3. Truck\n";
    int t = readInt("Choose: ", 1, 3);

    std::string err;
    Vehicle* v = registerVehicle(lot, number, owner, (VehicleType)t, err);
    if (!v) { std::cout << "Error: " << err << "\n"; return; }

    std::cout << "Vehicle registered successfully!\n"
              << "  Vehicle No. : " << v->number << "\n"
              << "  Type        : " << typeToString(v->type) << "\n"
              << "  Slot        : " << v->slot << "\n"
              << "  Entry time  : " << formatTime(v->entryTime) << "\n";
}
