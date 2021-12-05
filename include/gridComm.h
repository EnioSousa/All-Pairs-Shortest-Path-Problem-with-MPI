#ifndef GRIDCOMM
#define GRIDCOMM

#include <mpi.h>

#include "errorMsg.h"
#include "basicFunc.h"
#include "math.h"

/**
 * @brief Structure holds key information about the grid communicators used 
 * in mips
 * 
 */
typedef struct
{
    /**
     * @brief Number of processors in the grid
     * 
     */
    int p;
    /**
     * @brief Global comunicator for the grid
     * 
     */
    MPI_Comm comm;
    /**
     * @brief Row comunicator for the current processor
     * 
     */
    MPI_Comm rowComm;
    /**
     * @brief Col comunicator for the current processor
     * 
     */
    MPI_Comm colComm;
    /**
     * @brief Number of processors by row
     * 
     */
    int q;
    /**
     * @brief Specifies what is the grid row for the current processor
     * 
     */
    int myRow;
    /**
     * @brief SPecifies what is the grid col for the current processor
     * 
     */
    int myCol;
    /**
     * @brief Specifies what tank the current processor has in the grid
     * 
     */
    int myRank;

} GridInfoType;

/**
 * @brief Structure hold the send count, recive count and special MPI 
 * data type. These fields are used in scatter and gather functions.
 * 
 */
typedef struct ScatterGatherInfo
{
    int *sendRecCounts;
    int *displs;

    MPI_Datatype subMatrix;
} SGInfo;


/**
 * @brief Dinamically allocates space for a new GridInfoType object and initiates the 
 * communicators
 * 
 * @return Pointer to the new GridInfoType object
 */
GridInfoType *newGrid();

/**
 * @brief  Free memory allocated for GridInfoType object
 * 
 * @param grid The pointer for the grid object
 */
void freeGrid(GridInfoType *grid);

/**
 * @brief Function is responsible for dividing the full matrix in to n 
 * smaller sub matrix and scatter to other processes in the grid
 * 
 * @param grid The grid Info type object 
 * @param matrix Full matrix to scatter. Only the root process has this matrix
 * @param localMatrix Local matrix to each process. You need to create them
 * @return The corresponding sub matrix for the process that called this function
 */
Matrix *scatterData(GridInfoType *grid, Matrix *matrix, Matrix *localMatrix);

/**
 * @brief Function is responsible for gathering the sub matrix that the other 
 * processes have into a full matrix.
 *  
 * @param subMatrix Sub matrix to send 
 * @param grid Grid info type object
 * @return The full matrix. Only the root process will recive it, the other 
 * get null
 */
Matrix* gatherData(Matrix* subMatrix, GridInfoType *grid);


#include "main.h"
#endif
