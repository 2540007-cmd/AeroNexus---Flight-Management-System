#include <iostream>
#include "Company.h"
#include "FlightDB.h"
#include "PlaneDB.h"
using namespace std;

int main() {
    // Create a company
    Company company("AeroNexus Airlines", "ANX");
    cout << "Company: " << company.getName() << " (" << company.getCode() << ")" << endl;

    // Create databases
    FlightDB flightDB;
    PlaneDB planeDB;

    // Add some records
    flightDB.addRecord("Flight 101: JFK to LAX");
    flightDB.addRecord("Flight 202: ORD to MIA");

    planeDB.addRecord("Boeing 737-800");
    planeDB.addRecord("Airbus A320");

    // Display records
    cout << "Flights:" << endl;
    for (const auto& record : flightDB.getRecords()) {
        cout << "  " << record << endl;
    }

    cout << "Planes:" << endl;
    for (const auto& record : planeDB.getRecords()) {
        cout << "  " << record << endl;
    }

    return 0;
}