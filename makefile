 # source directory
SRC_DIR := src
 # Object directory (*.o)
OBJ_DIR := obj
 # Executables directory
BIN_DIR := bin
 # Headers file directory
INCLUDE_DIR := include
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

.PHONY: all compile clean run runTestHome runTestLab

 # Compile and run
all: compile run

runTestLab:
	$(RP) -np 1 --hostfile ./hostfile --map-by node ./$(EXE) input4
	$(RP) -np 1 --hostfile ./hostfile --map-by node ./$(EXE) input6
	$(RP) -np 1 --hostfile ./hostfile --map-by node ./$(EXE) input300
	$(RP) -np 1 --hostfile ./hostfile --map-by node ./$(EXE) input600
	$(RP) -np 1 --hostfile ./hostfile --map-by node ./$(EXE) input1200
	$(RP) -np 4 --hostfile ./hostfile --map-by node ./$(EXE) input4
	$(RP) -np 4 --hostfile ./hostfile --map-by node ./$(EXE) input6
	$(RP) -np 4 --hostfile ./hostfile --map-by node ./$(EXE) input300
	$(RP) -np 4 --hostfile ./hostfile --map-by node ./$(EXE) input600
	$(RP) -np 4 --hostfile ./hostfile --map-by node ./$(EXE) input1200
	$(RP) -np 9 --hostfile ./hostfile --map-by node ./$(EXE) input6
	$(RP) -np 9 --hostfile ./hostfile --map-by node ./$(EXE) input300
	$(RP) -np 9 --hostfile ./hostfile --map-by node ./$(EXE) input600
	$(RP) -np 9 --hostfile ./hostfile --map-by node ./$(EXE) input1200
	$(RP) -np 16 --hostfile ./hostfile --map-by node ./$(EXE) input300
	$(RP) -np 16 --hostfile ./hostfile --map-by node ./$(EXE) input600
	$(RP) -np 16 --hostfile ./hostfile --map-by node ./$(EXE) input1200


runTestHome:
	$(RP) -np 4  --oversubscribe ./$(EXE) input4
	$(RP) -np 4  --oversubscribe ./$(EXE) input6
	$(RP) -np 4  --oversubscribe ./$(EXE) input300
	$(RP) -np 9  --oversubscribe ./$(EXE) input6
	$(RP) -np 9  --oversubscribe ./$(EXE) input300
	$(RP) -np 9  --oversubscribe ./$(EXE) input600
	$(RP) -np 16 --oversubscribe ./$(EXE) input300
	$(RP) -np 16  --oversubscribe ./$(EXE) input600

run:
	$(RP) $(RFLAGS) --oversubscribe ./$(EXE) $(FILENAME)

compile: $(OBJ_DIR) $(BIN_DIR) $(EXE) 

# Create bin and obj directory in case they dont exist
$(OBJ_DIR) $(BIN_DIR):
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
