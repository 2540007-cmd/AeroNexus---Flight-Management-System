#include "PlaneDB.h"
#include <iostream>
using namespace std;

PlaneDB::PlaneDB(string fname) : Database(fname){
    setCap(); // Set capacity based on file content
    modelNo = new string[capacity];
    serialNo = new int[capacity];
    fuelCapacity = new float[capacity];
    status = new bool[capacity];
}
