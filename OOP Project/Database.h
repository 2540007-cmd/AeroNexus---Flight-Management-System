#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
using namespace std;

class Database {
protected:
    vector<string> records;
public:
    Database();
    virtual ~Database();
    virtual void addRecord(const string& record) = 0;
    virtual void removeRecord(const string& record) = 0;
    virtual vector<string> getRecords() const;
};

#endif // DATABASE_H