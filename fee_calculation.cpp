#include "fee_calculation.h"
#include "utils.h"
#include "vehicle_exit.h"
#include <iomanip>
#include <iostream>

double hourlyRate(VehicleType t) {
    switch (t) {
        case VehicleType::BIKE:  return 10.0;
        case VehicleType::CAR:   return 20.0;
        case VehicleType::TRUCK: return 40.0;
    }
    return 0.0;
}

long billableHours(long minutes) {
    if (minutes <= 0) return 1;           // minimum charge: 1 hour
    return (minutes + 59) / 60;           // round up
}

double calculateFee(VehicleType t, long minutes) {
    return billableHours(minutes) * hourlyRate(t);
}

void showRateChart() {
    std::cout << "\n===== Parking Rate Chart (per hour) =====\n";
    for (int i = 1; i <= 3; i++) {
        VehicleType t = (VehicleType)i;
        std::cout << "  " << std::left << std::setw(8) << typeToString(t) << std::right
                  << "Rs. " << std::fixed << std::setprecision(2) << hourlyRate(t) << "\n";
    }
    std::cout << "Note: time is rounded up to the next hour. Minimum charge is 1 hour.\n";
}

void estimateFeeInteractive(const ParkingLot& lot) {
    showRateChart();
    std::string number = normalizeNumber(readLine("\nVehicle number to check current fee (blank to skip): "));
    if (number.empty()) return;
    const Vehicle* v = findVehicle(lot, number);
    if (!v) { std::cout << "Vehicle " << number << " is not currently parked.\n"; return; }

    long minutes = parkedMinutes(*v, std::time(nullptr));
    std::cout << "Parked for " << formatDuration(minutes) << " ("
              << billableHours(minutes) << " billable hr) -> Fee so far: Rs. "
              << std::fixed << std::setprecision(2) << calculateFee(v->type, minutes) << "\n";
}
