#include "Database.h"
#include <iostream>
#include <fstream>
using namespace std;

Database::Database(string fname){
    fileName = fname;
    capacity = 0;
    pointer = 0;
}
void Database::setCap() {
    string line;
    int cap = 0;
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << fileName << endl;
        capacity = 100;   // default empty capacity
        return;
    }
    while (getline(file, line)) {
        if (line != "") {
            cap++;
        }
    }
    pointer = cap; // Set pointer to the number of records read

    file.close();
    capacity = cap + 100; 
    cout << "Capacity set to: " << capacity << endl;
}

void Database::removeEmptyLines() {
    string line;
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << fileName << endl;
        return;
    }
    ofstream tempFile("temp.csv");
    while (getline(file, line)) {
        if (line != "") {
            tempFile << line << endl;
        }
    }
    file.close();
    tempFile.close();
    remove(fileName.c_str());
    rename("temp.csv", fileName.c_str());
    setCap(); // Reset capacity after removing empty lines
}
