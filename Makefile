EXE := .exe

CC := gcc # trocar pelo comando do compilador C

BIN_DIR := bin
SRC_DIR := src

INCLUDE_DIRS := include C:/msys64/ucrt64/include # trocar pela pasta include do compilador C
INCLUDE := $(addprefix -I,$(INCLUDE_DIRS))

C_SOURCES := $(SRC_DIR)/grafos.c $(SRC_DIR)/leitor_grafo.c $(SRC_DIR)/main.c
C_OBJECTS := $(BIN_DIR)/grafos.o $(BIN_DIR)/leitor_grafo.o $(BIN_DIR)/main.o

TARGET := $(BIN_DIR)/main$(EXE)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(C_OBJECTS) | $(BIN_DIR)
	$(CXX) $(INCLUDE) $^ -o $@

$(BIN_DIR)/main.o: $(SRC_DIR)/main.c
	@mkdir -p $(dir $@)
	$(CC) $(INCLUDE) -c $< -o $@

$(BIN_DIR)/grafos.o: $(SRC_DIR)/grafos.c
	@mkdir -p $(dir $@)
	$(CC) $(INCLUDE) -c $< -o $@

$(BIN_DIR)/leitor_grafo.o: $(SRC_DIR)/leitor_grafo.c
	@mkdir -p $(dir $@)
	$(CC) $(INCLUDE) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)