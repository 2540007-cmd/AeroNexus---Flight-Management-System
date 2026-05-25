#include <iostream>
#include "RecordDB.h"

using namespace std;

int main() {
    RecordDB records("records.csv");

    int choice;

    do
    {
        cout << "\n========== RecordDB Test Menu ==========" << endl;
        cout << "1. Display Records" << endl;
        cout << "2. Add Record" << endl;
        cout << "3. Save Data" << endl;
        cout << "4. Reload Data" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            records.displayRecords();
            break;

        case 2:
            records.addRecord();
            break;

        case 3:
            records.saveData();
            break;

        case 4:
            records.loadData();
            break;

        case 0:
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != 0);

    return 0;
}
