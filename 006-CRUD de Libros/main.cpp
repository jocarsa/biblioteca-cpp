#include <iostream>
#include <limits> 
#include "database.h"
#include "Autor.h"
#include "Libro.h"
#include "Prestamo.h"
#include "Seccion.h"
#include "Usuario.h"

void menuSecciones(Database& db) {
    int opcion;
    do {
        std::cout << "\n--- Gestión de Secciones ---\n";
        std::cout << "1. Crear sección\n";
        std::cout << "2. Listar secciones\n";
        std::cout << "3. Actualizar sección\n";
        std::cout << "4. Eliminar sección\n";
        std::cout << "0. Volver\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (opcion) {
            case 1: {
                std::string nombre;
                std::cout << "Nombre de la nueva sección: ";
                std::getline(std::cin, nombre);
                if (Seccion::crear(db, nombre))
                    std::cout << "Sección creada correctamente.\n";
                else
                    std::cout << "Error al crear la sección.\n";
                break;
            }
            case 2: {
                auto lista = Seccion::listar(db);
                std::cout << "ID\tNombre\n";
                for (const auto& sec : lista)
                    std::cout << sec.getId() << "\t" << sec.getNombre() << "\n";
                break;
            }
            case 3: {
                int id;
                std::string nuevoNombre;
                std::cout << "ID de la sección a actualizar: ";
                std::cin >> id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Nuevo nombre: ";
                std::getline(std::cin, nuevoNombre);
                if (Seccion::actualizar(db, id, nuevoNombre))
                    std::cout << "Sección actualizada.\n";
                else
                    std::cout << "Error al actualizar la sección.\n";
                break;
            }
            case 4: {
                int id;
                std::cout << "ID de la sección a eliminar: ";
                std::cin >> id;
                if (Seccion::eliminar(db, id))
                    std::cout << "Sección eliminada.\n";
                else
                    std::cout << "Error al eliminar la sección.\n";
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Opción no válida.\n";
        }
    } while (opcion != 0);
}

void menuAutores(Database& db) {
    int opcion;
    do {
        std::cout << "\n--- Gestión de Autores ---\n";
        std::cout << "1. Crear autor\n";
        std::cout << "2. Listar autores\n";
        std::cout << "3. Actualizar autor\n";
        std::cout << "4. Eliminar autor\n";
        std::cout << "0. Volver\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch(opcion) {
            case 1: {
                std::string nom, ape;
                std::cout << "Nombre: "; std::getline(std::cin, nom);
                std::cout << "Apellidos: "; std::getline(std::cin, ape);
                if (Autor::crear(db, nom, ape))
                    std::cout << "Autor creado correctamente.\n";
                else
                    std::cout << "Error al crear autor.\n";
                break;
            }
            case 2: {
                auto lista = Autor::listar(db);
                std::cout << "ID\tNombre Completo\n";
                for (const auto& a : lista)
                    std::cout << a.getId() << "\t" << a.getNombreCompleto() << "\n";
                break;
            }
            case 3: {
                int id; std::string nom, ape;
                std::cout << "ID del autor a actualizar: "; std::cin >> id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Nuevo nombre: "; std::getline(std::cin, nom);
                std::cout << "Nuevos apellidos: "; std::getline(std::cin, ape);
                if (Autor::actualizar(db, id, nom, ape))
                    std::cout << "Autor actualizado.\n";
                else
                    std::cout << "Error al actualizar.\n";
                break;
            }
            case 4: {
                int id;
                std::cout << "ID del autor a eliminar: "; std::cin >> id;
                if (Autor::eliminar(db, id))
                    std::cout << "Autor eliminado.\n";
                else
                    std::cout << "Error al eliminar.\n";
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Opción no válida.\n";
        }
    } while (opcion != 0);
}

void menuLibros(Database& db) {
    int opcion;
    do {
        std::cout << "\n--- Gestión de Libros ---\n";
        std::cout << "1. Crear libro\n";
        std::cout << "2. Listar libros\n";
        std::cout << "3. Actualizar libro\n";
        std::cout << "4. Eliminar libro\n";
        std::cout << "0. Volver\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcion) {
            case 1: {
                std::string titulo, isbn;
                int anio, idAutor, idSeccion;
                std::cout << "Título: ";              std::getline(std::cin, titulo);
                std::cout << "ISBN: ";                std::getline(std::cin, isbn);
                std::cout << "Año publicación: ";     std::cin >> anio;
                std::cout << "ID Autor: ";            std::cin >> idAutor;
                std::cout << "ID Sección: ";          std::cin >> idSeccion;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (Libro::crear(db, titulo, isbn, anio, idAutor, idSeccion))
                    std::cout << "Libro creado correctamente.\n";
                else
                    std::cout << "Error al crear libro.\n";
                break;
            }
            case 2: {
                auto lista = Libro::listar(db);
                std::cout << "ID\tTítulo\tISBN\tAño\tAutorID\tSecciónID\n";
                for (const auto& l : lista) {
                    std::cout
                        << l.getId()             << "\t"
                        << l.getTitulo()         << "\t"
                        << l.getISBN()           << "\t"
                        << l.getAnioPublicacion()<< "\t"
                        << l.getIdAutor()        << "\t"
                        << l.getIdSeccion()      << "\n";
                }
                break;
            }
            case 3: {
                int id, anio, idAutor, idSeccion;
                std::string titulo, isbn;
                std::cout << "ID del libro a actualizar: "; std::cin >> id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Nuevo título: ";        std::getline(std::cin, titulo);
                std::cout << "Nuevo ISBN: ";          std::getline(std::cin, isbn);
                std::cout << "Nuevo año publicación: "; std::cin >> anio;
                std::cout << "Nuevo AutorID: ";        std::cin >> idAutor;
                std::cout << "Nueva SecciónID: ";      std::cin >> idSeccion;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (Libro::actualizar(db, id, titulo, isbn, anio, idAutor, idSeccion))
                    std::cout << "Libro actualizado correctamente.\n";
                else
                    std::cout << "Error al actualizar libro.\n";
                break;
            }
            case 4: {
                int id;
                std::cout << "ID del libro a eliminar: "; std::cin >> id;
                if (Libro::eliminar(db, id))
                    std::cout << "Libro eliminado correctamente.\n";
                else
                    std::cout << "Error al eliminar libro.\n";
                break;
            }
            case 0:
                // volver al menú principal
                break;
            default:
                std::cout << "Opción no válida.\n";
        }
    } while (opcion != 0);
}

void menuUsuarios(Database& db) {
    int opcion;
    do {
        std::cout << "\n--- Gestión de Usuarios ---\n";
        std::cout << "1. Crear usuario\n";
        std::cout << "2. Listar usuarios\n";
        std::cout << "3. Actualizar usuario\n";
        std::cout << "4. Eliminar usuario\n";
        std::cout << "0. Volver\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (opcion) {
            case 1: {
                std::string nom, ape, email;
                std::cout << "Nombre: "; std::getline(std::cin, nom);
                std::cout << "Apellidos: "; std::getline(std::cin, ape);
                std::cout << "Email: "; std::getline(std::cin, email);
                if (Usuario::crear(db, nom, ape, email))
                    std::cout << "Usuario creado correctamente.\n";
                else
                    std::cout << "Error al crear usuario.\n";
                break;
            }
            case 2: {
                auto lista = Usuario::listar(db);
                std::cout << "ID\tNombre Completo\tEmail\tFecha Alta\n";
                for (const auto& u : lista)
                    std::cout << u.getId() << "\t" << u.getNombreCompleto()
                              << "\t" << u.getEmail()
                              << "\t" << u.getFechaAlta() << "\n";
                break;
            }
            case 3: {
                int id;
                std::string nom, ape, email;
                std::cout << "ID del usuario a actualizar: "; std::cin >> id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Nuevo nombre: "; std::getline(std::cin, nom);
                std::cout << "Nuevos apellidos: "; std::getline(std::cin, ape);
                std::cout << "Nuevo email: "; std::getline(std::cin, email);
                if (Usuario::actualizar(db, id, nom, ape, email))
                    std::cout << "Usuario actualizado.\n";
                else
                    std::cout << "Error al actualizar usuario.\n";
                break;
            }
            case 4: {
                int id;
                std::cout << "ID del usuario a eliminar: "; std::cin >> id;
                if (Usuario::eliminar(db, id))
                    std::cout << "Usuario eliminado.\n";
                else
                    std::cout << "Error al eliminar usuario.\n";
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Opción no válida.\n";
        }
    } while (opcion != 0);
}

void menuPrestamos() {
    int opcion;
    do {
        std::cout << "\n--- Gestión de Préstamos ---\n";
        std::cout << "1. Crear préstamo\n";
        std::cout << "2. Listar préstamos\n";
        std::cout << "3. Actualizar préstamo\n";
        std::cout << "4. Eliminar préstamo\n";
        std::cout << "0. Volver\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        switch (opcion) {
            case 1:
                std::cout << "[Crear préstamo] Placeholder...\n";
                break;
            case 2:
                std::cout << "[Listar préstamos] Placeholder...\n";
                break;
            case 3:
                std::cout << "[Actualizar préstamo] Placeholder...\n";
                break;
            case 4:
                std::cout << "[Eliminar préstamo] Placeholder...\n";
                break;
            case 0:
                break;
            default:
                std::cout << "Opción no válida.\n";
        }
    } while (opcion != 0);
}

int main() {
    Database db("biblioteca.db");
    int opcion;

    do {
        std::cout << "\n=== Menú Principal ===\n";
        std::cout << "1. Secciones\n";
        std::cout << "2. Autores\n";
        std::cout << "3. Libros\n";
        std::cout << "4. Usuarios\n";
        std::cout << "5. Préstamos\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        switch (opcion) {
            case 1:
                menuSecciones(db);
                break;
            case 2:
                menuAutores(db);
                break;
            case 3:
                menuLibros(db);
                break;
            case 4:
                menuUsuarios(db);
                break;
            case 5:
                menuPrestamos();
                break;
            case 0:
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Opción no válida.\n";
        }
    } while (opcion != 0);

    return 0;
}


