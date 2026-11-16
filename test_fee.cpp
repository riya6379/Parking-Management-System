// Simple unit tests for the fee calculation module
#include "../src/fee_calculation.h"
#include <cassert>
#include <iostream>

int main() {
    assert(billableHours(0)   == 1);   // minimum 1 hour
    assert(billableHours(1)   == 1);
    assert(billableHours(60)  == 1);
    assert(billableHours(61)  == 2);   // rounded up
    assert(billableHours(150) == 3);

    assert(calculateFee(VehicleType::BIKE, 30)   == 10.0);
    assert(calculateFee(VehicleType::CAR, 150)   == 60.0);   // 3 hr * 20
    assert(calculateFee(VehicleType::TRUCK, 121) == 120.0);  // 3 hr * 40

    std::cout << "All fee calculation tests passed.\n";
    return 0;
}
