#include "utils.h"
#include <cctype>
#include <cstdlib>
#include <iostream>

std::string trim(const std::string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == std::string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

std::string normalizeNumber(const std::string& s) {
    std::string out;
    for (char c : s) {
        if (c == ' ' || c == '-') continue;
        out += (char)std::toupper((unsigned char)c);
    }
    return out;
}

bool isValidVehicleNumber(const std::string& s) {
    if (s.size() < 4 || s.size() > 12) return false;
    for (char c : s)
        if (!std::isalnum((unsigned char)c)) return false;
    return true;
}

std::string typeToString(VehicleType t) {
    switch (t) {
        case VehicleType::BIKE:  return "Bike";
        case VehicleType::CAR:   return "Car";
        case VehicleType::TRUCK: return "Truck";
    }
    return "Unknown";
}

std::string formatTime(std::time_t t) {
    std::tm* lt = std::localtime(&t);
    char buf[32];
    std::strftime(buf, sizeof(buf), "%d-%m-%Y %H:%M", lt);
    return buf;
}

std::string formatDuration(long minutes) {
    if (minutes < 0) minutes = 0;
    return std::to_string(minutes / 60) + " hr " + std::to_string(minutes % 60) + " min";
}

std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    if (!std::getline(std::cin, s)) {
        std::cout << "\nInput ended. Exiting.\n";
        std::exit(0);
    }
    return trim(s);
}

int readInt(const std::string& prompt, int lo, int hi) {
    while (true) {
        std::string s = readLine(prompt);
        try {
            size_t pos;
            int v = std::stoi(s, &pos);
            if (pos == s.size() && v >= lo && v <= hi) return v;
        } catch (...) {}
        std::cout << "  Invalid input. Enter a number between " << lo << " and " << hi << ".\n";
    }
}
