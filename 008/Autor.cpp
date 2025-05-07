#include "Autor.h"
#include <sqlite3.h>
#include <iostream>

Autor::Autor(int id, const std::string& nom, const std::string& ape)
    : id_autor(id), nombre(nom), apellidos(ape) {}

int Autor::getId() const { return id_autor; }
std::string Autor::getNombreCompleto() const { return nombre + " " + apellidos; }

bool Autor::crear(Database& db, const std::string& nom, const std::string& ape) {
    const char* sql = "INSERT INTO autor(nombre, apellidos) VALUES(?,?);";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error INSERT autor: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, nom.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, ape.c_str(), -1, SQLITE_STATIC);
    bool ok = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return ok;
}

std::vector<Autor> Autor::listar(Database& db) {
    std::vector<Autor> lista;
    const char* sql = "SELECT id_autor, nombre, apellidos FROM autor;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error SELECT autor: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return lista;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* nom = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* ape = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        lista.emplace_back(id, nom, ape);
    }
    sqlite3_finalize(stmt);
    return lista;
}

bool Autor::actualizar(Database& db, int id, const std::string& nom, const std::string& ape) {
    const char* sql = "UPDATE autor SET nombre=?, apellidos=? WHERE id_autor=?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error UPDATE autor: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, nom.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, ape.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, id);
    bool ok = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return ok;
}

bool Autor::eliminar(Database& db, int id) {
    const char* sql = "DELETE FROM autor WHERE id_autor=?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error DELETE autor: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, id);
    bool ok = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return ok;
}
