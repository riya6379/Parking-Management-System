#ifndef VEHICLE_ENTRY_H
#define VEHICLE_ENTRY_H

#include "common.h"

// Module 1: Vehicle Entry Registration
// Registers vehicle number, owner name, vehicle type and records entry time.
// Returns the new Vehicle node, or nullptr (error text in `err`).
Vehicle* registerVehicle(ParkingLot& lot, const std::string& number, const std::string& owner,
                         VehicleType type, std::string& err, std::time_t entryTime = std::time(nullptr));

void registerVehicleInteractive(ParkingLot& lot);

#endif
