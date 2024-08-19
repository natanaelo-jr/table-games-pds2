# Variáveis
CXX := g++
CXX_FLAGS := -Wall -Wextra -std=c++11 -ggdb

# Diretórios
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
INCLUDE_DIR := include
TEST_DIR := tests

# SFML
SFML_FLAGS := -lsfml-graphics -lsfml-window -lsfml-system

# Arquivos
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECT_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
EXECUTABLE := $(BIN_DIR)/main

# Arquivo de teste
TEST_SOURCE := $(TEST_DIR)/test_Reversi.cpp
TEST_OBJECT_FILE := $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TEST_SOURCE))
TEST_EXECUTABLE := $(BIN_DIR)/test

# Regra padrão
all: createbin createobj $(EXECUTABLE)

# Compilação do programa principal
$(EXECUTABLE): $(OBJECT_FILES)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE_DIR) $^ -o $@ $(SFML_FLAGS)

# Compilação dos arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compilação dos testes
test: createbin createobj $(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(filter-out $(OBJ_DIR)/main.o, $(OBJECT_FILES)) $(TEST_OBJECT_FILE)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE_DIR) $^ -o $@ $(SFML_FLAGS)

$(OBJ_DIR)/%.o: $(TEST_SOURCE)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Criação dos diretórios
createbin:
	mkdir -p $(BIN_DIR)

createobj:
	mkdir -p $(OBJ_DIR)

# Limpeza dos arquivos compilados
clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/*

.PHONY: all clean test createbin createobj