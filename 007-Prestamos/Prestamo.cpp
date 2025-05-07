// Prestamo.cpp
#include "Prestamo.h"
#include "database.h"
#include <sqlite3.h>
#include <iostream>

// Constructor
Prestamo::Prestamo(int id,
                   int idLibro,
                   int idUsuario,
                   const std::string& fechaPrestamo,
                   const std::string& fechaDevolucion,
                   const std::string& fechaRealDevolucion)
    : id_prestamo(id),
      id_libro(idLibro),
      id_usuario(idUsuario),
      fecha_prestamo(fechaPrestamo),
      fecha_devolucion(fechaDevolucion),
      fecha_real_devolucion(fechaRealDevolucion) {}

// Getters
int Prestamo::getId() const {
    return id_prestamo;
}

int Prestamo::getIdLibro() const {
    return id_libro;
}

int Prestamo::getIdUsuario() const {
    return id_usuario;
}

std::string Prestamo::getFechaPrestamo() const {
    return fecha_prestamo;
}

std::string Prestamo::getFechaDevolucion() const {
    return fecha_devolucion;
}

std::string Prestamo::getFechaRealDevolucion() const {
    return fecha_real_devolucion;
}

// Crear
bool Prestamo::crear(Database& db,
                     int idLibro,
                     int idUsuario,
                     const std::string& fechaPrestamo,
                     const std::string& fechaDevolucion) {
    const char* sql =
      "INSERT INTO prestamo(id_libro, id_usuario, fecha_prestamo, fecha_devolucion) "
      "VALUES(?,?,?,?);";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error INSERT prestamo: "
                  << sqlite3_errmsg(db.getDB()) << std::endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, idLibro);
    sqlite3_bind_int(stmt, 2, idUsuario);
    sqlite3_bind_text(stmt, 3, fechaPrestamo.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, fechaDevolucion.c_str(), -1, SQLITE_STATIC);

    bool ok = (sqlite3_step(stmt) == SQLITE_DONE);
    if (!ok)
        std::cerr << "Error ejecutando INSERT prestamo (clave externa inválida?): "
                  << sqlite3_errmsg(db.getDB()) << std::endl;
    sqlite3_finalize(stmt);
    return ok;
}

// Listar
std::vector<Prestamo> Prestamo::listar(Database& db) {
    std::vector<Prestamo> lista;
    const char* sql =
      "SELECT id_prestamo, id_libro, id_usuario, "
      "fecha_prestamo, fecha_devolucion, fecha_real_devolucion "
      "FROM prestamo;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error SELECT prestamo: "
                  << sqlite3_errmsg(db.getDB()) << std::endl;
        return lista;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id        = sqlite3_column_int(stmt, 0);
        int idLibro   = sqlite3_column_int(stmt, 1);
        int idUsuario = sqlite3_column_int(stmt, 2);
        const char* fp = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        const char* fd = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        const char* fr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        lista.emplace_back(
            id,
            idLibro,
            idUsuario,
            fp ? fp : "",
            fd ? fd : "",
            fr ? fr : ""
        );
    }
    sqlite3_finalize(stmt);
    return lista;
}

// Actualizar
bool Prestamo::actualizar(Database& db,
                          int id,
                          int idLibro,
                          int idUsuario,
                          const std::string& fechaPrestamo,
                          const std::string& fechaDevolucion,
                          const std::string& fechaRealDevolucion) {
    const char* sql =
      "UPDATE prestamo SET "
      "id_libro=?, id_usuario=?, fecha_prestamo=?, "
      "fecha_devolucion=?, fecha_real_devolucion=? "
      "WHERE id_prestamo=?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error UPDATE prestamo: "
                  << sqlite3_errmsg(db.getDB()) << std::endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, idLibro);
    sqlite3_bind_int(stmt, 2, idUsuario);
    sqlite3_bind_text(stmt, 3, fechaPrestamo.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, fechaDevolucion.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, fechaRealDevolucion.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 6, id);

    bool ok = (sqlite3_step(stmt) == SQLITE_DONE);
    if (!ok)
        std::cerr << "Error ejecutando UPDATE prestamo: "
                  << sqlite3_errmsg(db.getDB()) << std::endl;
    sqlite3_finalize(stmt);
    return ok;
}

// Eliminar
bool Prestamo::eliminar(Database& db, int id) {
    const char* sql = "DELETE FROM prestamo WHERE id_prestamo=?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error DELETE prestamo: "
                  << sqlite3_errmsg(db.getDB()) << std::endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, id);
    bool ok = (sqlite3_step(stmt) == SQLITE_DONE);
    if (!ok)
        std::cerr << "Error ejecutando DELETE prestamo: "
                  << sqlite3_errmsg(db.getDB()) << std::endl;
    sqlite3_finalize(stmt);
    return ok;
}

