#ifndef AUTOR_H
#define AUTOR_H

#include <string>
#include <vector>
#include "database.h"

class Autor {
private:
    int id_autor;
    std::string nombre;
    std::string apellidos;

public:
    Autor(int id, const std::string& nom, const std::string& ape);

    int getId() const;
    std::string getNombreCompleto() const;

    // CRUD estático
    static bool crear(Database& db, const std::string& nom, const std::string& ape);
    static std::vector<Autor> listar(Database& db);
    static bool actualizar(Database& db, int id, const std::string& nom, const std::string& ape);
    static bool eliminar(Database& db, int id);
};

#endif
