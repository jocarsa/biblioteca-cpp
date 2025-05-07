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
    rutas_["/secciones"] = [this]() { return manejarSecciones(); };
    rutas_["/autores"] = [this]() { return manejarAutores(); };
    rutas_["/libros"] = [this]() { return manejarLibros(); };
    rutas_["/usuarios"] = [this]() { return manejarUsuarios(); };
    rutas_["/prestamos"] = [this]() { return manejarPrestamos(); };
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
    char buffer[1024] = {0};
    read(clientSocket, buffer, 1024);
    return std::string(buffer);
}

void WebServer::enviarRespuesta(int clientSocket, const std::string& respuesta) {
    send(clientSocket, respuesta.c_str(), respuesta.size(), 0);
}

std::string WebServer::enrutarSolicitud(const std::string& solicitud) {
    if (solicitud.find("GET /secciones") != std::string::npos) {
        return rutas_["/secciones"]();
    } else if (solicitud.find("GET /autores") != std::string::npos) {
        return rutas_["/autores"]();
    } else if (solicitud.find("GET /libros") != std::string::npos) {
        return rutas_["/libros"]();
    } else if (solicitud.find("GET /usuarios") != std::string::npos) {
        return rutas_["/usuarios"]();
    } else if (solicitud.find("GET /prestamos") != std::string::npos) {
        return rutas_["/prestamos"]();
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

std::string WebServer::manejarSecciones() {
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
}

std::string WebServer::manejarAutores() {
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
}

std::string WebServer::manejarLibros() {
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
}

std::string WebServer::manejarUsuarios() {
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
}

std::string WebServer::manejarPrestamos() {
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
}

