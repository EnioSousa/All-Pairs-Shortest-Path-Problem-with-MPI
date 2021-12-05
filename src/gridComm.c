#include "gridComm.h"

/*
Local Declarations
===============================================================================
*/
GridInfoType *setUpGrid(GridInfoType *grid);
GridInfoType *setGlobalGrid(GridInfoType *grid);
GridInfoType *setRowColCommunicators(GridInfoType *grid);

void seeGridDef(GridInfoType *grid);

/*
Implementation
===============================================================================
*/
GridInfoType *newGrid()
{
    GridInfoType *grid = (GridInfoType *)malloc(sizeof(GridInfoType));
    checkAlloc(grid, "newGrid", "grid");

    setUpGrid(grid);

#if VERBOSE
    seeGridDef(grid);
#endif

    return grid;
}

void freeGrid(GridInfoType *grid)
{
    MPI_Comm_free(&grid->colComm);
    MPI_Comm_free(&grid->rowComm);
    MPI_Comm_free(&grid->comm);

    free(grid);
}

GridInfoType *setUpGrid(GridInfoType *grid)
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

GridInfoType *setRowColCommunicators(GridInfoType *grid)
{
    checkNullPointer(grid, "setRowColCommunicators", "grid");

    int indicateRow[2] = {0, 1};

    MPI_Cart_sub(grid->comm, indicateRow, &grid->rowComm);

    int indicateCol[2] = {1, 0};

    MPI_Cart_sub(grid->comm, indicateCol, &grid->colComm);

    return grid;
}

/*
    Note: Careful this is parallel computing. You'r going to have multiple
    processes trying to write at the same time.
*/
void seeGridDef(GridInfoType *grid)
{
    for (int i = 0; i < grid->p; i++)
    {
        if (i == grid->myRank)
            printf("CartRank: %d Row: %d col: %d\n",
                   grid->myRank, grid->myRow, grid->myCol);

        MPI_Barrier(MPI_COMM_WORLD);
    }
}

SGInfo *sgInfo;

Matrix *scatterData(GridInfoType *grid, Matrix *matrix, Matrix *localMatrix)
{
    // No need to check if matrix is null, since only the root process will have
    // the full matrix. All other process have a sub matrix
    checkNullPointer(localMatrix, "scatterData", "localMatrix");
    checkNullPointer(grid, "scatterData", "grid");

    if (grid->myRank == 0)
        checkNullPointer(matrix, "scatterData", "matrix");

    // Full matrix size. Attention: grid->q is the number of "divisions" per side
    int sideSize = localMatrix->nRow * grid->q;
    int size[2] = {sideSize, sideSize};
    // Local matrix size
    int subsize[2] = {localMatrix->nRow, localMatrix->nCol};
    // Start of the array
    int start[2] = {0, 0};

    sgInfo = (SGInfo *)malloc(sizeof(SGInfo));
    checkAlloc(sgInfo, "scatterData", "sgInfo");

    MPI_Datatype subArray;

    /*  The subarray type constructor creates an MPI data type describing an 
        n-dimensional subarray of an n-dimensional array. In out case means that
        the submatrix may be situated anywhere within the full matrix
        Very usefull to scatter matrix data
    */
    MPI_Type_create_subarray(2, size, subsize, start, MPI_ORDER_C,
                             MPI_INT, &subArray);

    /*
        Since our data is in a continuous piece of memory, we obviously have
        holes. The previous call calculates the extent (the piece of memory 
        where the submatrix is) as everything between the first and last block, 
        however, the holes contain other submatrix that we want to scatter. 
        We then need to indicate a new upper bound that will take into 
        consideration the holes. 
    */
    MPI_Type_create_resized(subArray, 0, localMatrix->nRow * sizeof(int),
                            &(sgInfo->subMatrix));

    MPI_Type_commit(&(sgInfo->subMatrix));

    //How many submatrix we will send
    sgInfo->sendRecCounts = newArray(grid->p, 1);

    // The displacement i.e. where each submatrix start in the continuous piece
    // of memory
    sgInfo->displs = newArray(grid->p, 0);

    if (grid->myRank == 0)
    {
        for (int i = 0, disp = 0; i < grid->q; i++)
        {
            for (int j = 0; j < grid->q; j++)
            {
                sgInfo->displs[i * grid->q + j] = disp;
                disp++;
            }

            disp += (localMatrix->nRow - 1) * grid->q;
        }
    }
    
    // We now scater the Matrix
    MPI_Scatterv(matrix != NULL ? matrix->data : NULL, sgInfo->sendRecCounts,
                 sgInfo->displs,
                 (sgInfo->subMatrix), localMatrix->data,
                 localMatrix->fullSize, MPI_INT, 0, grid->comm);

#if VERBOSE

    if (matrix != NULL)
    {
        printf("Full matrix\n");
        printMatrix(matrix);
    }
    MPI_Barrier(grid->comm);

    for (int i = 0; i < grid->p; i++)
    {
        if (i == grid->myRank)
        {
            printf("CartRank: %d\n", grid->myRank);
            printMatrix(localMatrix);
        }
        MPI_Barrier(grid->comm);
    }

#endif

    MPI_Type_free(&subArray);

    return localMatrix;
}

Matrix *gatherData(Matrix *subMatrix, GridInfoType *grid)
{
    int size = grid->q * subMatrix->nCol;

    Matrix *result = grid->myRank == 0 ? newMatrix(size, size, 0) : NULL;

    replaceMatrixValue(subMatrix, INT_MAX, 0);

    MPI_Gatherv(subMatrix->data, subMatrix->fullSize, MPI_INT,
                result == NULL ? NULL : result->data, sgInfo->sendRecCounts,
                sgInfo->displs, (sgInfo->subMatrix), 0, grid->comm);

    freeArray(sgInfo->displs);
    freeArray(sgInfo->sendRecCounts);
    MPI_Type_free(&(sgInfo->subMatrix));
    free(sgInfo);

    return result;
}
