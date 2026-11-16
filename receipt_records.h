#ifndef RECEIPT_RECORDS_H
#define RECEIPT_RECORDS_H

#include "common.h"

// Module 5: Receipt Generation and Parking Records
Transaction* addTransaction(ParkingLot& lot, const Vehicle& v, std::time_t exitTime, long minutes, double fee);
void printReceipt(const Transaction& t);
void displayAllRecords(const ParkingLot& lot);
void searchRecordsInteractive(const ParkingLot& lot);

// Persistence (data survives program restarts)
bool saveData(const ParkingLot& lot, const std::string& activeFile, const std::string& recordsFile);
void loadData(ParkingLot& lot, const std::string& activeFile, const std::string& recordsFile);

#endif
