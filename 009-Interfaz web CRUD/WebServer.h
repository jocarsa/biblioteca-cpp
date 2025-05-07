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
    std::map<std::string, std::function<std::string(const std::string&, const std::string&)>> rutas_;

    void configurarRutas();
    std::string manejarSecciones(const std::string& metodo, const std::string& solicitud);
    std::string manejarAutores(const std::string& metodo, const std::string& solicitud);
    std::string manejarLibros(const std::string& metodo, const std::string& solicitud);
    std::string manejarUsuarios(const std::string& metodo, const std::string& solicitud);
    std::string manejarPrestamos(const std::string& metodo, const std::string& solicitud);

    // Function to extract values from JSON body
    std::string extraerValor(const std::string& body, const std::string& clave);
};

#endif // WEBSERVER_H

