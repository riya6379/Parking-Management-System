#include "receipt_records.h"
#include "slot_management.h"
#include "utils.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

Transaction* addTransaction(ParkingLot& lot, const Vehicle& v, std::time_t exitTime, long minutes, double fee) {
    Transaction* t = new Transaction{lot.nextReceipt++, v.number, v.owner, v.type,
                                     v.entryTime, exitTime, v.slot, minutes, fee, nullptr};
    if (!lot.recHead) lot.recHead = lot.recTail = t;
    else { lot.recTail->next = t; lot.recTail = t; }
    return t;
}

void printReceipt(const Transaction& t) {
    std::cout << "\n+--------------------------------------+\n"
              << "|         PARKING RECEIPT              |\n"
              << "+--------------------------------------+\n"
              << " Receipt No   : " << t.receiptNo << "\n"
              << " Vehicle No   : " << t.number << "\n"
              << " Owner        : " << t.owner << "\n"
              << " Vehicle Type : " << typeToString(t.type) << "\n"
              << " Slot         : " << t.slot << "\n"
              << " Entry Time   : " << formatTime(t.entryTime) << "\n"
              << " Exit Time    : " << formatTime(t.exitTime) << "\n"
              << " Duration     : " << formatDuration(t.minutes) << "\n"
              << " Total Fee    : Rs. " << std::fixed << std::setprecision(2) << t.fee << "\n"
              << "+--------------------------------------+\n"
              << "     Thank you! Drive safely.\n";
}

static void printRecordHeader() {
    std::cout << "\n" << std::left
              << std::setw(6) << "Rcpt" << std::setw(14) << "Vehicle No." << std::setw(8) << "Type"
              << std::setw(18) << "Entry" << std::setw(18) << "Exit"
              << std::setw(14) << "Duration" << "Fee (Rs.)\n" << std::string(88, '-') << "\n";
}

static void printRecordRow(const Transaction* t) {
    std::cout << std::left << std::setw(6) << t->receiptNo << std::setw(14) << t->number
              << std::setw(8) << typeToString(t->type)
              << std::setw(18) << formatTime(t->entryTime) << std::setw(18) << formatTime(t->exitTime)
              << std::setw(14) << formatDuration(t->minutes)
              << std::fixed << std::setprecision(2) << t->fee << "\n";
}

void displayAllRecords(const ParkingLot& lot) {
    if (!lot.recHead) { std::cout << "\nNo parking records yet.\n"; return; }
    printRecordHeader();
    int n = 0;
    double total = 0;
    for (const Transaction* t = lot.recHead; t; t = t->next) { printRecordRow(t); n++; total += t->fee; }
    std::cout << std::string(88, '-') << "\nTotal records: " << n
              << "   |   Total collection: Rs. " << std::fixed << std::setprecision(2) << total << "\n";
}

void searchRecordsInteractive(const ParkingLot& lot) {
    std::string key = normalizeNumber(readLine("Enter vehicle number to search records: "));
    if (key.empty()) { std::cout << "Vehicle number cannot be empty.\n"; return; }
    int n = 0;
    for (const Transaction* t = lot.recHead; t; t = t->next) {
        if (t->number != key) continue;
        if (n == 0) printRecordHeader();
        printRecordRow(t);
        n++;
    }
    if (n == 0) std::cout << "No records found for " << key << ".\n";
    else std::cout << n << " record(s) found.\n";
}

// ---------- persistence ----------
// parking_active.txt  : number|owner|type|entryEpoch|slot
// parking_records.txt : receiptNo|number|owner|type|entryEpoch|exitEpoch|slot|minutes|fee
bool saveData(const ParkingLot& lot, const std::string& activeFile, const std::string& recordsFile) {
    std::ofstream a(activeFile), r(recordsFile);
    if (!a || !r) return false;
    for (const Vehicle* v = lot.vehicles; v; v = v->next)
        a << v->number << '|' << v->owner << '|' << (int)v->type << '|' << (long long)v->entryTime << '|' << v->slot << '\n';
    for (const Transaction* t = lot.recHead; t; t = t->next)
        r << t->receiptNo << '|' << t->number << '|' << t->owner << '|' << (int)t->type << '|'
          << (long long)t->entryTime << '|' << (long long)t->exitTime << '|' << t->slot << '|'
          << t->minutes << '|' << t->fee << '\n';
    return true;
}

static std::vector<std::string> splitLine(const std::string& line) {
    std::vector<std::string> parts;
    std::stringstream ss(line);
    std::string item;
    while (std::getline(ss, item, '|')) parts.push_back(item);
    return parts;
}

void loadData(ParkingLot& lot, const std::string& activeFile, const std::string& recordsFile) {
    std::string line;

    std::ifstream a(activeFile);
    Vehicle* tail = nullptr;
    while (a && std::getline(a, line)) {
        auto p = splitLine(line);
        if (p.size() != 5) continue;
        try {
            int type = std::stoi(p[2]);
            if (type < 1 || type > 3) continue;
            int slot = std::stoi(p[4]);
            if (!occupySlot(lot, slot)) {          // saved slot invalid/taken -> give a new one
                slot = allocateSlot(lot);
                if (slot == -1) continue;
            }
            Vehicle* v = new Vehicle{p[0], p[1], (VehicleType)type, (std::time_t)std::stoll(p[3]), slot, nullptr};
            if (!tail) lot.vehicles = v; else tail->next = v;
            tail = v;
        } catch (...) { continue; }
    }

    std::ifstream r(recordsFile);
    int maxReceipt = 0;
    while (r && std::getline(r, line)) {
        auto p = splitLine(line);
        if (p.size() != 9) continue;
        try {
            int type = std::stoi(p[3]);
            if (type < 1 || type > 3) continue;
            Transaction* t = new Transaction{std::stoi(p[0]), p[1], p[2], (VehicleType)type,
                                             (std::time_t)std::stoll(p[4]), (std::time_t)std::stoll(p[5]),
                                             std::stoi(p[6]), std::stol(p[7]), std::stod(p[8]), nullptr};
            if (!lot.recHead) lot.recHead = lot.recTail = t;
            else { lot.recTail->next = t; lot.recTail = t; }
            if (t->receiptNo > maxReceipt) maxReceipt = t->receiptNo;
        } catch (...) { continue; }
    }
    lot.nextReceipt = maxReceipt + 1;
}
