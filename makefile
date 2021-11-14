SRC_DIR := src # source directory
OBJ_DIR := obj # Object directory (*.o)
BIN_DIR := bin # Executables directory
INCLUDE_DIR := include # Headers file directory

CC = gcc # Compiler program
CFLAGS := -I$(INCLUDE_DIR) # Include directories in search path
 
EXE := $(BIN_DIR)/fox # Executable path name

SRC := $(wildcard $(SRC_DIR)/*.c)
DEP := $(wildcard $(INCLUDE_DIR)/*.h)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

.PHONY: all compile clean run

all: compile run # Compile and run

run:
	./$(EXE)

compile: $(EXE)

# Link the object files into a executable. Also checks if 
# the object directory exists, if not creates it
$(EXE): $(OBJ) | $(OBJ_DIR)
	$(CC) $^ -o $@

# Generate the object file without linking 
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEP)
	$(CC) $(CFLAGS) -c $< -o $@

# Create bin and obj directory in case they dont exist
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

clean:
	@rm -vf $(BIN_DIR)/*
	@rm -vf $(OBJ_DIR)/*.o