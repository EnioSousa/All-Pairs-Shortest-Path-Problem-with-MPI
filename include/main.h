#ifndef MAINSTUFF
#define MAINSTUFF

#include <mpi.h>

#include "readData.h"
#include "gridComm.h"
#include "foxAlgo.h"
#include <limits.h>
#include <string.h>

// If true then print the state of the program through its execution
#define VERBOSE 0

// If true then print the output machine
#define WANT_OUTPUT 1

// If true then we compare our output with the expected output
#define WANT_COMPARE 0

// If true print execution time
#define WANT_TIME 0

#endif
