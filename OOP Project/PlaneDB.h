#ifndef PLANEDB_H
#define PLANEDB_H

#include "Database.h"
#include <string>
using namespace std;

class PlaneDB : public Database{
    private:
        string* modelNo;       // Plane model number/name
        int* serialNo;         // Plane serial number
        float* fuelCapacity;   // Plane fuel capacity
        bool* status;          // true = available, false = unavailable/busy

    public:
        PlaneDB(string fname);
        void loadData() override;
        void saveData() override;
        void addRecord() override;
        void displayRecords() override;
        void updateRecord() override;
        void deleteRecord() override;
};

#endif
