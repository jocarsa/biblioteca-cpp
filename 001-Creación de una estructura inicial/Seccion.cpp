#include "Seccion.h"

Seccion::Seccion(
	int id, 
	const std::string& nombre
) : id_seccion(id), 
	nombre(nombre) {}

int Seccion::getId() const {
    return id_seccion;
}

std::string Seccion::getNombre() const {
    return nombre;
}

