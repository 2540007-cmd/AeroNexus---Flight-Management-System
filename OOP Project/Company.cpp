#include "Company.h"
using namespace std;

Company::Company() : name(""), code("") {}

Company::Company(const string& name, const string& code) : name(name), code(code) {}

void Company::setName(const string& name) {
    this->name = name;
}

string Company::getName() const {
    return name;
}

void Company::setCode(const string& code) {
    this->code = code;
}

string Company::getCode() const {
    return code;
}