#include "gridComm.h"

/*
Local Declarations
===============================================================================
*/
GridInfoType* setUpGrid(GridInfoType *grid);
GridInfoType *setGlobalGrid(GridInfoType *grid);
GridInfoType* setRowColCommunicators(GridInfoType *grid);

void seeGridDef(GridInfoType *grid);

/*
Implementation
===============================================================================
*/
GridInfoType* newGrid()
{
    GridInfoType *grid = (GridInfoType*)malloc(sizeof(GridInfoType));
    checkAlloc(grid, "newGrid", "grid");

    setUpGrid(grid);   

    seeGridDef(grid);

    return grid; 
}

void freeGrid(GridInfoType *grid)
{
    MPI_Comm_free(&grid->colComm);
    MPI_Comm_free(&grid->rowComm);
    MPI_Comm_free(&grid->comm);

    free(grid);
}

GridInfoType* setUpGrid(GridInfoType *grid)
{
    return setRowColCommunicators(setGlobalGrid(grid));
}

GridInfoType *setGlobalGrid(GridInfoType *grid)
{
    checkNullPointer(grid, "setGlobalGrid", "grid");

    int oldRank;
    int periods[2] = {1, 1};
    int dimensions[2];
    int coordinates[2];

    MPI_Comm_size(MPI_COMM_WORLD, &(grid->p));
    MPI_Comm_rank(MPI_COMM_WORLD, &oldRank);

    grid->q = (int)sqrt((double)grid->p);
    dimensions[0] = dimensions[1] = grid->q;

    MPI_Cart_create(MPI_COMM_WORLD, 2, dimensions, periods,
                    1, &(grid->comm));

    MPI_Comm_rank(grid->comm, &(grid->myRank));
    MPI_Cart_coords(grid->comm, grid->myRank, 2, coordinates);

    grid->myRow = coordinates[0];
    grid->myCol = coordinates[1];

    MPI_Barrier(MPI_COMM_WORLD);

    return grid;
}

GridInfoType* setRowColCommunicators(GridInfoType *grid)
{
    checkNullPointer(grid, "setRowColCommunicators", "grid");

    int indicateRow[2] = {0,1};

    MPI_Cart_sub(grid->comm, indicateRow, &grid->rowComm);

    int indicateCol[2] = {1, 0};

    MPI_Cart_sub(grid->comm, indicateCol, &grid->colComm);

    return grid;
}

void seeGridDef(GridInfoType *grid)
{
    printf("nProc: %d \nCartRank: %d \nRow: %d \ncol: %d\n\n", grid->p, 
            grid->myRank, grid->myRow, grid->myCol);
}
