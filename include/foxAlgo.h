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

/*
    Function: Print final result
    ------------------------------------ 
    Change the order of elements inside of array res and print the ordered array

    res: int pointer
    nProc: number of process
    matrixSize: size of the matrix read
	localMatrixSize: size of the matrix inside of process
	
    return: void
*/

void printResult(int *res, int nProc, int matrixSize, int localMatrixSize);

#endif
