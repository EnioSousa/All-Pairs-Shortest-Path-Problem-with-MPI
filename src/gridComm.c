#include "gridComm.h"

/*
    ========================= Local declaration =========================
*/
void initGrid(CommData *commData);
void newCartCommChl(CommData *commData);
void newSubCartCommChl(CommData *commData);
void testStuff(CommData *commData);

/*
    ========================= Implementation =========================
*/
CommData *newCommData()
{
    CommData *commData = (CommData *)malloc(sizeof(CommData));
    checkAlloc(commData, "initGird", "girdData");

    MPI_Comm_rank(MPI_COMM_WORLD, &commData->globalRank);
    MPI_Comm_size(MPI_COMM_WORLD, &commData->nProc);

    initGrid(commData);

    newCartCommChl(commData);
    newSubCartCommChl(commData);

    testStuff(commData);
    return commData;
}

void initGrid(CommData *commData)
{
    commData->nDim = 2;
    commData->isWrap = newArray(commData->nDim, PERIODIC);
    commData->dim = newArray(commData->nDim, (int)sqrt((double)commData->nProc));
    commData->coordinates = newArray(commData->nDim, NONVALUE);
}

void newCartCommChl(CommData *commData)
{
    // Create cart comm
    MPI_Cart_create(MPI_COMM_WORLD, commData->nDim, commData->dim,
                    commData->isWrap, 1, &commData->cartComm);

    // Get current process cart rank
    MPI_Comm_rank(commData->cartComm, &commData->cartRank);

    // Get current process coordinates
    MPI_Cart_coords(commData->cartComm, commData->cartRank,
                    commData->nDim, commData->coordinates);

    MPI_Barrier(MPI_COMM_WORLD);
}

void newSubCartCommChl(CommData *commData)
{
    int temp0[2] = {0, 1};
    MPI_Cart_sub(commData->cartComm, temp0, &commData->rowComm);

    int temp1[2] = {1, 0};
    MPI_Cart_sub(commData->cartComm, temp1, &commData->colComm);

    MPI_Comm_size(commData->rowComm, &commData->rowSize);
    MPI_Comm_size(commData->colComm, &commData->colSize);

    MPI_Comm_rank(commData->rowComm, &commData->rowRank);
    MPI_Comm_rank(commData->colComm, &commData->colRank);
}

void freeCommData(CommData *commData)
{
    MPI_Comm_free(&commData->cartComm);
 
    free(commData->isWrap);
    free(commData->dim);
    free(commData->coordinates);

    free(commData);
}

void testStuff(CommData *commData)
{
    printf("World %d Cart %d Row %d Col %d Coord (%d, %d)\n", commData->globalRank,
            commData->cartRank, commData->rowRank, commData->colRank, 
            commData->coordinates[0],commData->coordinates[1]);
}