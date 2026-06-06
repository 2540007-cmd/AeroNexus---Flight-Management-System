#ifndef COMPANY_H
#define COMPANY_H

#include "Database.h"
#include "PlaneDB.h"
#include "FlightDB.h"
#include "RecordDB.h"
#include <string>
using namespace std;

class Company : public Database {
    private:
        int* companyId;
        string* companyName;

        // Dynamic list of PlaneDB objects for this company
        int* planeCount = 0;
        int* no_of_terminals;
        //PlaneDB planeList;
        //FlightDB flightList;
        

        // Record database for this company
        RecordDB** recordlist;

    public:
        Company(string fname);
        void setCap() override;
        void loadData() override;
        void saveData() override;
        void addRecord() override;
        void displayRecords() override;
        void displayPastRecords(int index);
        void displayPlaneRecords(int index);
        void displayFlightRecords(int index);
        void tweakRecords(int index);
        void updateRecord() override;
        void deleteRecord() override;
};

#endif