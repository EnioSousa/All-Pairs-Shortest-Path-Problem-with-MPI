 # source directory
SRC_DIR := src
 # Object directory (*.o)
OBJ_DIR := obj
 # Executables directory
BIN_DIR := bin
 # Headers file directory
INCLUDE_DIR := include
# Data directory
DATA_DIR := data
# Executable path name
EXE := $(BIN_DIR)/fox

# Compiler program
CC := mpicc
# Include directories in search path
CFLAGS := -I$(INCLUDE_DIR)
LFLAGS := -lm

# How to run
RP := mpirun
RFLAGS := -np 9
FILENAME := input300

SRC := $(wildcard $(SRC_DIR)/*.c)
DEP := $(wildcard $(INCLUDE_DIR)/*.h)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
.PHONY: all compile clean run runTestHome runTestLab testHome testLab

 # Compile and run
all: compile

compile: $(OBJ_DIR) $(BIN_DIR) $(EXE) 

run: compile
	$(RP) $(RFLAGS) --oversubscribe ./$(EXE) 

runTestLab: compile testLab
runTestHome: compile testHome

testLab: $(DATA_DIR)/input* 
	for file in $^; do \
		echo FILE: $$file; \
		for number in 16 9 4; do \
			echo NP: $$number; \
			$(RP) -np $$number --hostfile ./hostfile --map-by node ./$(EXE) < $$file; \
		done; \
		echo; \
	done

testHome: $(DATA_DIR)/input* 
	for file in $^; do \
		echo FILE: $$file; \
		for number in 16 9 4; do \
			echo NP: $$number; \
			$(RP) -np $$number  --oversubscribe ./$(EXE) < $$file; \
		done; \
		echo; \
	done

# Create bin and obj directory in case they dont exist
$(OBJ_DIR) $(BIN_DIR) $(DATA_DIR):
	mkdir -p $@

# Generate the object file without linking 
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEP)
	$(CC) $(CFLAGS) -c $< -o $@

# Link the object files into a executable. Also checks if 
# the object directory exists, if not creates it
$(EXE): $(OBJ) 
	$(CC) $^ -o $@ $(LFLAGS)

clean:
	@rm -vf $(BIN_DIR)/*
	@rm -vf $(OBJ_DIR)/*.o