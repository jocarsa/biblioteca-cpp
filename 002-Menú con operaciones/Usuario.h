#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario {
private:
    int id_usuario;
    std::string nombre;
    std::string apellidos;
    std::string email;
    std::string fecha_alta;

public:
    Usuario(
    	int id, 
    	const std::string& nom, 
    	const std::string& ape, 
    	const std::string& email, 
    	const std::string& fechaAlta);
    int getId() const;
    std::string getNombreCompleto() const;
    std::string getEmail() const;
    std::string getFechaAlta() const;
};

#endif

