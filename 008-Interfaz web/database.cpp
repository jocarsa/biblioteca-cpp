#include "database.h"
#include <iostream>

Database::Database(const std::string& filename) {
    if (sqlite3_open(filename.c_str(), &db)) {
        std::cerr << "No se puede abrir la base de datos: "
                  << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    } else {
        // Habilitar comprobación de claves externas
        char* errMsg = nullptr;
        if (sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, &errMsg) != SQLITE_OK) {
            std::cerr << "Error al habilitar foreign_keys: "
                      << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }
}

Database::~Database() {
    if (db) sqlite3_close(db);
}

sqlite3* Database::getDB() {
    return db;
}

