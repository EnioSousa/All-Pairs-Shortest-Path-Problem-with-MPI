#ifndef FOXALGO
#define FOXALGO

#include <mpi.h>

#include <stdio.h>
#include <limits.h>

#include "basicFunc.h"
#include "gridComm.h"


/*
    Function: Fox algorithm
    ------------------------------------ 
*/

void Fox(int n, GridInfoType* grid, Matrix* local_A, Matrix* local_B, Matrix* local_C);

#endif
