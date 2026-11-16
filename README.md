# Parking Management System (C++)

A console-based Parking Management System that manages vehicle entry, slot allocation, exit, fee calculation, receipt generation and parking history. Built with a **Linked List** based design in C++17.

## Features
- Register vehicles with number, owner name, type (Bike / Car / Truck) and automatic entry time
- Automatic slot allocation (first free slot) with live slot status map
- Vehicle exit by number search with parking-duration calculation
- Fee calculation by vehicle type and duration (hourly, rounded up, minimum 1 hour)
- Printed receipt for every exit and a full history of past parkings with total collection
- Search parking history by vehicle number
- Data is saved to text files, so the parking lot state survives restarts
- Input validation (duplicate vehicles, invalid numbers, full lot, wrong menu input)

## Modules
| # | Module | Files | Functionality |
|---|---|---|---|
| 1 | Vehicle Entry Registration | `vehicle_entry.*` | Register vehicle number, owner name, vehicle type and record entry time |
| 2 | Parking Slot Management | `slot_management.*` | Total / occupied / available slots, slot allocation and release |
| 3 | Vehicle Exit Management | `vehicle_exit.*` | Search vehicle by number, record exit, calculate parking duration |
| 4 | Parking Fee Calculation | `fee_calculation.*` | Charges by vehicle type and duration |
| 5 | Receipt Generation & Parking Records | `receipt_records.*` | Final receipt, previous transactions, search, file save/load |

Shared code: `common.h` (data structures), `utils.*` (validation, time formatting, input helpers), `main.cpp` (menu).

## Data Structures Used
| Structure | Used for | Complexity |
|---|---|---|
| Singly linked list | Currently parked vehicles | Insert O(n) at tail, search/remove O(n) |
| Singly linked list (head + tail) | Parking history / receipts | Insert O(1) |
| Boolean slot table (array) | Slot occupancy | Allocate O(n), release O(1) |
| Linear search | Find vehicle by number | O(n) |

## Parking Rates
| Vehicle | Rate per hour |
|---|---|
| Bike | Rs. 10 |
| Car | Rs. 20 |
| Truck | Rs. 40 |

Time is rounded **up** to the next hour, minimum charge is 1 hour. Example: a car parked for 2 hr 30 min pays 3 x 20 = Rs. 60.
Rates can be changed in `hourlyRate()` in `src/fee_calculation.cpp`.

## Project Structure
```
parking-management-system/
├── src/
│   ├── main.cpp
│   ├── common.h
│   ├── utils.h / utils.cpp
│   ├── vehicle_entry.h / .cpp       (Module 1)
│   ├── slot_management.h / .cpp     (Module 2)
│   ├── vehicle_exit.h / .cpp        (Module 3)
│   ├── fee_calculation.h / .cpp     (Module 4)
│   └── receipt_records.h / .cpp     (Module 5)
├── tests/
│   └── test_fee.cpp
├── Makefile
├── .gitignore
└── README.md
```

## Build and Run
Requires a C++17 compiler (g++ / clang++).

```bash
make              # build
./parking_system  # default: 20 slots
./parking_system 50   # custom number of slots
make test         # run fee calculation tests
```

Without `make`:
```bash
g++ -std=c++17 -o parking_system src/*.cpp
```
On Windows (MinGW): `g++ -std=c++17 -o parking_system.exe src/*.cpp`

## Sample Receipt
```
+--------------------------------------+
|         PARKING RECEIPT              |
+--------------------------------------+
 Receipt No   : 1
 Vehicle No   : RJ14CD5678
 Owner        : Ramesh Kumar
 Vehicle Type : Car
 Slot         : 3
 Entry Time   : 16-11-2026 13:45
 Exit Time    : 16-11-2026 16:15
 Duration     : 2 hr 30 min
 Total Fee    : Rs. 60.00
+--------------------------------------+
```

## Team
| Member | Module |
|---|---|
| Member 1 | Vehicle Entry Registration |
| Member 2 | Parking Slot Management |
| Member 3 | Vehicle Exit Management |
| Member 4 | Parking Fee Calculation |
| Member 5 | Receipt Generation & Parking Records |

## Future Improvements
- Separate rates for first hour / daily maximum
- Reserved and handicapped slots
- GUI or web front-end
- Database storage instead of text files
