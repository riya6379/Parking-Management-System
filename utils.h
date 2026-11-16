#ifndef UTILS_H
#define UTILS_H

#include "common.h"
#include <string>

std::string trim(const std::string& s);
std::string normalizeNumber(const std::string& s);   // upper-case, remove spaces and '-'
bool isValidVehicleNumber(const std::string& s);     // after normalizing
std::string typeToString(VehicleType t);
std::string formatTime(std::time_t t);               // DD-MM-YYYY HH:MM
std::string formatDuration(long minutes);            // "2 hr 15 min"
std::string readLine(const std::string& prompt);
int readInt(const std::string& prompt, int lo, int hi);

#endif
