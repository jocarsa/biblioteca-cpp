#ifndef LIBRO_H
#define LIBRO_H

#include <string>

class Libro {
private:
    int id_libro;
    std::string titulo;
    std::string isbn;
    int anio_publicacion;
    int id_autor;
    int id_seccion;

public:
    Libro(
    	int id, 
    	const std::string& titulo, 
    	const std::string& isbn, 
    	int anio, 
    	int idAutor, 
    	int idSeccion);
    int getId() const;
    std::string getTitulo() const;
    std::string getISBN() const;
    int getAnioPublicacion() const;
    int getIdAutor() const;
    int getIdSeccion() const;
};

#endif

