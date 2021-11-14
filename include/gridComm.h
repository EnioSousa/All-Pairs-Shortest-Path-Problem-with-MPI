#ifndef GRIDCOMM
#define GRIDCOOM

#include <mpi.h>

#include "errorMsg.h"
#include "basicFunc.h"
#include "math.h"

#define PERIODIC 1
#define NONPERIODIC 0
#define NONVALUE -1

/*
    cartComm: Comunication channel for the cart
    rowComm: Comunications channel for the the process row
    colComm: Communication channel for the process column

    globalRank: Process global rank
    cartRank: Process cart rank
    
    nDim: Number of dimensions in the grid
    isWrap: Specifies if the dimensions are periodical or not, i.e., 
            if the last process of each dimension communicates or not 
            with the first process in the same dimension
    dim: specifies the number of processes in each dimension of the grid

    coordinates: Cart Coordinates for the process
*/
typedef struct CommData
{
    MPI_Comm cartComm;
    MPI_Comm rowComm; 
    MPI_Comm colComm;

    int cartRank;
    int globalRank;
    int rowRank;
    int colRank; 

    int nDim;
    int nProc;
    
    int *isWrap; 
    int *dim;

    int *coordinates;
    int rowSize;
    int colSize;

}CommData;

CommData *newCommData();
void freeCommData(CommData *commData);

#endif