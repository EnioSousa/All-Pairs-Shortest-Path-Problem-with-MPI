#include "foxAlgo.h"

/*
Local Declarations
===============================================================================
*/

void localMatrixMultiply(Matrix *A, Matrix *B, Matrix *C);

/*
Implementation
===============================================================================
*/

void fox(GridInfoType *grid, Matrix *localA, Matrix *localB, Matrix *localC)
{
	Matrix *temp = newMatrix(localA->nRow, localA->nCol, 0);

	/**
	 * @brief Processor directly below
	 */
	int columnSource = (grid->myRow + 1) % grid->q;
	/**
	 * @brief Processor directly above 
	 */
	int columnDest = (grid->myRow + grid->q - 1) % grid->q;

	int tag = 43;

	resetMatrix(localC, INT_MAX);

	for (int step = 0; step < grid->q; step++)
	{
		/**
		 * @brief Defines which process is the one broadcasting its submatrix
		 * to the other processes in the same row.
		 * Example: If the current process is 0 we need the submatrix from
		 * 0 then 1 then 2
		 * Example: If the current process is 3 then we need 4 5 3 
		 */
		int broadCastRoot = (grid->myRow + step) % grid->q;

		MPI_Barrier(MPI_COMM_WORLD);

		MPI_Barrier(MPI_COMM_WORLD);
		// The current process will broadcast
		if (broadCastRoot == grid->myCol)
		{
			MPI_Bcast(localA->data, localA->fullSize, MPI_INT, broadCastRoot,
					  grid->rowComm);
			localMatrixMultiply(localA, localB, localC);
		}
		// The current process will receive
		else
		{
			MPI_Bcast(temp->data, temp->fullSize, MPI_INT,
					  broadCastRoot, grid->rowComm);
			localMatrixMultiply(temp, localB, localC);
		}

		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Sendrecv_replace(localB->data, localB->fullSize, MPI_INT,
							 columnDest, tag, columnSource, tag,
							 grid->colComm, MPI_STATUS_IGNORE);
	}

	freeMatrix(temp);
}

void localMatrixMultiply(Matrix *A, Matrix *B, Matrix *C)
{
	int size = A->nRow;
	int posA, posB;
	int *posC;
	int temp;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			posC = getMatrixPos(C, i, j);

			for (int k = 0; k < size; k++)
			{
				posA = *(getMatrixPos(A, i, k));
				posB = *(getMatrixPos(B, k, j));

				if ((posA == INT_MAX) || (posB == INT_MAX))
					continue;

				temp = posA + posB;

				if ((temp < *posC))
					*posC = temp;
			}
		}
	}
}