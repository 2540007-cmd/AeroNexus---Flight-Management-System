#include "Company.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

Company::Company(string fname) : Database(fname) {
    setCap(); // Set capacity based on file content

    companyId = new int[capacity];
    companyName = new string[capacity];
    planeCount = new int[capacity];
    no_of_terminals = new int[capacity];

    loadData(); // Load existing data from the file

    recordlist = new RecordDB*[capacity];

    for(int i = 0; i < capacity; i++) {
        recordlist[i] = nullptr;
    }

    recordlist = new RecordDB*[capacity]; // Initialize the array of record databases for the entire companyDB
    for(int i = 0; i < pointer; i++) {
        recordlist[i] = new RecordDB("Data_Dependancy/Company_Records/" + companyName[i] + "_records.csv"); // Initialize each record database with their won unique file name based on the company name
    }
}

void Company::setCap() {
    Database::setCap();
    capacity += 10; // Add extra space for company-specific records
    cout << "Company capacity set to: " << capacity << endl;
}

void Company::loadData() {
    // Implement file reading logic to populate the company database
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
        companyId[index] = stoi(data);

        getline(ss, data, ',');
        companyName[index] = data;

        getline(ss, data, ',');
        planeCount[index] = stoi(data);

        getline(ss, data, ',');
        no_of_terminals[index] = stoi(data);
        
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

void Company::saveData() {
    ofstream file("Data_Dependancy/temp.csv");
    if (!file.is_open()) {
        cerr << "Error opening file for writing: " << fileName << endl;
        return;
    }
    for (int i = 0; i < pointer; i++) {
        file << companyId[i] << ","
             << companyName[i] << ","
             << planeCount[i] << ","
             << no_of_terminals[i] << endl;
    }
    file.close();
    remove(fileName.c_str()); // Remove old file
    rename("Data_Dependancy/temp.csv", fileName.c_str()); // Replace old file with new file
    cout << "Data saved successfully to " << fileName << endl;
}

void Company::addRecord() {
    if (pointer >= capacity) {
        cout << "Company database is full. Cannot add more records. Try again later!" << endl;
        return;
    }
    
    companyId[pointer] = pointer + 1; // Assign a new company ID based on the current pointer

    cout << "Enter Company Name: ";
    getline(cin, companyName[pointer]);
    cout << "Enter Number of Planes: ";
    cin >> planeCount[pointer];
    cout << "Enter Number of Terminals: ";
    cin >> no_of_terminals[pointer];
    
    // Initialize a new record database for this company
    recordlist[pointer] = new RecordDB("Data_Dependancy/Company_Records/" + companyName[pointer] + "_records.csv");
    
    cout << "Company record added successfully." << endl;
    pointer++; // Increment pointer for new record
}
void Company::displayRecords() {
    cout << "\n========== CURRENT Companies ==========" << endl;
    for (int i = 0; i < pointer; i++) {
        cout << "ID: " << companyId[i] << endl
             << "Name: " << companyName[i] << endl
             << "Planes: " << planeCount[i] << endl
             << "Terminals: " << no_of_terminals[i] << endl;
    }
    cout << "\n=====================================\n" << endl;
}
void Company::displayPastRecords(int index) {
    cout << "\n--- Past Flight Records for Company: " << companyName[index] << " ---" << endl;
    recordlist[index]->displayRecords(); // Display records for the specified company's record database
}

void Company::tweakRecords(int index) {
    int choice;

    do {
        cout << "\n========== RECORD MENU ==========\n";
        cout << "Company: " << companyName[index] << endl;
        cout << "\t1. Display Records\n";
        cout << "\t2. Add Record\n";
        cout << "\t3. Update Record\n";
        cout << "\t4. Delete Record\n";
        cout << "\t5. Save Records\n";
        cout << "\t0. Return\n";
        
        cout << "Enter choice: ";

        cin >> choice;
        cin.ignore();
        switch(choice)
        {
            case 1:
                recordlist[index]->displayRecords();
                break;

            case 2:
                recordlist[index]->addRecord();
                break;

            case 3:
                recordlist[index]->updateRecord();
                break;

            case 4:
                recordlist[index]->deleteRecord();
                break;

            case 5:
                recordlist[index]->saveData();
                break;

            case 0:
                cout << "Returning..." << endl;
                break;

            default:
                cout << "Invalid choice." << endl;
        }

    } while(choice != 0);

}
void Company::updateRecord() {
    // Implement logic to update a company record
}
void Company::deleteRecord() {
    // Implement logic to delete a company record
}