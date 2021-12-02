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
	int *res;
	
    /* Initialize global communicator and read the matrix data */
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nProc);
    MPI_Comm_rank(MPI_COMM_WORLD, &globalRank);

    if (globalRank == 0)
    {
        matrix = getData();
		matrixSize = matrix->nCol;
		
		int *pos;
		for(int i = 0; i < matrixSize; i++){
			for(int x = 0; x < matrixSize; x++){
				pos = getMatrixPos(matrix, i, x);
				if((i != x) && (*pos == 0)) setMatrixPos(matrix, i, x, INT_MAX); //Change value to infinite
			}
		}
		
		res = (int *)malloc(sizeof(int) * matrixSize*matrixSize);
		checkAlloc(res, "main", "res");
    }

#if VERBOSE
    //printf("World %d: starting\n", globalRank);
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
    Matrix *local_A = scatterData(grid, matrix, newMatrix(localMatrixSize, localMatrixSize, 0));
	Matrix *local_B = newMatrix(localMatrixSize, localMatrixSize, 0);
	copyMatrix(local_A, local_B);

	Matrix *local_C =  newMatrix(localMatrixSize, localMatrixSize, INT_MAX);

	for(int x = 1; x < matrixSize-1; x++) //Fox algorithm
	{ 
		Fox(matrixSize, grid, local_A, local_B, local_C);
		copyMatrix(local_C, local_A);
		copyMatrix(local_C, local_B);
	}

	MPI_Gather(local_C->data, localMatrixSize*localMatrixSize, MPI_INT, res, localMatrixSize*localMatrixSize, MPI_INT, 0, MPI_COMM_WORLD);

    if(grid->myRank == 0){
		printResult(res, nProc, matrixSize, localMatrixSize);
		freeArray(res);
	}
	
    freeGrid(grid);
    freeMatrix(matrix);
	freeMatrix(local_A);
	freeMatrix(local_B);
	freeMatrix(local_C);

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
