#include "main.h"

/* 
    NOTE: You can change global definitions in main.h. Currently you can change
    file to read and VERBOSE mode.
*/

Matrix *getData();

int main(int argc, char **argv)
{
    Matrix *matrix = NULL;

    int globalRank, nProc, matrixSize;

    /* Initialize global communicator and read the matrix data */
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nProc);
    MPI_Comm_rank(MPI_COMM_WORLD, &globalRank);

    if (globalRank == 0)
    {
        matrix = getData();
        matrixSize = matrix->nCol;
    }

#if VERBOSE
    printf("World %d: starting\n", globalRank);
#endif
    // Wait
    MPI_Barrier(MPI_COMM_WORLD);

    /* Construct grid communicator */
    GridInfoType *grid = newGrid();
    // Wait
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Bcast(&matrixSize, 1, MPI_INT, 0, grid->comm);

    // Scatter the data. Each process has a localMatrix that is a submatrix
    int localMatrixSize = matrixSize / grid->q;
    Matrix *localMatrix = scatterData(grid, matrix, newMatrix(localMatrixSize, localMatrixSize, 0));

    freeGrid(grid);
    freeMatrix(matrix);

    MPI_Finalize();
}

Matrix *getData()
{
    Matrix *matrix = readData(FILENAME);

#if VERBOSE
    printf("Matrix Read:\n");
    printMatrix(matrix);
#endif

    return matrix;
}