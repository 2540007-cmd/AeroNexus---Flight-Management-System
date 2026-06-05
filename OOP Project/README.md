# AeroNexus Flight Management System

This is a simple Object-Oriented Programming project implementing a flight management system using C++.

## Classes

- **Company**: Represents an airline company with name and code.
- **Database**: Abstract base class for databases.
- **FlightDB**: Derived class for managing flight records.
- **PlaneDB**: Derived class for managing plane records.

## Files

- `Company.h` / `Company.cpp`: Company class implementation.
- `Database.h` / `Database.cpp`: Database base class.
- `FlightDB.h` / `FlightDB.cpp`: Flight database.
- `PlaneDB.h` / `PlaneDB.cpp`: Plane database.
- `main.cpp`: Main program demonstrating the classes.

## Building and Running

To compile and run on Windows:

1. Ensure you have a C++ compiler like g++ or Visual Studio.
2. Compile: `g++ main.cpp Company.cpp Database.cpp FlightDB.cpp PlaneDB.cpp RecordDB.cpp User.cpp -o AeroNexus`
3. Run: `./AeroNexus`

## Usage

The main program creates a company and sample flight and plane records, then displays them.
