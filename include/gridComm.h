#ifndef GRIDCOMM
#define GRIDCOMM

#include <mpi.h>

#include "errorMsg.h"
#include "basicFunc.h"
#include "math.h"
#include "main.h"

/*
    p:          Total number of processes
    comm:       Communicator for the entire grid
    rowComm:   Communicator for my row
    colComm:   Communicator for my col
    q:         Order of grid
    myRow:     My row number
    myCol:     My col number
    myRank:    My rank in the grid communicator
*/
typedef struct
{
    int p;

    MPI_Comm comm;
    MPI_Comm rowComm;
    MPI_Comm colComm;

    int q;
    int myRow;
    int myCol;
    int myRank;

} GridInfoType;

/*
    Function: Allocates and initiates a new GridInfoType objects
    ---------------------------------------------------------------------------
    Dinamically allocates space for a new GridInfoType object and initiates the
    communicators

    Returns: Pointer to the new GridInfoType object
*/
GridInfoType* newGrid();

/*
    Function: Free memory allocated for GridInfoType object
    ---------------------------------------------------------------------------
    Free memory and communicators

    Return: void
*/
void freeGrid(GridInfoType *grid);

#endif