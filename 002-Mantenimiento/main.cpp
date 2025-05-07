#include <iostream>
#include "database.h"
#include "Autor.h"
#include "Libro.h"
#include "Prestamo.h"
#include "Seccion.h"
#include "Usuario.h"

void menuSecciones() {
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
        switch (opcion) {
            case 1:
                // TODO: placeholder para crear sección
                std::cout << "[Crear sección] Placeholder...\n";
                break;
            case 2:
                // TODO: placeholder para listar secciones
                std::cout << "[Listar secciones] Placeholder...\n";
                break;
            case 3:
                // TODO: placeholder para actualizar sección
                std::cout << "[Actualizar sección] Placeholder...\n";
                break;
            case 4:
                // TODO: placeholder para eliminar sección
                std::cout << "[Eliminar sección] Placeholder...\n";
                break;
            case 0:
                break;
            default:
                std::cout << "Opción no válida.\n";
        }
    } while (opcion != 0);
}

void menuAutores() {
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
        switch (opcion) {
            case 1:
                std::cout << "[Crear autor] Placeholder...\n";
                break;
            case 2:
                std::cout << "[Listar autores] Placeholder...\n";
                break;
            case 3:
                std::cout << "[Actualizar autor] Placeholder...\n";
                break;
            case 4:
                std::cout << "[Eliminar autor] Placeholder...\n";
                break;
            case 0:
                break;
            default:
                std::cout << "Opción no válida.\n";
        }
    } while (opcion != 0);
}

void menuLibros() {
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
        switch (opcion) {
            case 1:
                std::cout << "[Crear libro] Placeholder...\n";
                break;
            case 2:
                std::cout << "[Listar libros] Placeholder...\n";
                break;
            case 3:
                std::cout << "[Actualizar libro] Placeholder...\n";
                break;
            case 4:
                std::cout << "[Eliminar libro] Placeholder...\n";
                break;
            case 0:
                break;
            default:
                std::cout << "Opción no válida.\n";
        }
    } while (opcion != 0);
}

void menuUsuarios() {
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
        switch (opcion) {
            case 1:
                std::cout << "[Crear usuario] Placeholder...\n";
                break;
            case 2:
                std::cout << "[Listar usuarios] Placeholder...\n";
                break;
            case 3:
                std::cout << "[Actualizar usuario] Placeholder...\n";
                break;
            case 4:
                std::cout << "[Eliminar usuario] Placeholder...\n";
                break;
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
                menuSecciones();
                break;
            case 2:
                menuAutores();
                break;
            case 3:
                menuLibros();
                break;
            case 4:
                menuUsuarios();
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

