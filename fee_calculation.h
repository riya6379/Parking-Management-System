#ifndef FEE_CALCULATION_H
#define FEE_CALCULATION_H

#include "common.h"

// Module 4: Parking Fee Calculation
// Charged per hour (rounded UP), minimum 1 hour. Rate depends on vehicle type.
double hourlyRate(VehicleType t);
long   billableHours(long minutes);
double calculateFee(VehicleType t, long minutes);

void showRateChart();
void estimateFeeInteractive(const ParkingLot& lot);   // fee so far for a parked vehicle

#endif
