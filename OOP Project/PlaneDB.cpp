#include "PlaneDB.h"
using namespace std;

PlaneDB::PlaneDB() {}

void PlaneDB::addRecord(const string& record) {
    records.push_back(record);
}

void PlaneDB::removeRecord(const string& record) {
    // Simple implementation, remove first occurrence
    for (auto it = records.begin(); it != records.end(); ++it) {
        if (*it == record) {
            records.erase(it);
            break;
        }
    }
}