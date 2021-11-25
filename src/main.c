#include "main.h"

/* 
    Note:   To change the number of process you need to change in the 
            makefile 
*/

Matrix *getData();


int main(int argc, char **argv)
{
    Matrix *matrix;

    int globalRank, nProc;

    /* Initialize global communicator and read the matrix data */
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nProc);
    MPI_Comm_rank(MPI_COMM_WORLD, &globalRank);

    if ( globalRank == 0 )
        matrix = getData();

#if VERBOSE
    printf("World %d: starting\n", globalRank);
#endif
    // Wait
    MPI_Barrier(MPI_COMM_WORLD);

    /* Construct grid communicator */
    GridInfoType *grid = newGrid();
    // Wait
    MPI_Barrier(MPI_COMM_WORLD);

    freeGrid(grid);

    MPI_Finalize(); 
}

Matrix *getData()
{
    Matrix *matrix = readData(FILENAME);

#if VERBOSE
    printf("Matrix Read:\n");
    printMatrix(matrix);
#endif
}