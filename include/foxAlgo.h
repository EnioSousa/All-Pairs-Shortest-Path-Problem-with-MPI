#ifndef FOXALGO
#define FOXALGO

#include <mpi.h>

#include <stdio.h>
#include <limits.h>

#include "basicFunc.h"
#include "gridComm.h"

/**
 * @brief 
 * 
 * @param grid 
 * @param localA 
 * @param localB 
 * @param localC 
 */
void fox(GridInfoType* grid, Matrix* localA, Matrix *localB, Matrix *localC);

#endif
