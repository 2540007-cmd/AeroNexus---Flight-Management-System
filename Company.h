#ifndef COMPANY_H
#define COMPANY_H

#include "PlaneDB.h"
#include "FlightDB.h"
#include "RecordDB.h"
#include <string>
using namespace std;

class Company {
    private:
        int companyId;
        string companyName;

        // Dynamic list of PlaneDB objects for this company
        int planeCount = 0;
        int no_of_terminals;
        PlaneDB planeList;
        FlightDB flightList;
        

        // Record database for this company
        RecordDB recordDB;
};

#endif