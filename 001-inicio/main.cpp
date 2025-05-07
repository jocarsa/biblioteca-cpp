#include <iostream>
#include "database.h"
#include "Autor.h"
#include "Libro.h"
#include "Prestamo.h"
#include "Seccion.h"
#include "Usuario.h"

int main() {
    Database db("biblioteca.db");
    
    Autor a1(1, "Ana", "Torres Delgado");
    std::cout << "Autor: " << a1.getNombreCompleto() << std::endl;

    // Aquí iría el menú o lógica de interacción
    return 0;
}

