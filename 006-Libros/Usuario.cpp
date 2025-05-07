#include "Usuario.h"
#include <sqlite3.h>
#include <iostream>

Usuario::Usuario(int id, const std::string& nom, const std::string& ape,
                 const std::string& email, const std::string& fechaAlta)
    : id_usuario(id), nombre(nom), apellidos(ape),
      email(email), fecha_alta(fechaAlta) {}

int Usuario::getId() const { return id_usuario; }
std::string Usuario::getNombreCompleto() const { return nombre + " " + apellidos; }
std::string Usuario::getEmail() const { return email; }
std::string Usuario::getFechaAlta() const { return fecha_alta; }

bool Usuario::crear(Database& db, const std::string& nom,
                    const std::string& ape, const std::string& email) {
    const char* sql =
        "INSERT INTO usuario(nombre, apellidos, email, fecha_alta) "
        "VALUES(?,?,?, date('now'));";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error INSERT usuario: "
                  << sqlite3_errmsg(db.getDB()) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, nom.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, ape.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, email.c_str(), -1, SQLITE_STATIC);
    bool ok = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return ok;
}

std::vector<Usuario> Usuario::listar(Database& db) {
    std::vector<Usuario> lista;
    const char* sql =
        "SELECT id_usuario, nombre, apellidos, email, fecha_alta FROM usuario;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error SELECT usuario: "
                  << sqlite3_errmsg(db.getDB()) << std::endl;
        return lista;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* nom = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* ape = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        const char* mail = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        const char* fecha = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        lista.emplace_back(id, nom, ape, mail, fecha);
    }
    sqlite3_finalize(stmt);
    return lista;
}

bool Usuario::actualizar(Database& db, int id,
                         const std::string& nom,
                         const std::string& ape,
                         const std::string& email) {
    const char* sql =
        "UPDATE usuario SET nombre = ?, apellidos = ?, email = ? "
        "WHERE id_usuario = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error UPDATE usuario: "
                  << sqlite3_errmsg(db.getDB()) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, nom.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, ape.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, email.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, id);
    bool ok = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return ok;
}

bool Usuario::eliminar(Database& db, int id) {
    const char* sql = "DELETE FROM usuario WHERE id_usuario = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error DELETE usuario: "
                  << sqlite3_errmsg(db.getDB()) << std::endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, id);
    bool ok = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return ok;
}
