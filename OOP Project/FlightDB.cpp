#include "FlightDB.h"
using namespace std;

FlightDB::FlightDB() {}

void FlightDB::addRecord(const string& record) {
    records.push_back(record);
}

void FlightDB::removeRecord(const string& record) {
    // Simple implementation, remove first occurrence
    for (auto it = records.begin(); it != records.end(); ++it) {
        if (*it == record) {
            records.erase(it);
            break;
        }
    }
}