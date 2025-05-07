#include "Prestamo.h"

Prestamo::Prestamo(
	int id, 
	int idLibro, 
	int idUsuario, 
	const std::string& fechaPrestamo,
	const std::string& fechaDevolucion, 
	const std::string& fechaRealDevolucion)
    : id_prestamo(id), 
    id_libro(idLibro), 
    id_usuario(idUsuario),
      fecha_prestamo(fechaPrestamo), 
      fecha_devolucion(fechaDevolucion),
      fecha_real_devolucion(fechaRealDevolucion) {}

int Prestamo::getId() const { 
	return id_prestamo; 
}
int Prestamo::getIdLibro() const { 
	return id_libro; 
}
int Prestamo::getIdUsuario() const { 
	return id_usuario; 
}
std::string Prestamo::getFechaPrestamo() const { 
	return fecha_prestamo; 
}
std::string Prestamo::getFechaDevolucion() const { 
	return fecha_devolucion; 
}
std::string Prestamo::getFechaRealDevolucion() const { 
	return fecha_real_devolucion; 
}

