# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude -Iinclude/modelos -Iinclude/sistema -Iinclude/utils

# Directorios
SRC_DIR = src
OBJ_DIR = build
BIN_DIR = .

# Archivos
SOURCES = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
TARGET = $(BIN_DIR)/bankqueue

# Colores para output
GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m # No Color

# Regla principal
all: $(TARGET)
	@echo "$(GREEN)✓ Compilación exitosa!$(NC)"

# Compilar el ejecutable
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compilar archivos .cpp a .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compilando: $<$(NC)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ejecutar el programa
run: $(TARGET)
	@echo "$(GREEN)Ejecutando BankQueue...$(NC)"
	@./$(TARGET)

# Limpiar archivos compilados
clean:
	@echo "$(YELLOW)Limpiando archivos...$(NC)"
	@rm -rf $(OBJ_DIR) $(TARGET)
	@echo "$(GREEN)✓ Limpieza completada$(NC)"

# Recompilar todo desde cero
rebuild: clean all

# Mostrar ayuda
help:
	@echo "Comandos disponibles:"
	@echo "  make          - Compilar el proyecto"
	@echo "  make run      - Compilar y ejecutar"
	@echo "  make clean    - Limpiar archivos compilados"
	@echo "  make rebuild  - Limpiar y recompilar"
	@echo "  make help     - Mostrar esta ayuda"

.PHONY: all run clean rebuild help