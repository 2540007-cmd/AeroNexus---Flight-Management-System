#include "RecordDB.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
using namespace std;
RecordDB::RecordDB(string fname) : Database(fname){
    setCap(); // Set capacity based on file content

    airport = new string[capacity];
    destination = new string[capacity];
    modelno = new string[capacity];
    distance = new float[capacity];
    fuelConsumed = new float[capacity];
    status = new string[capacity];

    loadData(); // Load existing data from the file
}

void RecordDB::loadData() {
    // Implement file reading logic to populate the record database
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error opening file: " << fileName << endl;
        return;
    }
    string line;
    string data;
    bool emptylines = false;
    int index = 0;
    while (getline(file, line)) {
        if (line == ""){
            emptylines = true;
            continue; // Skip empty lines
        }
        stringstream ss(line);

        getline(ss, data, ',');
        airport[index] = data;

        getline(ss, data, ',');
        destination[index] = data;

        getline(ss, data, ',');
        modelno[index] = data;

        getline(ss, data, ',');
        distance[index] = stof(data);

        getline(ss, data, ',');
        fuelConsumed[index] = stof(data);

        getline(ss, data, ',');
        status[index] = data;

        index++;
    }
    pointer = index; // Set pointer to the number of records loaded
    file.close();
    if (emptylines) {
        cout << "Warning: Empty lines were found and skipped in the file." << endl;
        cout << "Correcting file by removing empty lines..." << endl;
        removeEmptyLines(); // Remove empty lines from the file
        cout << "Empty lines removed and file corrected." << endl;
    }
    
    cout << "Data loaded successfully from " << fileName << endl;
}

void RecordDB::addRecord() {
    if (pointer >= capacity) {
        cout << "Database is full. Cannot add more records." << endl;
        return;
    }
    cout << "Enter Starting Airport: ";
    getline(cin, airport[pointer]);
    cout << "Enter Destination Airport: ";
    getline(cin, destination[pointer]);
    cout << "Enter Plane Model Number: ";
    getline(cin, modelno[pointer]);
    cout << "Enter Flight Distance: ";
    cin >> distance[pointer];
    cout << "Enter Fuel Consumed: ";
    cin >> fuelConsumed[pointer];
    cin.ignore(); // Clear the input buffer
    cout << "Enter Flight Status (Scheduled, Completed, Cancelled): ";
    getline(cin, status[pointer]);
    cout << "Record added successfully." << endl;
    pointer++;                  // Increment temporary pointer for new record
}

void RecordDB::saveData() {
    ofstream file("temp.csv");
    if (!file.is_open()) {
        cerr << "Error opening file for writing: " << fileName << endl;
        return;
    }
    for (int i = 0; i < pointer; i++) {
        file << airport[i] << ","
             << destination[i] << ","
             << modelno[i] << ","
             << distance[i] << ","
             << fuelConsumed[i] << ","
             << status[i] << endl;
    }
    file.close();
    remove(fileName.c_str()); // Remove old file
    rename("temp.csv", fileName.c_str()); // Replace old file with new file
    cout << "Data saved successfully to " << fileName << endl;
}

void RecordDB::displayRecords() {
    cout << "Current Records in the Database:" << endl;
    for (int i = 0; i < pointer; i++) {
        cout << "Record " << (i + 1) << ": "
             << airport[i] << " -> "
             << destination[i] << ", Model: "
             << modelno[i] << ", Distance: "
             << distance[i] << " km, Fuel: "
             << fuelConsumed[i] << " liters, Status: "
             << status[i] << endl;
    }
}
void RecordDB::updateRecord() {
    cout << "updateRecord() is not implemented yet." << endl;
}

void RecordDB::deleteRecord() {
    cout << "deleteRecord() is not implemented yet." << endl;
}