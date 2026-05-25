#include "FlightDB.h"
#include <iostream>
using namespace std;

FlightDB::FlightDB(string fname) : Database(fname){
    setCap(); // Set capacity based on file content
    airport = new string[capacity];
    destination = new string[capacity];
    modelno = new string[capacity];
    distance = new float[capacity];
    fuelConsumed = new float[capacity];
    status = new string[capacity];
}
