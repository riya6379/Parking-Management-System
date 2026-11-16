#ifndef SLOT_MANAGEMENT_H
#define SLOT_MANAGEMENT_H

#include "common.h"

// Module 2: Parking Slot Management
void initLot(ParkingLot& lot, int totalSlots);
int  allocateSlot(ParkingLot& lot);          // first free slot (1-based), -1 if full
void freeSlot(ParkingLot& lot, int slot);
bool occupySlot(ParkingLot& lot, int slot);  // used when loading saved data
int  availableSlots(const ParkingLot& lot);
void displaySlotStatus(const ParkingLot& lot);
void displayParkedVehicles(const ParkingLot& lot);
void freeLot(ParkingLot& lot);               // releases all linked-list memory

#endif
