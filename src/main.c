#include "main.h"

/*
    NOTE: You can change global definitions in main.h. Currently you can change
    file to read and VERBOSE mode.
*/

char *getOutputName(char *inputName);
int compareOutput(FILE *file, Matrix *matrix);

int main(int argc, char **argv)
{
    Matrix *matrix = NULL;

    int globalRank, nProc, matrixSize;

    double timeStart, timeFinish;

    /* Initialize global communicator and read the matrix data */
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nProc);
    MPI_Comm_rank(MPI_COMM_WORLD, &globalRank);

    int q = (int)sqrt(nProc);

    if (q * q < nProc)
    {
        if (globalRank == 0)
            printf("ERROR: Invalid configuration!\n");
        MPI_Finalize();

        return 0;
    }

    if (globalRank == 0)
    {
        if (argc < 2)
            matrix = readData(stdin);
        else
            matrix = readDataFromFile(argv[1]);

        matrixSize = matrix->nCol;

        int *pos;
        for (int i = 0; i < matrixSize; i++)
        {
            for (int x = 0; x < matrixSize; x++)
            {
                pos = getMatrixPos(matrix, i, x);

                if ((i != x) && (*pos == 0))
                    setMatrixPos(matrix, i, x, INT_MAX); // Change value to infinite
            }
        }
    }

#if VERBOSE
    printf("World %d: starting\n", globalRank);
#endif
    // Wait
    MPI_Barrier(MPI_COMM_WORLD);

    timeStart = MPI_Wtime();

    /* Construct grid communicator */
    GridInfoType *grid = newGrid();
    // Wait

    MPI_Bcast(&matrixSize, 1, MPI_INT, 0, grid->comm);

    if (matrixSize % q != 0)
    {
        if (grid->myRank == 0)
            printf("ERROR: Invalid configuration!!!\n");
        MPI_Finalize();

        return 0;
    }

    // Scatter the data. Each process has a localMatrix that is a submatrix
    int localMatrixSize = matrixSize / grid->q;
    Matrix *local_A = scatterData(grid, matrix, newMatrix(localMatrixSize, localMatrixSize, 0));
    Matrix *local_B = newMatrix(localMatrixSize, localMatrixSize, 0);
    Matrix *local_C = newMatrix(localMatrixSize, localMatrixSize, INT_MAX);
    Matrix *temp = newMatrixNoDefault(local_A->nRow, local_A->nCol);

    copyMatrix(local_A, local_B);

    double maxIterations = log2((double)matrixSize - 1);

    for (int x = 0; x < maxIterations; x++) // Fox algorithm
    {
        fox(grid, local_A, local_B, local_C, temp);
        copyMatrix(local_C, local_A);
        copyMatrix(local_C, local_B);
    }

    free(temp);

    Matrix *result = gatherData(local_C, grid);

    timeFinish = MPI_Wtime(); /* Finish timer */

    if (grid->myRank == 0)
    {
#if WANT_COMPARE
        FILE *file;

        if (argc < 2)
        {
            file = stdin;
        }
        else
        {
            char *temp = getOutputName(argv[1]);
            file = openFile(temp, "r");
            free(temp);
        }

        if (!compareOutput(file, result))
        {
            printf("Incorrect result\n");
        }
        else
        {
            printf("Correct result\n");
        }
#endif

#if WANT_OUTPUT
        printMatrix(result);
#endif

#if WANT_TIME
        printf("Execution time: %f\n", timeFinish - timeStart);
#endif       
        
        freeMatrix(result);
    }

    freeGrid(grid);
    freeMatrix(matrix);
    freeMatrix(local_A);
    freeMatrix(local_B);
    freeMatrix(local_C);

    MPI_Finalize();
}

int compareOutput(FILE *file, Matrix *matrix)
{
    int temp;

    for (int i = 0; i < matrix->fullSize && fscanf(file, "%d", &temp) != EOF; i++)
    {
        if (*getMatrixPos(matrix, i / matrix->nRow, i % matrix->nCol) != temp)
            return 0;
    }

    return 1;
}

char *getOutputName(char *fileName)
{

    char *inputName = fileName;
    const char *number = inputName + 5; // Word "input" have 5 letters

    int sizeOfOutput = strlen("output") + strlen(number);
    char *outputName = (char *)malloc(sizeof(char) * (sizeOfOutput + 1));

    checkAlloc(outputName, "getOutputName", "outputName");

    strcpy(outputName, "output");
    strcat(outputName, number);

    return outputName;
}
