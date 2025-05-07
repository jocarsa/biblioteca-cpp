#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>

class Database {
private:
    sqlite3* db;
public:
    Database(const std::string& filename);
    ~Database();
    sqlite3* getDB();
};

#endif

