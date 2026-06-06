#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "RecordDB.h"
#include "User.h"

using namespace std;

int main() {
    RecordDB records("records.csv");
    User profile;
    string fileName = "User.csv";
    bool login = false;

    int choice;
    do {
        cout << "1. ========== Login ==========" << endl;
        cout << "2. ========== Sign Up ========" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the input buffer

        
        if (choice == 1) {
            string inputUsername, inputPassword;
            cout << "Enter Username: ";
            getline(cin, inputUsername);
            cout << "Enter Password: ";
            getline(cin, inputPassword);

            ifstream file(fileName);
            if (!file.is_open()) {
                cerr << "Error Connecting to the DataBase: " << fileName << endl;
                break;
            }
            string line;
            string data;
            
            while (getline(file, line)) {
                if (profile.Login(line, inputUsername, inputPassword)) {
                    profile = profile.toUser(line); // Convert the line to a User object and store in profile
                    cout << "Login successful! Welcome, " << profile.getUsername() << "!" << endl;
                    login = true;
                    break;
                }
            }
            if (!login) {
                cout << "This User name and password combination does not exist." << endl;
                cout << "Please try again or Sign Up to create a new account." << endl;
            }
            file.close();
        } else if (choice == 2) {
            profile.initializeUser(); // Create a new user profile
            cout << "User created successfully! Automatic Login Successful." << endl;
            login = true;
            ofstream file(fileName);
            if (!file.is_open()) {
                cerr << "Error Connecting to the DataBase: Login info was not saved to DataBase!" << fileName << endl;
            } else {
                file << profile.toCSV() << endl;
                file.close();
            }

        } else {
            cout << "Invalid choice. Please enter 1 for Login or 2 for Sign Up." << endl;
        }
    } while((choice != 1 && choice != 2) || (!login)); // Loop until valid input is received or Login is successful

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