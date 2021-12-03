#include "foxAlgo.h"

/*
Local Declarations
===============================================================================
*/

void localMatrixMultiply(Matrix* A, Matrix* B, Matrix* C);

/*
Implementation
===============================================================================
*/

void Fox(int n, GridInfoType* grid,
	Matrix* local_A,
	Matrix* local_B,
	Matrix* local_C){
		
	Matrix* temp_A;
		
	int step;
	int bcast_root;
	int n_bar;
	int source;
	int dest;
	int tag = 43;
	MPI_Status status;
	
	n_bar = n/grid->q;
	resetMatrix(local_C, INT_MAX);
	
	/* Calculate addresses for circular shift of B */
	source = (grid->myRow + 1) % grid->q;
	dest = (grid->myRow + grid->q - 1) % grid->q;
	
	/* Set aside storage for the broadcast block of A */
	temp_A = newMatrix(n_bar, n_bar, 0); 

	for(step = 0; step < grid->q; step++)
	{

		bcast_root = (grid->myRow + step) % grid->q;
		
		if(bcast_root == grid->myCol)
		{
			
			MPI_Bcast(local_A->data, local_A->fullSize, MPI_INT, bcast_root, grid->rowComm);
			localMatrixMultiply(local_A, local_B, local_C);
			
		}else{
			
			MPI_Bcast(temp_A->data, temp_A->fullSize, MPI_INT, bcast_root, grid->rowComm);
			localMatrixMultiply(temp_A, local_B, local_C);
		}
		
		MPI_Send(local_B->data, local_B->fullSize, MPI_INT, dest, tag, grid->colComm);
		MPI_Recv(local_B->data, local_B->fullSize, MPI_INT, source, tag, grid->colComm, &status);	

	}
	
	freeMatrix(temp_A);
}

void localMatrixMultiply(Matrix* A, Matrix* B, Matrix* C){
	
	int size = A->nRow;
	int Apos, Bpos;
	int * Cpos;
	int temp;

	for (int i = 0; i < size; i++) 
	{
		for (int j = 0; j < size; j++)
		{
			Cpos = getMatrixPos(C, i, j);
			
			for (int k = 0; k < size; k++)
			{
				Apos = *(getMatrixPos(A, i, k));
				Bpos = *(getMatrixPos(B, k, j)); 
	
				if((Apos == INT_MAX) || (Bpos == INT_MAX )) continue;
				
				temp = Apos + Bpos; 
	
				if((temp < *Cpos)) *Cpos = temp;

			}
		}
	}
}


