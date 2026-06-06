#include "FlightDB.h"
#include <iostream>
using namespace std;

FlightDB::FlightDB(string fname, int cap) : Database(fname){
    capacity = cap; // Set capacity based on provided argument
    airport = new string[capacity];
    destination = new string[capacity];
    modelno = new string[capacity];
    distance = new float[capacity];
    fuelConsumed = new float[capacity];
    status = new string[capacity];
}
