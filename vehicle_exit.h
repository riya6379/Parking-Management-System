#ifndef VEHICLE_EXIT_H
#define VEHICLE_EXIT_H

#include "common.h"

// Module 3: Vehicle Exit Management
// Searches vehicle by number (linked list search), records exit and calculates duration.
Vehicle* findVehicle(const ParkingLot& lot, const std::string& normalizedNumber);
long parkedMinutes(const Vehicle& v, std::time_t now);
Transaction* processExit(ParkingLot& lot, const std::string& number, std::time_t exitTime = std::time(nullptr));
void vehicleExitInteractive(ParkingLot& lot);

#endif
