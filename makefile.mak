# Nombre del ejecutable
TARGET = carrera

# Comando del compilador y las banderas
CXX = g++
CXXFLAGS = -std=c++11 -pthread

# Archivo fuente
SRC = tarea_1.cpp

# Archivo objeto generado
OBJ = $(SRC:.cpp=.o)

# Regla por defecto (compilar el programa)
all: $(TARGET)

# Regla para compilar el ejecutable
$(TARGET): $(OBJ)
	$(CXX) -o $(TARGET) $(OBJ) $(CXXFLAGS)

# Regla para compilar el archivo objeto
$(OBJ): $(SRC)
	$(CXX) -c $(SRC) $(CXXFLAGS)

# Limpiar los archivos generados
clean:
	rm -f $(OBJ) $(TARGET)
