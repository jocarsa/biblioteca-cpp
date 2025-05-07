#include "database.h"
#include <iostream>

Database::Database(const std::string& filename) {
    if (sqlite3_open(filename.c_str(), &db)) {
        std::cerr << "No se puede abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    }
}

Database::~Database() {
    if (db) sqlite3_close(db);
}

sqlite3* Database::getDB() {
    return db;
}

