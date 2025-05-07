#include <iostream>
#include "database.h"
#include "WebServer.h"

int main() {
    Database db("biblioteca.db");
    WebServer servidor(8080, db);
    servidor.iniciar();
    return 0;
}

