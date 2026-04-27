#ifndef FLIGHTDB_H
#define FLIGHTDB_H

#include "Database.h"
#include <string>
using namespace std;

class FlightDB : public Database {
private:
    // Additional members specific to flights
public:
    FlightDB();
    void addRecord(const string& record) override;
    void removeRecord(const string& record) override;
    // Additional methods for flight management
};

#endif // FLIGHTDB_H