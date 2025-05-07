function cargarSecciones() {
    fetch('/secciones')
        .then(response => response.json())
        .then(data => {
            let contenido = '<h2>Secciones</h2><table><tr><th>ID</th><th>Nombre</th><th>Acciones</th></tr>';
            data.forEach(seccion => {
                contenido += `<tr><td>${seccion.id}</td><td>${seccion.nombre}</td><td>
                    <button onclick="eliminarSeccion(${seccion.id})">Eliminar</button>
                    <button onclick="mostrarFormularioActualizarSeccion(${seccion.id}, '${seccion.nombre}')">Actualizar</button>
                </td></tr>`;
            });
            contenido += '</table>';
            contenido += `
                <form onsubmit="crearSeccion(event)">
                    <h3>Crear Sección</h3>
                    <input type="text" id="nombreSeccion" placeholder="Nombre" required>
                    <button type="submit">Crear</button>
                </form>
                <div id="formularioActualizarSeccion"></div>
            `;
            document.getElementById('datos').innerHTML = contenido;
        });
}

function crearSeccion(event) {
    event.preventDefault();
    const nombre = document.getElementById('nombreSeccion').value.trim();
    if (!nombre) {
        alert("El nombre de la sección no puede estar vacío.");
        return;
    }
    console.log("Sending data:", { nombre });
    fetch('/secciones', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ nombre: nombre }),
    })
    .then(response => response.json())
    .then(data => {
        console.log("Server response:", data);
        alert(data.mensaje);
        cargarSecciones();
    })
    .catch(error => {
        console.error("Error:", error);
    });
}

function eliminarSeccion(id) {
    console.log("Attempting to delete section with ID:", id);
    fetch('/secciones', {
        method: 'DELETE',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ id: id }),
    })
    .then(response => {
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        return response.json();
    })
    .then(data => {
        console.log("Server response:", data);
        alert(data.mensaje);
        cargarSecciones();
    })
    .catch(error => {
        console.error("Error:", error);
    });
}

function mostrarFormularioActualizarSeccion(id, nombre) {
    const formulario = `
        <form onsubmit="actualizarSeccion(event, ${id})">
            <h3>Actualizar Sección</h3>
            <input type="text" id="nuevoNombreSeccion" value="${nombre}" required>
            <button type="submit">Actualizar</button>
        </form>
    `;
    document.getElementById('formularioActualizarSeccion').innerHTML = formulario;
}

function actualizarSeccion(event, id) {
    event.preventDefault();
    const nuevoNombre = document.getElementById('nuevoNombreSeccion').value.trim();
    if (!nuevoNombre) {
        alert("El nombre de la sección no puede estar vacío.");
        return;
    }
    fetch('/secciones', {
        method: 'PUT',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ id: id, nombre: nuevoNombre }),
    })
    .then(response => response.json())
    .then(data => {
        alert(data.mensaje);
        cargarSecciones();
    });
}

function cargarAutores() {
    fetch('/autores')
        .then(response => response.json())
        .then(data => {
            let contenido = '<h2>Autores</h2><table><tr><th>ID</th><th>Nombre Completo</th><th>Acciones</th></tr>';
            data.forEach(autor => {
                contenido += `<tr><td>${autor.id}</td><td>${autor.nombre}</td><td>
                    <button onclick="eliminarAutor(${autor.id})">Eliminar</button>
                    <button onclick="mostrarFormularioActualizarAutor(${autor.id}, '${autor.nombre}')">Actualizar</button>
                </td></tr>`;
            });
            contenido += '</table>';
            contenido += `
                <form onsubmit="crearAutor(event)">
                    <h3>Crear Autor</h3>
                    <input type="text" id="nombreAutor" placeholder="Nombre" required>
                    <input type="text" id="apellidosAutor" placeholder="Apellidos" required>
                    <button type="submit">Crear</button>
                </form>
                <div id="formularioActualizarAutor"></div>
            `;
            document.getElementById('datos').innerHTML = contenido;
        });
}

function crearAutor(event) {
    event.preventDefault();
    const nombre = document.getElementById('nombreAutor').value.trim();
    const apellidos = document.getElementById('apellidosAutor').value.trim();
    if (!nombre || !apellidos) {
        alert("El nombre y los apellidos no pueden estar vacíos.");
        return;
    }
    console.log("Sending data:", { nombre, apellidos });
    fetch('/autores', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ nombre: nombre, apellidos: apellidos }),
    })
    .then(response => response.json())
    .then(data => {
        console.log("Server response:", data);
        alert(data.mensaje);
        cargarAutores();
    })
    .catch(error => {
        console.error("Error:", error);
    });
}

function eliminarAutor(id) {
    console.log("Attempting to delete author with ID:", id);
    fetch('/autores', {
        method: 'DELETE',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ id: id }),
    })
    .then(response => {
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        return response.json();
    })
    .then(data => {
        console.log("Server response:", data);
        alert(data.mensaje);
        cargarAutores();
    })
    .catch(error => {
        console.error("Error:", error);
    });
}

function mostrarFormularioActualizarAutor(id, nombre) {
    const formulario = `
        <form onsubmit="actualizarAutor(event, ${id})">
            <h3>Actualizar Autor</h3>
            <input type="text" id="nuevoNombreAutor" value="${nombre.split(' ')[0]}" required>
            <input type="text" id="nuevosApellidosAutor" value="${nombre.split(' ')[1]}" required>
            <button type="submit">Actualizar</button>
        </form>
    `;
    document.getElementById('formularioActualizarAutor').innerHTML = formulario;
}

function actualizarAutor(event, id) {
    event.preventDefault();
    const nuevoNombre = document.getElementById('nuevoNombreAutor').value.trim();
    const nuevosApellidos = document.getElementById('nuevosApellidosAutor').value.trim();
    if (!nuevoNombre || !nuevosApellidos) {
        alert("El nombre y los apellidos no pueden estar vacíos.");
        return;
    }
    fetch('/autores', {
        method: 'PUT',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ id: id, nombre: nuevoNombre, apellidos: nuevosApellidos }),
    })
    .then(response => response.json())
    .then(data => {
        alert(data.mensaje);
        cargarAutores();
    });
}

function cargarLibros() {
    fetch('/libros')
        .then(response => response.json())
        .then(data => {
            let contenido = '<h2>Libros</h2><table><tr><th>ID</th><th>Título</th><th>ISBN</th><th>Año</th><th>AutorID</th><th>SecciónID</th><th>Acciones</th></tr>';
            data.forEach(libro => {
                contenido += `<tr><td>${libro.id}</td><td>${libro.titulo}</td><td>${libro.isbn}</td><td>${libro.anio}</td><td>${libro.idAutor}</td><td>${libro.idSeccion}</td><td>
                    <button onclick="eliminarLibro(${libro.id})">Eliminar</button>
                    <button onclick="mostrarFormularioActualizarLibro(${libro.id}, '${libro.titulo}', '${libro.isbn}', ${libro.anio}, ${libro.idAutor}, ${libro.idSeccion})">Actualizar</button>
                </td></tr>`;
            });
            contenido += '</table>';
            contenido += `
                <form onsubmit="crearLibro(event)">
                    <h3>Crear Libro</h3>
                    <input type="text" id="tituloLibro" placeholder="Título" required>
                    <input type="text" id="isbnLibro" placeholder="ISBN" required>
                    <input type="number" id="anioLibro" placeholder="Año" required>
                    <input type="number" id="idAutorLibro" placeholder="ID Autor" required>
                    <input type="number" id="idSeccionLibro" placeholder="ID Sección" required>
                    <button type="submit">Crear</button>
                </form>
                <div id="formularioActualizarLibro"></div>
            `;
            document.getElementById('datos').innerHTML = contenido;
        });
}

function crearLibro(event) {
    event.preventDefault();
    const titulo = document.getElementById('tituloLibro').value.trim();
    const isbn = document.getElementById('isbnLibro').value.trim();
    const anio = document.getElementById('anioLibro').value.trim();
    const idAutor = document.getElementById('idAutorLibro').value.trim();
    const idSeccion = document.getElementById('idSeccionLibro').value.trim();

    if (!titulo || !isbn || !anio || !idAutor || !idSeccion) {
        alert("Todos los campos son obligatorios.");
        return;
    }

    if (isNaN(anio) || isNaN(idAutor) || isNaN(idSeccion)) {
        alert("Los campos Año, ID Autor y ID Sección deben ser números.");
        return;
    }

    fetch('/libros', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ titulo: titulo, isbn: isbn, anio: anio, idAutor: idAutor, idSeccion: idSeccion }),
    })
    .then(response => response.json())
    .then(data => {
        alert(data.mensaje);
        cargarLibros();
    });
}

function eliminarLibro(id) {
    console.log("Attempting to delete book with ID:", id);
    fetch('/libros', {
        method: 'DELETE',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ id: id }),
    })
    .then(response => {
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        return response.json();
    })
    .then(data => {
        console.log("Server response:", data);
        alert(data.mensaje);
        cargarLibros();
    })
    .catch(error => {
        console.error("Error:", error);
    });
}

function mostrarFormularioActualizarLibro(id, titulo, isbn, anio, idAutor, idSeccion) {
    const formulario = `
        <form onsubmit="actualizarLibro(event, ${id})">
            <h3>Actualizar Libro</h3>
            <input type="text" id="nuevoTituloLibro" value="${titulo}" required>
            <input type="text" id="nuevoIsbnLibro" value="${isbn}" required>
            <input type="number" id="nuevoAnioLibro" value="${anio}" required>
            <input type="number" id="nuevoIdAutorLibro" value="${idAutor}" required>
            <input type="number" id="nuevoIdSeccionLibro" value="${idSeccion}" required>
            <button type="submit">Actualizar</button>
        </form>
    `;
    document.getElementById('formularioActualizarLibro').innerHTML = formulario;
}

function actualizarLibro(event, id) {
    event.preventDefault();
    const nuevoTitulo = document.getElementById('nuevoTituloLibro').value.trim();
    const nuevoIsbn = document.getElementById('nuevoIsbnLibro').value.trim();
    const nuevoAnio = document.getElementById('nuevoAnioLibro').value.trim();
    const nuevoIdAutor = document.getElementById('nuevoIdAutorLibro').value.trim();
    const nuevoIdSeccion = document.getElementById('nuevoIdSeccionLibro').value.trim();

    if (!nuevoTitulo || !nuevoIsbn || !nuevoAnio || !nuevoIdAutor || !nuevoIdSeccion) {
        alert("Todos los campos son obligatorios.");
        return;
    }

    if (isNaN(nuevoAnio) || isNaN(nuevoIdAutor) || isNaN(nuevoIdSeccion)) {
        alert("Los campos Año, ID Autor y ID Sección deben ser números.");
        return;
    }

    fetch('/libros', {
        method: 'PUT',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ id: id, titulo: nuevoTitulo, isbn: nuevoIsbn, anio: nuevoAnio, idAutor: nuevoIdAutor, idSeccion: nuevoIdSeccion }),
    })
    .then(response => response.json())
    .then(data => {
        alert(data.mensaje);
        cargarLibros();
    });
}

function cargarUsuarios() {
    fetch('/usuarios')
        .then(response => response.json())
        .then(data => {
            let contenido = '<h2>Usuarios</h2><table><tr><th>ID</th><th>Nombre Completo</th><th>Email</th><th>Fecha Alta</th><th>Acciones</th></tr>';
            data.forEach(usuario => {
                contenido += `<tr><td>${usuario.id}</td><td>${usuario.nombre}</td><td>${usuario.email}</td><td>${usuario.fechaAlta}</td><td>
                    <button onclick="eliminarUsuario(${usuario.id})">Eliminar</button>
                    <button onclick="mostrarFormularioActualizarUsuario(${usuario.id}, '${usuario.nombre}', '${usuario.email}')">Actualizar</button>
                </td></tr>`;
            });
            contenido += '</table>';
            contenido += `
                <form onsubmit="crearUsuario(event)">
                    <h3>Crear Usuario</h3>
                    <input type="text" id="nombreUsuario" placeholder="Nombre" required>
                    <input type="text" id="apellidosUsuario" placeholder="Apellidos" required>
                    <input type="email" id="emailUsuario" placeholder="Email" required>
                    <button type="submit">Crear</button>
                </form>
                <div id="formularioActualizarUsuario"></div>
            `;
            document.getElementById('datos').innerHTML = contenido;
        });
}

function crearUsuario(event) {
    event.preventDefault();
    const nombre = document.getElementById('nombreUsuario').value.trim();
    const apellidos = document.getElementById('apellidosUsuario').value.trim();
    const email = document.getElementById('emailUsuario').value.trim();

    if (!nombre || !apellidos || !email) {
        alert("Todos los campos son obligatorios.");
        return;
    }

    fetch('/usuarios', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ nombre: nombre, apellidos: apellidos, email: email }),
    })
    .then(response => response.json())
    .then(data => {
        alert(data.mensaje);
        cargarUsuarios();
    });
}

function eliminarUsuario(id) {
    console.log("Attempting to delete user with ID:", id);
    fetch('/usuarios', {
        method: 'DELETE',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ id: id }),
    })
    .then(response => {
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        return response.json();
    })
    .then(data => {
        console.log("Server response:", data);
        alert(data.mensaje);
        cargarUsuarios();
    })
    .catch(error => {
        console.error("Error:", error);
    });
}

function mostrarFormularioActualizarUsuario(id, nombre, email) {
    const formulario = `
        <form onsubmit="actualizarUsuario(event, ${id})">
            <h3>Actualizar Usuario</h3>
            <input type="text" id="nuevoNombreUsuario" value="${nombre.split(' ')[0]}" required>
            <input type="text" id="nuevosApellidosUsuario" value="${nombre.split(' ')[1]}" required>
            <input type="email" id="nuevoEmailUsuario" value="${email}" required>
            <button type="submit">Actualizar</button>
        </form>
    `;
    document.getElementById('formularioActualizarUsuario').innerHTML = formulario;
}

function actualizarUsuario(event, id) {
    event.preventDefault();
    const nuevoNombre = document.getElementById('nuevoNombreUsuario').value.trim();
    const nuevosApellidos = document.getElementById('nuevosApellidosUsuario').value.trim();
    const nuevoEmail = document.getElementById('nuevoEmailUsuario').value.trim();

    if (!nuevoNombre || !nuevosApellidos || !nuevoEmail) {
        alert("Todos los campos son obligatorios.");
        return;
    }

    fetch('/usuarios', {
        method: 'PUT',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ id: id, nombre: nuevoNombre, apellidos: nuevosApellidos, email: nuevoEmail }),
    })
    .then(response => response.json())
    .then(data => {
        alert(data.mensaje);
        cargarUsuarios();
    });
}

function cargarPrestamos() {
    fetch('/prestamos')
        .then(response => response.json())
        .then(data => {
            let contenido = '<h2>Préstamos</h2><table><tr><th>ID</th><th>LibroID</th><th>UsuarioID</th><th>Fecha Préstamo</th><th>Fecha Devolución</th><th>Fecha Real Devolución</th><th>Acciones</th></tr>';
            data.forEach(prestamo => {
                contenido += `<tr><td>${prestamo.id}</td><td>${prestamo.idLibro}</td><td>${prestamo.idUsuario}</td><td>${prestamo.fechaPrestamo}</td><td>${prestamo.fechaDevolucion}</td><td>${prestamo.fechaRealDevolucion}</td><td>
                    <button onclick="eliminarPrestamo(${prestamo.id})">Eliminar</button>
                    <button onclick="mostrarFormularioActualizarPrestamo(${prestamo.id}, ${prestamo.idLibro}, ${prestamo.idUsuario}, '${prestamo.fechaPrestamo}', '${prestamo.fechaDevolucion}', '${prestamo.fechaRealDevolucion}')">Actualizar</button>
                </td></tr>`;
            });
            contenido += '</table>';
            contenido += `
                <form onsubmit="crearPrestamo(event)">
                    <h3>Crear Préstamo</h3>
                    <input type="number" id="idLibroPrestamo" placeholder="ID Libro" required>
                    <input type="number" id="idUsuarioPrestamo" placeholder="ID Usuario" required>
                    <input type="date" id="fechaPrestamo" placeholder="Fecha Préstamo" required>
                    <input type="date" id="fechaDevolucion" placeholder="Fecha Devolución" required>
                    <button type="submit">Crear</button>
                </form>
                <div id="formularioActualizarPrestamo"></div>
            `;
            document.getElementById('datos').innerHTML = contenido;
        });
}

function crearPrestamo(event) {
    event.preventDefault();
    const idLibro = document.getElementById('idLibroPrestamo').value.trim();
    const idUsuario = document.getElementById('idUsuarioPrestamo').value.trim();
    const fechaPrestamo = document.getElementById('fechaPrestamo').value.trim();
    const fechaDevolucion = document.getElementById('fechaDevolucion').value.trim();

    if (!idLibro || !idUsuario || !fechaPrestamo || !fechaDevolucion) {
        alert("Todos los campos son obligatorios.");
        return;
    }

    if (isNaN(idLibro) || isNaN(idUsuario)) {
        alert("Los campos ID Libro y ID Usuario deben ser números.");
        return;
    }

    fetch('/prestamos', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ idLibro: idLibro, idUsuario: idUsuario, fechaPrestamo: fechaPrestamo, fechaDevolucion: fechaDevolucion }),
    })
    .then(response => response.json())
    .then(data => {
        alert(data.mensaje);
        cargarPrestamos();
    });
}

function eliminarPrestamo(id) {
    console.log("Attempting to delete loan with ID:", id);
    fetch('/prestamos', {
        method: 'DELETE',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ id: id }),
    })
    .then(response => {
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        return response.json();
    })
    .then(data => {
        console.log("Server response:", data);
        alert(data.mensaje);
        cargarPrestamos();
    })
    .catch(error => {
        console.error("Error:", error);
    });
}

function mostrarFormularioActualizarPrestamo(id, idLibro, idUsuario, fechaPrestamo, fechaDevolucion, fechaRealDevolucion) {
    const formulario = `
        <form onsubmit="actualizarPrestamo(event, ${id})">
            <h3>Actualizar Préstamo</h3>
            <input type="number" id="nuevoIdLibroPrestamo" value="${idLibro}" required>
            <input type="number" id="nuevoIdUsuarioPrestamo" value="${idUsuario}" required>
            <input type="date" id="nuevaFechaPrestamo" value="${fechaPrestamo}" required>
            <input type="date" id="nuevaFechaDevolucion" value="${fechaDevolucion}" required>
            <input type="date" id="nuevaFechaRealDevolucion" value="${fechaRealDevolucion}">
            <button type="submit">Actualizar</button>
        </form>
    `;
    document.getElementById('formularioActualizarPrestamo').innerHTML = formulario;
}

function actualizarPrestamo(event, id) {
    event.preventDefault();
    const nuevoIdLibro = document.getElementById('nuevoIdLibroPrestamo').value.trim();
    const nuevoIdUsuario = document.getElementById('nuevoIdUsuarioPrestamo').value.trim();
    const nuevaFechaPrestamo = document.getElementById('nuevaFechaPrestamo').value.trim();
    const nuevaFechaDevolucion = document.getElementById('nuevaFechaDevolucion').value.trim();
    const nuevaFechaRealDevolucion = document.getElementById('nuevaFechaRealDevolucion').value.trim();

    if (!nuevoIdLibro || !nuevoIdUsuario || !nuevaFechaPrestamo || !nuevaFechaDevolucion) {
        alert("Todos los campos son obligatorios.");
        return;
    }

    if (isNaN(nuevoIdLibro) || isNaN(nuevoIdUsuario)) {
        alert("Los campos ID Libro y ID Usuario deben ser números.");
        return;
    }

    fetch('/prestamos', {
        method: 'PUT',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ id: id, idLibro: nuevoIdLibro, idUsuario: nuevoIdUsuario, fechaPrestamo: nuevaFechaPrestamo, fechaDevolucion: nuevaFechaDevolucion, fechaRealDevolucion: nuevaFechaRealDevolucion }),
    })
    .then(response => response.json())
    .then(data => {
        alert(data.mensaje);
        cargarPrestamos();
    });
}

