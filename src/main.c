#include <mpi.h>

#include "readData.h"
#include "gridComm.h"

/* 
    Note:   To change the number of process you need to change in the 
            makefile 
*/

int main(int argc, char **argv)
{
    int globalRank, nProc;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nProc);
    MPI_Comm_rank(MPI_COMM_WORLD, &globalRank);

    printf("World %d: starting\n", globalRank);
    MPI_Barrier(MPI_COMM_WORLD);

    CommData *commData = newCommData();
    MPI_Barrier(MPI_COMM_WORLD);

    freeCommData(commData);

    MPI_Finalize();
}