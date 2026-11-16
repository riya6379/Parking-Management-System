#ifndef COMMON_H
#define COMMON_H

#include <ctime>
#include <string>
#include <vector>

enum class VehicleType { BIKE = 1, CAR = 2, TRUCK = 3 };

// Node of the "currently parked vehicles" linked list
struct Vehicle {
    std::string number;
    std::string owner;
    VehicleType type;
    std::time_t entryTime;
    int slot;              // 1-based slot number
    Vehicle* next;
};

// Node of the "parking history" linked list (one per completed parking)
struct Transaction {
    int receiptNo;
    std::string number;
    std::string owner;
    VehicleType type;
    std::time_t entryTime;
    std::time_t exitTime;
    int slot;
    long minutes;
    double fee;
    Transaction* next;
};

// The whole parking lot
struct ParkingLot {
    int totalSlots = 0;
    std::vector<bool> occupied;     // index 0 -> slot 1
    int occupiedCount = 0;
    Vehicle* vehicles = nullptr;    // active vehicles (linked list)
    Transaction* recHead = nullptr; // history (linked list, oldest first)
    Transaction* recTail = nullptr;
    int nextReceipt = 1;
};

#endif
