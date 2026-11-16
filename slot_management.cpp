#include "slot_management.h"
#include "utils.h"
#include <iomanip>
#include <iostream>

void initLot(ParkingLot& lot, int totalSlots) {
    lot.totalSlots = totalSlots;
    lot.occupied.assign(totalSlots, false);
    lot.occupiedCount = 0;
}

int availableSlots(const ParkingLot& lot) {
    return lot.totalSlots - lot.occupiedCount;
}

int allocateSlot(ParkingLot& lot) {
    for (int i = 0; i < lot.totalSlots; i++) {
        if (!lot.occupied[i]) {
            lot.occupied[i] = true;
            lot.occupiedCount++;
            return i + 1;
        }
    }
    return -1;
}

bool occupySlot(ParkingLot& lot, int slot) {
    if (slot < 1 || slot > lot.totalSlots || lot.occupied[slot - 1]) return false;
    lot.occupied[slot - 1] = true;
    lot.occupiedCount++;
    return true;
}

void freeSlot(ParkingLot& lot, int slot) {
    if (slot < 1 || slot > lot.totalSlots || !lot.occupied[slot - 1]) return;
    lot.occupied[slot - 1] = false;
    lot.occupiedCount--;
}

static const Vehicle* vehicleInSlot(const ParkingLot& lot, int slot) {
    for (const Vehicle* v = lot.vehicles; v; v = v->next)
        if (v->slot == slot) return v;
    return nullptr;
}

void displaySlotStatus(const ParkingLot& lot) {
    std::cout << "\n===== Parking Slot Status =====\n"
              << "Total slots     : " << lot.totalSlots << "\n"
              << "Occupied slots  : " << lot.occupiedCount << "\n"
              << "Available slots : " << availableSlots(lot) << "\n\n";

    for (int s = 1; s <= lot.totalSlots; s++) {
        const Vehicle* v = lot.occupied[s - 1] ? vehicleInSlot(lot, s) : nullptr;
        std::cout << "[" << std::right << std::setfill('0') << std::setw(2) << s << std::setfill(' ') << "] "
                  << std::left << std::setw(13) << (v ? v->number : "FREE");
        if (s % 4 == 0 || s == lot.totalSlots) std::cout << "\n";
        else std::cout << " ";
    }
    std::cout << std::right;
}

void displayParkedVehicles(const ParkingLot& lot) {
    if (!lot.vehicles) { std::cout << "\nNo vehicles are currently parked.\n"; return; }
    std::cout << "\n" << std::left
              << std::setw(6) << "Slot" << std::setw(14) << "Vehicle No."
              << std::setw(16) << "Owner" << std::setw(8) << "Type"
              << "Entry Time\n" << std::string(60, '-') << "\n";
    for (const Vehicle* v = lot.vehicles; v; v = v->next) {
        std::cout << std::setw(6) << v->slot << std::setw(14) << v->number
                  << std::setw(16) << v->owner.substr(0, 14) << std::setw(8) << typeToString(v->type)
                  << formatTime(v->entryTime) << "\n";
    }
    std::cout << std::right;
}

void freeLot(ParkingLot& lot) {
    while (lot.vehicles) { Vehicle* n = lot.vehicles->next; delete lot.vehicles; lot.vehicles = n; }
    while (lot.recHead)  { Transaction* n = lot.recHead->next; delete lot.recHead; lot.recHead = n; }
    lot.recTail = nullptr;
}
