// Parking Management System
// DSA Concepts: Singly Linked List (active vehicles + parking history), array-based slot table, linear search

#include "common.h"
#include "fee_calculation.h"
#include "receipt_records.h"
#include "slot_management.h"
#include "utils.h"
#include "vehicle_entry.h"
#include "vehicle_exit.h"
#include <iostream>
#include <string>

static const std::string ACTIVE_FILE  = "parking_active.txt";
static const std::string RECORDS_FILE = "parking_records.txt";
static const int DEFAULT_SLOTS = 20;

static void printMenu() {
    std::cout << "\n========== PARKING MANAGEMENT SYSTEM ==========\n"
              << " 1. Register vehicle entry        (Module 1)\n"
              << " 2. View slot status              (Module 2)\n"
              << " 3. View parked vehicles          (Module 2)\n"
              << " 4. Vehicle exit                  (Module 3)\n"
              << " 5. Rate chart / check current fee(Module 4)\n"
              << " 6. View all parking records      (Module 5)\n"
              << " 7. Search records by vehicle no. (Module 5)\n"
              << " 0. Save & Exit\n"
              << "===============================================\n";
}

int main(int argc, char* argv[]) {
    int slots = DEFAULT_SLOTS;
    if (argc > 1) {
        try { slots = std::stoi(argv[1]); } catch (...) { slots = DEFAULT_SLOTS; }
        if (slots < 1 || slots > 500) slots = DEFAULT_SLOTS;
    }

    ParkingLot lot;
    initLot(lot, slots);
    loadData(lot, ACTIVE_FILE, RECORDS_FILE);
    std::cout << "Parking lot ready: " << lot.totalSlots << " slots, "
              << lot.occupiedCount << " occupied.\n";

    while (true) {
        printMenu();
        int choice = readInt("Enter your choice: ", 0, 7);
        switch (choice) {
            case 1: registerVehicleInteractive(lot); break;
            case 2: displaySlotStatus(lot); break;
            case 3: displayParkedVehicles(lot); break;
            case 4: vehicleExitInteractive(lot); break;
            case 5: estimateFeeInteractive(lot); break;
            case 6: displayAllRecords(lot); break;
            case 7: searchRecordsInteractive(lot); break;
            case 0:
                std::cout << (saveData(lot, ACTIVE_FILE, RECORDS_FILE) ? "Data saved. " : "Could not save data! ")
                          << "Goodbye!\n";
                freeLot(lot);
                return 0;
        }
    }
}
