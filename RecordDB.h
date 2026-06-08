#ifndef RECORDDB_H
#define RECORDDB_H

#include "Database.h"
#include <string>
using namespace std;

class RecordDB : public Database {
    protected:
        string* airport;        // Starting airport
        string* destination;    // Destination airport

        string* modelno;     // Plane model number used in this flight

        float* distance;        // Flight distance
        float* fuelConsumed;    // Fuel consumed during flight

        string* status;         // Scheduled, Completed, Cancelled

    public:
        RecordDB(string fname);
        void setCap() override;
        void loadData() override;
        void saveData() override;
        void addRecord() override;
        void displayRecords() override;
        void updateRecord(int index) override;
        void deleteRecord(int index) override;
};

#endif