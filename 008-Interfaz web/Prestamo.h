// === Prestamo.h ===
#ifndef PRESTAMO_H
#define PRESTAMO_H

#include <string>
#include <vector>
#include "database.h"

class Prestamo {
private:
    int id_prestamo;
    int id_libro;
    int id_usuario;
    std::string fecha_prestamo;
    std::string fecha_devolucion;
    std::string fecha_real_devolucion;

public:
    Prestamo(int id, int idLibro, int idUsuario,
             const std::string& fechaPrestamo,
             const std::string& fechaDevolucion,
             const std::string& fechaRealDevolucion);

    int getId() const;
    int getIdLibro() const;
    int getIdUsuario() const;
    std::string getFechaPrestamo() const;
    std::string getFechaDevolucion() const;
    std::string getFechaRealDevolucion() const;

    // CRUD estático
    static bool crear(Database& db,
                      int idLibro,
                      int idUsuario,
                      const std::string& fechaPrestamo,
                      const std::string& fechaDevolucion);
    static std::vector<Prestamo> listar(Database& db);
    static bool actualizar(Database& db,
                           int id,
                           int idLibro,
                           int idUsuario,
                           const std::string& fechaPrestamo,
                           const std::string& fechaDevolucion,
                           const std::string& fechaRealDevolucion);
    static bool eliminar(Database& db, int id);
};

#endif

