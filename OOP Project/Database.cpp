#include "Database.h"
using namespace std;

Database::Database() {}

Database::~Database() {}

vector<string> Database::getRecords() const {
    return records;
}