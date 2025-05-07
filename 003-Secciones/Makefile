CXX = g++
CXXFLAGS = -std=c++17
LDFLAGS = -lsqlite3

SRCS = main.cpp Autor.cpp Seccion.cpp Libro.cpp Usuario.cpp Prestamo.cpp database.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = biblioteca

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)
