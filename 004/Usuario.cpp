#include "Usuario.h"

Usuario::Usuario(
	int id, 
	const std::string& nom, 
	const std::string& ape, 
	const std::string& email, 
	const std::string& fechaAlta)
    : id_usuario(id), 
    nombre(nom), 
    apellidos(ape), 
    email(email), 
    fecha_alta(fechaAlta) {}

int Usuario::getId() const { 
	return id_usuario; 
}
std::string Usuario::getNombreCompleto() const { 
	return nombre + " " + apellidos; 
}
std::string Usuario::getEmail() const { 
	return email; 
}
std::string Usuario::getFechaAlta() const { 
	return fecha_alta; 
}

