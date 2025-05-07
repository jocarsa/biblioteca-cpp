#include "Libro.h"
#include <sqlite3.h>
#include <iostream>

Libro::Libro(int id,
             const std::string& titulo,
             const std::string& isbn,
             int anio,
             int idAutor,
             int idSeccion)
    : id_libro(id),
      titulo(titulo),
      isbn(isbn),
      anio_publicacion(anio),
      id_autor(idAutor),
      id_seccion(idSeccion) {}

int Libro::getId() const { return id_libro; }
std::string Libro::getTitulo() const { return titulo; }
std::string Libro::getISBN() const { return isbn; }
int Libro::getAnioPublicacion() const { return anio_publicacion; }
int Libro::getIdAutor() const { return id_autor; }
int Libro::getIdSeccion() const { return id_seccion; }

bool Libro::crear(Database& db,
                  const std::string& titulo,
                  const std::string& isbn,
                  int anio,
                  int idAutor,
                  int idSeccion) {
    const char* sql =
      "INSERT INTO libro(titulo, isbn, anio_publicacion, id_autor, id_seccion) "
      "VALUES(?,?,?,?,?);";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error INSERT libro: "
                  << sqlite3_errmsg(db.getDB()) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, titulo.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, isbn.c_str(),   -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt,  3, anio);
    sqlite3_bind_int(stmt,  4, idAutor);
    sqlite3_bind_int(stmt,  5, idSeccion);

    bool ok = (sqlite3_step(stmt) == SQLITE_DONE);
    if (!ok) {
        std::cerr << "Error ejecutando INSERT libro (posible clave externa inválida): "
                  << sqlite3_errmsg(db.getDB()) << std::endl;
    }
    sqlite3_finalize(stmt);
    return ok;
}

std::vector<Libro> Libro::listar(Database& db) {
    std::vector<Libro> lista;
    const char* sql =
      "SELECT id_libro, titulo, isbn, anio_publicacion, id_autor, id_seccion "
      "FROM libro;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error SELECT libro: "
                  << sqlite3_errmsg(db.getDB()) << std::endl;
        return lista;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id      = sqlite3_column_int(stmt, 0);
        const char* t = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* i = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        int year    = sqlite3_column_int(stmt, 3);
        int ida     = sqlite3_column_int(stmt, 4);
        int ids     = sqlite3_column_int(stmt, 5);

        lista.emplace_back(id, t, i, year, ida, ids);
    }
    sqlite3_finalize(stmt);
    return lista;
}

bool Libro::actualizar(Database& db,
                       int id,
                       const std::string& titulo,
                       const std::string& isbn,
                       int anio,
                       int idAutor,
                       int idSeccion) {
    const char* sql =
      "UPDATE libro "
      "SET titulo=?, isbn=?, anio_publicacion=?, id_autor=?, id_seccion=? "
      "WHERE id_libro=?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error UPDATE libro: "
                  << sqlite3_errmsg(db.getDB()) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, titulo.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, isbn.c_str(),   -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt,  3, anio);
    sqlite3_bind_int(stmt,  4, idAutor);
    sqlite3_bind_int(stmt,  5, idSeccion);
    sqlite3_bind_int(stmt,  6, id);

    bool ok = (sqlite3_step(stmt) == SQLITE_DONE);
    if (!ok) {
        std::cerr << "Error al actualizar libro (clave externa o id inválido): "
                  << sqlite3_errmsg(db.getDB()) << std::endl;
    }
    sqlite3_finalize(stmt);
    return ok;
}

bool Libro::eliminar(Database& db, int id) {
    const char* sql = "DELETE FROM libro WHERE id_libro=?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error DELETE libro: "
                  << sqlite3_errmsg(db.getDB()) << std::endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, id);
    bool ok = (sqlite3_step(stmt) == SQLITE_DONE);
    if (!ok) {
        std::cerr << "Error al eliminar libro (quizá existan préstamos asociados): "
                  << sqlite3_errmsg(db.getDB()) << std::endl;
    }
    sqlite3_finalize(stmt);
    return ok;
}

