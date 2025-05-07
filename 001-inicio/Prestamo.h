#ifndef PRESTAMO_H
#define PRESTAMO_H

#include <string>

class Prestamo {
private:
    int id_prestamo;
    int id_libro;
    int id_usuario;
    std::string fecha_prestamo;
    std::string fecha_devolucion;
    std::string fecha_real_devolucion;

public:
    Prestamo(int id, int idLibro, int idUsuario, const std::string& fechaPrestamo,
             const std::string& fechaDevolucion, const std::string& fechaRealDevolucion);
    int getId() const;
    int getIdLibro() const;
    int getIdUsuario() const;
    std::string getFechaPrestamo() const;
    std::string getFechaDevolucion() const;
    std::string getFechaRealDevolucion() const;
};

#endif

