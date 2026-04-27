#ifndef PLANEDB_H
#define PLANEDB_H

#include "Database.h"
#include <string>
using namespace std;

class PlaneDB : public Database {
private:
    // Additional members specific to planes
public:
    PlaneDB();
    void addRecord(const string& record) override;
    void removeRecord(const string& record) override;
    // Additional methods for plane management
};

#endif // PLANEDB_H