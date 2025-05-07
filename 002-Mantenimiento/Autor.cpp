#include "Autor.h"

Autor::Autor(
	int id, 
	const std::string& nom, 
	const std::string& ape)
    : id_autor(id), 
    nombre(nom), 
    apellidos(ape) {}

int Autor::getId() const {
    return id_autor;
}

std::string Autor::getNombreCompleto() const {
    return nombre + " " + apellidos;
}

