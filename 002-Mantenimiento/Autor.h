#ifndef AUTOR_H
#define AUTOR_H

#include <string>

class Autor {
private:
    int id_autor;
    std::string nombre;
    std::string apellidos;

public:
    Autor(int id, const std::string& nom, const std::string& ape);
    int getId() const;
    std::string getNombreCompleto() const;
};

#endif

