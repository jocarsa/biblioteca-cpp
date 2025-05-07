function cargarSecciones() {
    fetch('/secciones')
        .then(response => response.json())
        .then(data => {
            let contenido = '<h2>Secciones</h2><table><tr><th>ID</th><th>Nombre</th></tr>';
            data.forEach(seccion => {
                contenido += `<tr><td>${seccion.id}</td><td>${seccion.nombre}</td></tr>`;
            });
            contenido += '</table>';
            document.getElementById('datos').innerHTML = contenido;
        });
}

function cargarAutores() {
    fetch('/autores')
        .then(response => response.json())
        .then(data => {
            let contenido = '<h2>Autores</h2><table><tr><th>ID</th><th>Nombre Completo</th></tr>';
            data.forEach(autor => {
                contenido += `<tr><td>${autor.id}</td><td>${autor.nombre}</td></tr>`;
            });
            contenido += '</table>';
            document.getElementById('datos').innerHTML = contenido;
        });
}

function cargarLibros() {
    fetch('/libros')
        .then(response => response.json())
        .then(data => {
            let contenido = '<h2>Libros</h2><table><tr><th>ID</th><th>Título</th><th>ISBN</th><th>Año</th><th>AutorID</th><th>SecciónID</th></tr>';
            data.forEach(libro => {
                contenido += `<tr><td>${libro.id}</td><td>${libro.titulo}</td><td>${libro.isbn}</td><td>${libro.anio}</td><td>${libro.idAutor}</td><td>${libro.idSeccion}</td></tr>`;
            });
            contenido += '</table>';
            document.getElementById('datos').innerHTML = contenido;
        });
}

function cargarUsuarios() {
    fetch('/usuarios')
        .then(response => response.json())
        .then(data => {
            let contenido = '<h2>Usuarios</h2><table><tr><th>ID</th><th>Nombre Completo</th><th>Email</th><th>Fecha Alta</th></tr>';
            data.forEach(usuario => {
                contenido += `<tr><td>${usuario.id}</td><td>${usuario.nombre}</td><td>${usuario.email}</td><td>${usuario.fechaAlta}</td></tr>`;
            });
            contenido += '</table>';
            document.getElementById('datos').innerHTML = contenido;
        });
}

function cargarPrestamos() {
    fetch('/prestamos')
        .then(response => response.json())
        .then(data => {
            let contenido = '<h2>Préstamos</h2><table><tr><th>ID</th><th>LibroID</th><th>UsuarioID</th><th>Fecha Préstamo</th><th>Fecha Devolución</th><th>Fecha Real Devolución</th></tr>';
            data.forEach(prestamo => {
                contenido += `<tr><td>${prestamo.id}</td><td>${prestamo.idLibro}</td><td>${prestamo.idUsuario}</td><td>${prestamo.fechaPrestamo}</td><td>${prestamo.fechaDevolucion}</td><td>${prestamo.fechaRealDevolucion}</td></tr>`;
            });
            contenido += '</table>';
            document.getElementById('datos').innerHTML = contenido;
        });
}

