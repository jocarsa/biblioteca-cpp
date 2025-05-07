#ifndef SECCION_H
#define SECCION_H

#include <string>

class Seccion {
private:
    int id_seccion;
    std::string nombre;

public:
    Seccion(int id, const std::string& nombre);
    int getId() const;
    std::string getNombre() const;
};

#endif

