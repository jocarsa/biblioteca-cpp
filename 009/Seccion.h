#ifndef SECCION_H
#define SECCION_H

#include <string>
#include <vector>
#include "database.h"

class Seccion {
private:
    int id_seccion;
    std::string nombre;

public:
    Seccion(int id, const std::string& nombre);

    int getId() const;
    std::string getNombre() const;

    // CRUD estático
    static bool crear(Database& db, const std::string& nombre);
    static std::vector<Seccion> listar(Database& db);
    static bool actualizar(Database& db, int id, const std::string& nuevoNombre);
    static bool eliminar(Database& db, int id);
};

#endif
