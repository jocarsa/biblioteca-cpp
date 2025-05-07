#include "WebServer.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <sys/stat.h>
#include "Seccion.h"
#include "Autor.h"
#include "Libro.h"
#include "Usuario.h"
#include "Prestamo.h"

WebServer::WebServer(int puerto, Database& db) : puerto_(puerto), db_(db) {
    configurarRutas();
}

void WebServer::configurarRutas() {
    rutas_["/secciones"] = [this](const std::string& metodo, const std::string& solicitud) { return manejarSecciones(metodo, solicitud); };
    rutas_["/autores"] = [this](const std::string& metodo, const std::string& solicitud) { return manejarAutores(metodo, solicitud); };
    rutas_["/libros"] = [this](const std::string& metodo, const std::string& solicitud) { return manejarLibros(metodo, solicitud); };
    rutas_["/usuarios"] = [this](const std::string& metodo, const std::string& solicitud) { return manejarUsuarios(metodo, solicitud); };
    rutas_["/prestamos"] = [this](const std::string& metodo, const std::string& solicitud) { return manejarPrestamos(metodo, solicitud); };
}

void WebServer::iniciar() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Error al crear el socket" << std::endl;
        return;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(puerto_);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error al enlazar el socket" << std::endl;
        close(serverSocket);
        return;
    }

    if (listen(serverSocket, 5) < 0) {
        std::cerr << "Error al escuchar en el socket" << std::endl;
        close(serverSocket);
        return;
    }

    std::cout << "Servidor escuchando en el puerto " << puerto_ << std::endl;

    while (true) {
        sockaddr_in clientAddr{};
        socklen_t clientAddrLen = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket < 0) {
            std::cerr << "Error al aceptar la conexión" << std::endl;
            continue;
        }

        manejarSolicitud(clientSocket);
        close(clientSocket);
    }
}

void WebServer::manejarSolicitud(int clientSocket) {
    std::string solicitud = leerSolicitud(clientSocket);
    std::string respuesta = enrutarSolicitud(solicitud);
    enviarRespuesta(clientSocket, respuesta);
}

std::string WebServer::leerSolicitud(int clientSocket) {
    std::string solicitud;
    char buf[1024];
    int n;

    // 1) Leer hasta encontrar el separador de cabeceras y cuerpo
    while (solicitud.find("\r\n\r\n") == std::string::npos) {
        n = read(clientSocket, buf, sizeof(buf));
        if (n <= 0) break;
        solicitud.append(buf, n);
    }

    // 2) Extraer Content-Length (si existe) para saber cuántos bytes leer
    size_t pos = solicitud.find("Content-Length:");
    int contentLength = 0;
    if (pos != std::string::npos) {
        size_t lineEnd = solicitud.find("\r\n", pos);
        std::string lenStr = solicitud.substr(pos + 15, lineEnd - (pos + 15));
        contentLength = std::stoi(lenStr);
    }

    // 3) Leer el cuerpo restante basándose en Content-Length
    size_t headerEnd = solicitud.find("\r\n\r\n") + 4;
    int bodySoFar = solicitud.size() - headerEnd;
    while (bodySoFar < contentLength) {
        n = read(clientSocket, buf, sizeof(buf));
        if (n <= 0) break;
        solicitud.append(buf, n);
        bodySoFar += n;
    }

    return solicitud;
}

void WebServer::enviarRespuesta(int clientSocket, const std::string& respuesta) {
    send(clientSocket, respuesta.c_str(), respuesta.size(), 0);
}

std::string WebServer::enrutarSolicitud(const std::string& solicitud) {
    if (solicitud.find("GET /secciones") != std::string::npos) {
        return rutas_["/secciones"]("GET", solicitud);
    } else if (solicitud.find("POST /secciones") != std::string::npos) {
        return rutas_["/secciones"]("POST", solicitud);
    } else if (solicitud.find("PUT /secciones") != std::string::npos) {
        return rutas_["/secciones"]("PUT", solicitud);
    } else if (solicitud.find("DELETE /secciones") != std::string::npos) {
        return rutas_["/secciones"]("DELETE", solicitud);
    } else if (solicitud.find("GET /autores") != std::string::npos) {
        return rutas_["/autores"]("GET", solicitud);
    } else if (solicitud.find("POST /autores") != std::string::npos) {
        return rutas_["/autores"]("POST", solicitud);
    } else if (solicitud.find("PUT /autores") != std::string::npos) {
        return rutas_["/autores"]("PUT", solicitud);
    } else if (solicitud.find("DELETE /autores") != std::string::npos) {
        return rutas_["/autores"]("DELETE", solicitud);
    } else if (solicitud.find("GET /libros") != std::string::npos) {
        return rutas_["/libros"]("GET", solicitud);
    } else if (solicitud.find("POST /libros") != std::string::npos) {
        return rutas_["/libros"]("POST", solicitud);
    } else if (solicitud.find("PUT /libros") != std::string::npos) {
        return rutas_["/libros"]("PUT", solicitud);
    } else if (solicitud.find("DELETE /libros") != std::string::npos) {
        return rutas_["/libros"]("DELETE", solicitud);
    } else if (solicitud.find("GET /usuarios") != std::string::npos) {
        return rutas_["/usuarios"]("GET", solicitud);
    } else if (solicitud.find("POST /usuarios") != std::string::npos) {
        return rutas_["/usuarios"]("POST", solicitud);
    } else if (solicitud.find("PUT /usuarios") != std::string::npos) {
        return rutas_["/usuarios"]("PUT", solicitud);
    } else if (solicitud.find("DELETE /usuarios") != std::string::npos) {
        return rutas_["/usuarios"]("DELETE", solicitud);
    } else if (solicitud.find("GET /prestamos") != std::string::npos) {
        return rutas_["/prestamos"]("GET", solicitud);
    } else if (solicitud.find("POST /prestamos") != std::string::npos) {
        return rutas_["/prestamos"]("POST", solicitud);
    } else if (solicitud.find("PUT /prestamos") != std::string::npos) {
        return rutas_["/prestamos"]("PUT", solicitud);
    } else if (solicitud.find("DELETE /prestamos") != std::string::npos) {
        return rutas_["/prestamos"]("DELETE", solicitud);
    } else if (solicitud.find("GET / ") != std::string::npos || solicitud.find("GET /index.html") != std::string::npos) {
        std::ifstream archivo("static/index.html");
        if (archivo) {
            std::string contenido((std::istreambuf_iterator<char>(archivo)), std::istreambuf_iterator<char>());
            return "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + contenido;
        } else {
            return "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nArchivo no encontrado";
        }
    } else if (solicitud.find("GET /estilo.css") != std::string::npos) {
        std::ifstream archivo("static/estilo.css");
        if (archivo) {
            std::string contenido((std::istreambuf_iterator<char>(archivo)), std::istreambuf_iterator<char>());
            return "HTTP/1.1 200 OK\r\nContent-Type: text/css\r\n\r\n" + contenido;
        } else {
            return "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nArchivo no encontrado";
        }
    } else if (solicitud.find("GET /codigo.js") != std::string::npos) {
        std::ifstream archivo("static/codigo.js");
        if (archivo) {
            std::string contenido((std::istreambuf_iterator<char>(archivo)), std::istreambuf_iterator<char>());
            return "HTTP/1.1 200 OK\r\nContent-Type: application/javascript\r\n\r\n" + contenido;
        } else {
            return "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nArchivo no encontrado";
        }
    } else {
        return "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNo encontrado";
    }
}

std::string WebServer::manejarSecciones(const std::string& metodo, const std::string& solicitud) {
    if (metodo == "GET") {
        auto lista = Seccion::listar(db_);
        std::string respuesta = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n[";
        for (const auto& sec : lista) {
            respuesta += "{\"id\":" + std::to_string(sec.getId()) + ", \"nombre\":\"" + sec.getNombre() + "\"},";
        }
        if (!lista.empty()) {
            respuesta.pop_back(); // Eliminar la coma final
        }
        respuesta += "]";
        return respuesta;
    } else if (metodo == "POST") {
        std::string body = solicitud.substr(solicitud.find("\r\n\r\n") + 4);
        std::string nombre = extraerValor(body, "nombre");
        if (nombre.empty()) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"El nombre de la sección no puede estar vacío\"}";
        }
        if (Seccion::crear(db_, nombre)) {
            return "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Sección creada\"}";
        } else {
            return "HTTP/1.1 500 Internal Server Error\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Error al crear la sección\"}";
        }
    } else if (metodo == "PUT") {
        std::string body = solicitud.substr(solicitud.find("\r\n\r\n") + 4);
        std::string idStr = extraerValor(body, "id");
        std::string nombre = extraerValor(body, "nombre");

        if (idStr.empty() || nombre.empty()) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"El ID y el nombre no pueden estar vacíos\"}";
        }

        try {
            int id = std::stoi(idStr);
            if (Seccion::actualizar(db_, id, nombre)) {
                return "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Sección actualizada\"}";
            } else {
                return "HTTP/1.1 500 Internal Server Error\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Error al actualizar la sección\"}";
            }
        } catch (const std::invalid_argument& e) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"El ID debe ser un número válido\"}";
        }
    } else if (metodo == "DELETE") {
        std::string body = solicitud.substr(solicitud.find("\r\n\r\n") + 4);
        std::string idStr = extraerValor(body, "id");

        if (idStr.empty()) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"El ID no puede estar vacío\"}";
        }

        try {
            int id = std::stoi(idStr);
            if (Seccion::eliminar(db_, id)) {
                return "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Sección eliminada\"}";
            } else {
                return "HTTP/1.1 500 Internal Server Error\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Error al eliminar la sección\"}";
            }
        } catch (const std::invalid_argument& e) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"El ID debe ser un número válido\"}";
        }
    } else {
        return "HTTP/1.1 405 Method Not Allowed\r\nContent-Type: text/plain\r\n\r\nMétodo no permitido";
    }
}

std::string WebServer::manejarAutores(const std::string& metodo, const std::string& solicitud) {
    if (metodo == "GET") {
        auto lista = Autor::listar(db_);
        std::string respuesta = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n[";
        for (const auto& a : lista) {
            respuesta += "{\"id\":" + std::to_string(a.getId()) + ", \"nombre\":\"" + a.getNombreCompleto() + "\"},";
        }
        if (!lista.empty()) {
            respuesta.pop_back(); // Eliminar la coma final
        }
        respuesta += "]";
        return respuesta;
    } else if (metodo == "POST") {
        std::string body = solicitud.substr(solicitud.find("\r\n\r\n") + 4);
        std::string nombre = extraerValor(body, "nombre");
        std::string apellidos = extraerValor(body, "apellidos");

        if (nombre.empty() || apellidos.empty()) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"El nombre y los apellidos no pueden estar vacíos\"}";
        }

        if (Autor::crear(db_, nombre, apellidos)) {
            return "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Autor creado\"}";
        } else {
            return "HTTP/1.1 500 Internal Server Error\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Error al crear el autor\"}";
        }
    } else if (metodo == "PUT") {
        std::string body = solicitud.substr(solicitud.find("\r\n\r\n") + 4);
        std::string idStr = extraerValor(body, "id");
        std::string nombre = extraerValor(body, "nombre");
        std::string apellidos = extraerValor(body, "apellidos");

        if (idStr.empty() || nombre.empty() || apellidos.empty()) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"El ID, nombre y apellidos no pueden estar vacíos\"}";
        }

        try {
            int id = std::stoi(idStr);
            if (Autor::actualizar(db_, id, nombre, apellidos)) {
                return "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Autor actualizado\"}";
            } else {
                return "HTTP/1.1 500 Internal Server Error\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Error al actualizar el autor\"}";
            }
        } catch (const std::invalid_argument& e) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"El ID debe ser un número válido\"}";
        }
    } else if (metodo == "DELETE") {
        std::string body = solicitud.substr(solicitud.find("\r\n\r\n") + 4);
        std::string idStr = extraerValor(body, "id");

        if (idStr.empty()) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"El ID no puede estar vacío\"}";
        }

        try {
            int id = std::stoi(idStr);
            if (Autor::eliminar(db_, id)) {
                return "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Autor eliminado\"}";
            } else {
                return "HTTP/1.1 500 Internal Server Error\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Error al eliminar el autor\"}";
            }
        } catch (const std::invalid_argument& e) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"El ID debe ser un número válido\"}";
        }
    } else {
        return "HTTP/1.1 405 Method Not Allowed\r\nContent-Type: text/plain\r\n\r\nMétodo no permitido";
    }
}

std::string WebServer::manejarLibros(const std::string& metodo, const std::string& solicitud) {
    if (metodo == "GET") {
        auto lista = Libro::listar(db_);
        std::string respuesta = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n[";
        for (const auto& l : lista) {
            respuesta += "{\"id\":" + std::to_string(l.getId()) +
                        ", \"titulo\":\"" + l.getTitulo() +
                        "\", \"isbn\":\"" + l.getISBN() +
                        "\", \"anio\":" + std::to_string(l.getAnioPublicacion()) +
                        ", \"idAutor\":" + std::to_string(l.getIdAutor()) +
                        ", \"idSeccion\":" + std::to_string(l.getIdSeccion()) + "},";
        }
        if (!lista.empty()) {
            respuesta.pop_back(); // Eliminar la coma final
        }
        respuesta += "]";
        return respuesta;
    } else if (metodo == "POST") {
        std::string body = solicitud.substr(solicitud.find("\r\n\r\n") + 4);
        std::string titulo = extraerValor(body, "titulo");
        std::string isbn = extraerValor(body, "isbn");
        std::string anioStr = extraerValor(body, "anio");
        std::string idAutorStr = extraerValor(body, "idAutor");
        std::string idSeccionStr = extraerValor(body, "idSeccion");

        if (titulo.empty() || isbn.empty() || anioStr.empty() || idAutorStr.empty() || idSeccionStr.empty()) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Todos los campos son obligatorios\"}";
        }

        try {
            int anio = std::stoi(anioStr);
            int idAutor = std::stoi(idAutorStr);
            int idSeccion = std::stoi(idSeccionStr);

            if (Libro::crear(db_, titulo, isbn, anio, idAutor, idSeccion)) {
                return "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Libro creado\"}";
            } else {
                return "HTTP/1.1 500 Internal Server Error\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Error al crear el libro\"}";
            }
        } catch (const std::invalid_argument& e) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Los campos Año, ID Autor y ID Sección deben ser números\"}";
        }
    } else if (metodo == "PUT") {
        std::string body = solicitud.substr(solicitud.find("\r\n\r\n") + 4);
        std::string idStr = extraerValor(body, "id");
        std::string titulo = extraerValor(body, "titulo");
        std::string isbn = extraerValor(body, "isbn");
        std::string anioStr = extraerValor(body, "anio");
        std::string idAutorStr = extraerValor(body, "idAutor");
        std::string idSeccionStr = extraerValor(body, "idSeccion");

        if (idStr.empty() || titulo.empty() || isbn.empty() || anioStr.empty() || idAutorStr.empty() || idSeccionStr.empty()) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Todos los campos son obligatorios\"}";
        }

        try {
            int id = std::stoi(idStr);
            int anio = std::stoi(anioStr);
            int idAutor = std::stoi(idAutorStr);
            int idSeccion = std::stoi(idSeccionStr);

            if (Libro::actualizar(db_, id, titulo, isbn, anio, idAutor, idSeccion)) {
                return "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Libro actualizado\"}";
            } else {
                return "HTTP/1.1 500 Internal Server Error\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Error al actualizar el libro\"}";
            }
        } catch (const std::invalid_argument& e) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Los campos Año, ID Autor y ID Sección deben ser números\"}";
        }
    } else if (metodo == "DELETE") {
        std::string body = solicitud.substr(solicitud.find("\r\n\r\n") + 4);
        std::string idStr = extraerValor(body, "id");

        if (idStr.empty()) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"El ID no puede estar vacío\"}";
        }

        try {
            int id = std::stoi(idStr);
            if (Libro::eliminar(db_, id)) {
                return "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Libro eliminado\"}";
            } else {
                return "HTTP/1.1 500 Internal Server Error\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Error al eliminar el libro\"}";
            }
        } catch (const std::invalid_argument& e) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"El ID debe ser un número válido\"}";
        }
    } else {
        return "HTTP/1.1 405 Method Not Allowed\r\nContent-Type: text/plain\r\n\r\nMétodo no permitido";
    }
}

std::string WebServer::manejarUsuarios(const std::string& metodo, const std::string& solicitud) {
    if (metodo == "GET") {
        auto lista = Usuario::listar(db_);
        std::string respuesta = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n[";
        for (const auto& u : lista) {
            respuesta += "{\"id\":" + std::to_string(u.getId()) +
                        ", \"nombre\":\"" + u.getNombreCompleto() +
                        "\", \"email\":\"" + u.getEmail() +
                        "\", \"fechaAlta\":\"" + u.getFechaAlta() + "\"},";
        }
        if (!lista.empty()) {
            respuesta.pop_back(); // Eliminar la coma final
        }
        respuesta += "]";
        return respuesta;
    } else if (metodo == "POST") {
        std::string body = solicitud.substr(solicitud.find("\r\n\r\n") + 4);
        std::string nombre = extraerValor(body, "nombre");
        std::string apellidos = extraerValor(body, "apellidos");
        std::string email = extraerValor(body, "email");

        if (nombre.empty() || apellidos.empty() || email.empty()) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Todos los campos son obligatorios\"}";
        }

        if (Usuario::crear(db_, nombre, apellidos, email)) {
            return "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Usuario creado\"}";
        } else {
            return "HTTP/1.1 500 Internal Server Error\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Error al crear el usuario\"}";
        }
    } else if (metodo == "PUT") {
        std::string body = solicitud.substr(solicitud.find("\r\n\r\n") + 4);
        std::string idStr = extraerValor(body, "id");
        std::string nombre = extraerValor(body, "nombre");
        std::string apellidos = extraerValor(body, "apellidos");
        std::string email = extraerValor(body, "email");

        if (idStr.empty() || nombre.empty() || apellidos.empty() || email.empty()) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Todos los campos son obligatorios\"}";
        }

        try {
            int id = std::stoi(idStr);
            if (Usuario::actualizar(db_, id, nombre, apellidos, email)) {
                return "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Usuario actualizado\"}";
            } else {
                return "HTTP/1.1 500 Internal Server Error\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Error al actualizar el usuario\"}";
            }
        } catch (const std::invalid_argument& e) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"El ID debe ser un número válido\"}";
        }
    } else if (metodo == "DELETE") {
        std::string body = solicitud.substr(solicitud.find("\r\n\r\n") + 4);
        std::string idStr = extraerValor(body, "id");

        if (idStr.empty()) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"El ID no puede estar vacío\"}";
        }

        try {
            int id = std::stoi(idStr);
            if (Usuario::eliminar(db_, id)) {
                return "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Usuario eliminado\"}";
            } else {
                return "HTTP/1.1 500 Internal Server Error\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Error al eliminar el usuario\"}";
            }
        } catch (const std::invalid_argument& e) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"El ID debe ser un número válido\"}";
        }
    } else {
        return "HTTP/1.1 405 Method Not Allowed\r\nContent-Type: text/plain\r\n\r\nMétodo no permitido";
    }
}

std::string WebServer::manejarPrestamos(const std::string& metodo, const std::string& solicitud) {
    if (metodo == "GET") {
        auto lista = Prestamo::listar(db_);
        std::string respuesta = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n[";
        for (const auto& p : lista) {
            respuesta += "{\"id\":" + std::to_string(p.getId()) +
                        ", \"idLibro\":" + std::to_string(p.getIdLibro()) +
                        ", \"idUsuario\":" + std::to_string(p.getIdUsuario()) +
                        ", \"fechaPrestamo\":\"" + p.getFechaPrestamo() +
                        "\", \"fechaDevolucion\":\"" + p.getFechaDevolucion() +
                        "\", \"fechaRealDevolucion\":\"" + p.getFechaRealDevolucion() + "\"},";
        }
        if (!lista.empty()) {
            respuesta.pop_back(); // Eliminar la coma final
        }
        respuesta += "]";
        return respuesta;
    } else if (metodo == "POST") {
        std::string body = solicitud.substr(solicitud.find("\r\n\r\n") + 4);
        std::string idLibroStr = extraerValor(body, "idLibro");
        std::string idUsuarioStr = extraerValor(body, "idUsuario");
        std::string fechaPrestamo = extraerValor(body, "fechaPrestamo");
        std::string fechaDevolucion = extraerValor(body, "fechaDevolucion");

        if (idLibroStr.empty() || idUsuarioStr.empty() || fechaPrestamo.empty() || fechaDevolucion.empty()) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Todos los campos son obligatorios\"}";
        }

        try {
            int idLibro = std::stoi(idLibroStr);
            int idUsuario = std::stoi(idUsuarioStr);

            if (Prestamo::crear(db_, idLibro, idUsuario, fechaPrestamo, fechaDevolucion)) {
                return "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Préstamo creado\"}";
            } else {
                return "HTTP/1.1 500 Internal Server Error\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Error al crear el préstamo\"}";
            }
        } catch (const std::invalid_argument& e) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Los campos ID Libro y ID Usuario deben ser números\"}";
        }
    } else if (metodo == "PUT") {
        std::string body = solicitud.substr(solicitud.find("\r\n\r\n") + 4);
        std::string idStr = extraerValor(body, "id");
        std::string idLibroStr = extraerValor(body, "idLibro");
        std::string idUsuarioStr = extraerValor(body, "idUsuario");
        std::string fechaPrestamo = extraerValor(body, "fechaPrestamo");
        std::string fechaDevolucion = extraerValor(body, "fechaDevolucion");
        std::string fechaRealDevolucion = extraerValor(body, "fechaRealDevolucion");

        if (idStr.empty() || idLibroStr.empty() || idUsuarioStr.empty() || fechaPrestamo.empty() || fechaDevolucion.empty()) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Todos los campos son obligatorios\"}";
        }

        try {
            int id = std::stoi(idStr);
            int idLibro = std::stoi(idLibroStr);
            int idUsuario = std::stoi(idUsuarioStr);

            if (Prestamo::actualizar(db_, id, idLibro, idUsuario, fechaPrestamo, fechaDevolucion, fechaRealDevolucion)) {
                return "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Préstamo actualizado\"}";
            } else {
                return "HTTP/1.1 500 Internal Server Error\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Error al actualizar el préstamo\"}";
            }
        } catch (const std::invalid_argument& e) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Los campos ID, ID Libro y ID Usuario deben ser números\"}";
        }
    } else if (metodo == "DELETE") {
        std::string body = solicitud.substr(solicitud.find("\r\n\r\n") + 4);
        std::string idStr = extraerValor(body, "id");

        if (idStr.empty()) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"El ID no puede estar vacío\"}";
        }

        try {
            int id = std::stoi(idStr);
            if (Prestamo::eliminar(db_, id)) {
                return "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Préstamo eliminado\"}";
            } else {
                return "HTTP/1.1 500 Internal Server Error\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"Error al eliminar el préstamo\"}";
            }
        } catch (const std::invalid_argument& e) {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"mensaje\":\"El ID debe ser un número válido\"}";
        }
    } else {
        return "HTTP/1.1 405 Method Not Allowed\r\nContent-Type: text/plain\r\n\r\nMétodo no permitido";
    }
}

std::string WebServer::extraerValor(const std::string& body,
                                    const std::string& clave)
{
    // 1) Valores entre comillas  -->  "clave":"valor"
    std::string patronStr = "\"" + clave + "\":\"";
    size_t pos = body.find(patronStr);
    if (pos != std::string::npos) {
        pos += patronStr.length();                 // justo después de las comillas
        size_t fin = body.find('"', pos);          // siguiente comilla
        return body.substr(pos, fin - pos);
    }

    // 2) Valores numéricos       -->  "clave": 123
    patronStr = "\"" + clave + "\":";
    pos = body.find(patronStr);
    if (pos != std::string::npos) {
        pos += patronStr.length();
        while (pos < body.size() && std::isspace(body[pos])) ++pos;   // saltar espacios
        size_t fin = pos;
        while (fin < body.size() && (std::isdigit(body[fin]) || body[fin] == '-'))
            ++fin;
        return body.substr(pos, fin - pos);
    }

    return "";
}

