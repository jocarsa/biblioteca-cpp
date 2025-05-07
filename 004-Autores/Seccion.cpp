#include "Seccion.h"
#include <sqlite3.h>
#include <iostream>

Seccion::Seccion(int id, const std::string& nombre)
    : id_seccion(id), nombre(nombre) {}

int Seccion::getId() const {
    return id_seccion;
}

std::string Seccion::getNombre() const {
    return nombre;
}

bool Seccion::crear(Database& db, const std::string& nombre) {
    const char* sql = "INSERT INTO seccion(nombre) VALUES(?);";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparando INSERT: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, nombre.c_str(), -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error ejecutando INSERT: " << sqlite3_errmsg(db.getDB()) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}

std::vector<Seccion> Seccion::listar(Database& db) {
    std::vector<Seccion> lista;
    const char* sql = "SELECT id_seccion, nombre FROM seccion;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparando SELECT: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return lista;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* txt = sqlite3_column_text(stmt, 1);
        lista.emplace_back(id, reinterpret_cast<const char*>(txt));
    }
    sqlite3_finalize(stmt);
    return lista;
}

bool Seccion::actualizar(Database& db, int id, const std::string& nuevoNombre) {
    const char* sql = "UPDATE seccion SET nombre = ? WHERE id_seccion = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparando UPDATE: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, nuevoNombre.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, id);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error ejecutando UPDATE: " << sqlite3_errmsg(db.getDB()) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}

bool Seccion::eliminar(Database& db, int id) {
    const char* sql = "DELETE FROM seccion WHERE id_seccion = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparando DELETE: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, id);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error ejecutando DELETE: " << sqlite3_errmsg(db.getDB()) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}
