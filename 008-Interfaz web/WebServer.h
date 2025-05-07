#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <string>
#include <vector>
#include <map>
#include <functional>
#include "database.h"

class WebServer {
public:
    WebServer(int puerto, Database& db);
    void iniciar();

private:
    int puerto_;
    Database& db_;
    void manejarSolicitud(int clientSocket);
    std::string leerSolicitud(int clientSocket);
    void enviarRespuesta(int clientSocket, const std::string& respuesta);
    std::string enrutarSolicitud(const std::string& solicitud);
    std::map<std::string, std::function<std::string()>> rutas_;

    void configurarRutas();
    std::string manejarSecciones();
    std::string manejarAutores();
    std::string manejarLibros();
    std::string manejarUsuarios();
    std::string manejarPrestamos();
};

#endif // WEBSERVER_H

