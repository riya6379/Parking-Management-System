#include "vehicle_exit.h"
#include "fee_calculation.h"
#include "receipt_records.h"
#include "slot_management.h"
#include "utils.h"
#include <iomanip>
#include <iostream>

Vehicle* findVehicle(const ParkingLot& lot, const std::string& number) {
    for (Vehicle* v = lot.vehicles; v; v = v->next)
        if (v->number == number) return v;
    return nullptr;
}

long parkedMinutes(const Vehicle& v, std::time_t now) {
    long secs = (long)(now - v.entryTime);
    if (secs < 0) secs = 0;
    return (secs + 59) / 60;   // round up to whole minutes
}

static bool unlinkVehicle(ParkingLot& lot, const Vehicle* target) {
    Vehicle* prev = nullptr;
    Vehicle* cur = lot.vehicles;
    while (cur && cur != target) { prev = cur; cur = cur->next; }
    if (!cur) return false;
    if (!prev) lot.vehicles = cur->next;
    else prev->next = cur->next;
    delete cur;
    return true;
}

Transaction* processExit(ParkingLot& lot, const std::string& number, std::time_t exitTime) {
    Vehicle* v = findVehicle(lot, normalizeNumber(number));
    if (!v) return nullptr;

    long minutes = parkedMinutes(*v, exitTime);
    double fee = calculateFee(v->type, minutes);

    Transaction* t = addTransaction(lot, *v, exitTime, minutes, fee);  // Module 5
    freeSlot(lot, v->slot);                                            // Module 2
    unlinkVehicle(lot, v);
    return t;
}

void vehicleExitInteractive(ParkingLot& lot) {
    std::cout << "\n--- Vehicle Exit ---\n";
    if (!lot.vehicles) { std::cout << "No vehicles are currently parked.\n"; return; }

    std::string number = normalizeNumber(readLine("Enter vehicle number: "));
    Vehicle* v = findVehicle(lot, number);
    if (!v) { std::cout << "Vehicle " << number << " not found in parking.\n"; return; }

    long minutes = parkedMinutes(*v, std::time(nullptr));
    std::cout << "Found: " << v->number << " (" << typeToString(v->type) << "), owner " << v->owner
              << ", slot " << v->slot << "\n"
              << "Entry: " << formatTime(v->entryTime) << "  |  Duration so far: " << formatDuration(minutes) << "\n";

    std::string ans = readLine("Confirm exit? (y/n): ");
    if (ans != "y" && ans != "Y") { std::cout << "Exit cancelled.\n"; return; }

    Transaction* t = processExit(lot, number);
    if (t) printReceipt(*t);
}
