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

void RecordDB::setCap() {
    Database::setCap(); // Call base class method to set capacity
    capacity += 100; // Add extra space for new records unique to RecordDB
    cout << "Record capacity set to: " << capacity << endl;
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
    cout << "Enter Flight Status ( 1 for Scheduled, 2 for Completed, 3 for Cancelled): ";
    int x;
    cin >> x;
    switch (x) {
        case 1:
            status[pointer] = "Scheduled";
            break;
        case 2:
            status[pointer] = "Completed";
            break;
        case 3:
            status[pointer] = "Cancelled";
            break;
        default:
            cout << "Invalid input for status. Setting to 'Scheduled' by default." << endl;
            status[pointer] = "Scheduled";
    }
    cout << "Record added successfully." << endl;
    pointer++;                  // Increment temporary pointer for new record
}

void RecordDB::saveData() {
    ofstream file("Data_Dependancy/Company_Records/temp.csv");
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
    rename("Data_Dependancy/Company_Records/temp.csv", fileName.c_str()); // Replace old file with new file
    cout << "Data saved successfully to " << fileName << endl;
}

void RecordDB::displayRecords() {
    cout << "\n========== CURRENT RECORDS ==========\n";

    for (int i = 0; i < pointer; i++) {
        cout << "\nRecord #" << (i + 1) << endl;
        cout << "----------------------------------" << endl;
        cout << "Airport      : " << airport[i] << endl;
        cout << "Destination  : " << destination[i] << endl;
        cout << "Model Number : " << modelno[i] << endl;
        cout << "Distance     : " << distance[i] << " km" << endl;
        cout << "Fuel Used    : " << fuelConsumed[i] << " liters" << endl;
        cout << "Status       : " << status[i] << endl;
    }

    cout << "\n=====================================\n";
}
void RecordDB::updateRecord() {
    cout << "updateRecord() is not implemented yet." << endl;
}

void RecordDB::deleteRecord() {
    cout << "deleteRecord() is not implemented yet." << endl;
}