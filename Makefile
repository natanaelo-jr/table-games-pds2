CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++11 -ggdb

BIN		:= bin
SRC		:= src
INCLUDE	:= include
OBJECTS := obj
LIBRARIES	:=
EXECUTABLE	:= main
SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECT_FILES := $(patsubst $(SRC)/%.cpp, $(OBJECTS)/%.o, $(SOURCES))


all: createbin createobj $(BIN)/$(EXECUTABLE)

createbin:
	mkdir -p $(BIN)

createobj:
	mkdir -p $(OBJECTS)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(OBJECT_FILES)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

$(OBJECTS)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	-rm $(BIN)/*
	-rm $(OBJECTS)/*