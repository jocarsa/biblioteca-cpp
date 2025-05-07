#include "Libro.h"

Libro::Libro(
	int id, 
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
    id_seccion(idSeccion) {
    
    }

int Libro::getId() const { 
	return id_libro; 
}
std::string Libro::getTitulo() const { 
	return titulo; 
}
std::string Libro::getISBN() const { 
	return isbn; 
}
int Libro::getAnioPublicacion() const { 
	return anio_publicacion; 
}
int Libro::getIdAutor() const { 
	return id_autor; 
}
int Libro::getIdSeccion() const { 
	return id_seccion; 
}

