#ifndef COMPANY_H
#define COMPANY_H

#include <string>
using namespace std;

class Company {
private:
    string name;
    string code;
public:
    Company();
    Company(const string& name, const string& code);
    void setName(const string& name);
    string getName() const;
    void setCode(const string& code);
    string getCode() const;
};

#endif // COMPANY_H