#ifndef GRIDCOMM
#define GRIDCOMM

#include <mpi.h>

#include "errorMsg.h"
#include "basicFunc.h"
#include "math.h"
#include "main.h"

/*
    p:         Total number of processes
    comm:      Communicator for the entire grid
    rowComm:   Communicator for my row
    colComm:   Communicator for my col
    q:         q == p * p i.e. q is the number of divisions per "side"
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
GridInfoType *newGrid();

/*
    Function: Free memory allocated for GridInfoType object
    ---------------------------------------------------------------------------
    Free memory and communicators

    Return: void
*/
void freeGrid(GridInfoType *grid);

/*
    Function: Divide the full matrix into subMatrix and scatter 
    ---------------------------------------------------------------------------
    Function is responsible dividing the full matrix in to n smaller sub matrix
    and scatter to other processes in the grid

    grid: grid communication
    matrix: full matrix. Only the root process has this matrix
    localMatrix: local matrix to each process.

    Return: The corresponding subMatrix for a given process
*/
Matrix *scatterData(GridInfoType *grid, Matrix *matrix, Matrix *localMatrix);

#endif