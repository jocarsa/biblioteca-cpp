CXX = g++
CXXFLAGS = -std=c++11 -I.
LDFLAGS = -lsqlite3
SRCS = main.cpp WebServer.cpp database.cpp Autor.cpp Libro.cpp Prestamo.cpp Seccion.cpp Usuario.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = biblioteca_servidor

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

