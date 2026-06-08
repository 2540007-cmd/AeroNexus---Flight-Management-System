#include "FlightDB.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

FlightDB::FlightDB(string fname, int cap) : Database(fname){
    capacity = cap; // Set capacity based on provided argument
    airport = new string[capacity];
    destination = new string[capacity];
    modelno = new string[capacity];
    distance = new float[capacity];
    fuelConsumed = new float[capacity];
    status = new string[capacity];

    ifstream file(fileName);
    if (!file.is_open()) {
        cout << fileName
             << " not found. Creating new file..."
             << endl;

        ofstream file(fileName);
        file.close();

        pointer = 0;
        return;
    }
}

void FlightDB::loadData() {
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
        cout << "Warning: Empty lines were found and skipped and now removed from the file." << endl;
        removeEmptyLines(); // Remove empty lines from the file
    }
    cout << "Data loaded successfully from " << fileName << endl;
}

void FlightDB::saveData() {
    ofstream file("Data_Dependancy/Company_Flights/temp.csv");
    if (!file.is_open()) {
        cerr << "Error opening file" << fileName << endl;
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
    rename("Data_Dependancy/Company_Flights/temp.csv", fileName.c_str()); // Replace old file with new file
    cout << "Data saved successfully to " << fileName << endl;
}

void FlightDB::addRecord() {
    if (pointer >= capacity) {
        cout << "All terminals are in use. Cannot schedule more Flights today." << endl;
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
    cin.ignore(); // Clear the input buffer after reading numeric input
    status[pointer] = "Scheduled"; // Set default status to Scheduled for new records
    cout << "Record added successfully." << endl;
    pointer++;                  // Increment temporary pointer for new record
}

void FlightDB::updateRecord() {
    // Implement logic to update an existing record based on user input
}
void FlightDB::deleteRecord() {
    // Implement logic to delete a record based on user input
}