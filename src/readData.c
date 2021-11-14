#include "readData.h"

#define DATALOC "data/"

/*
    ========================= Local declaration =========================
*/
/*
    Function: Matrix stucture allocation
    ------------------------------
    Allocates space from a Matrix object and returns the pointer

    size: Number of lines in the matrix. Nº of lines is equal to the number
          columns

    Returns: Matrix structure, initialized with zeros
*/
Matrix *newMatrix(int size);

/* 
    Function: Read matrix data from a file
    --------------------------------------
    Read data from a file and puts in the matrix

    matrix: Structure where to put the data
    inFIle: File where to read the data

    returns: The matrix structure pointer
*/
Matrix *readMatrixData(Matrix *matrix, FILE *inFile);

/*
    Function: Alocates space for a bidimensional array
    --------------------------------------------------
    Will dynamically allocate space for a bi array and initiate it with a 
    default value

    size: size of the bi array (size x size)
    defaultValue: default value for the array

    Returns: pointer to a bi array
*/
int **initBiArray(int size, int defaultValue);

void printBiArray(int **biArray, int n, int m);

/*
    ========================= Implementation =========================
*/
FILE *openFile(char *fileName, char *permissions)
{
    char *pathName = (char *)malloc(strlen(DATALOC) + strlen(fileName));
    checkAlloc(pathName, "openFile", "pathName");

    strcpy(pathName, DATALOC);
    strcat(pathName, fileName);

    FILE *inFile = fopen(pathName, permissions);
    checkNullPointer(inFile, "openFile", "inFile");

    free(pathName);

    return inFile;
}

FILE *closeFile(FILE *fileName)
{
    if (fileName != NULL)
        fclose(fileName);
}

Matrix *initMatrix(char *fileName)
{
    FILE *inFile = openFile(fileName, "r");

    int size = 0;
    fscanf(inFile, "%d", &size);

    Matrix *matrix = newMatrix(size);

    readMatrixData(matrix, inFile);

    closeFile(inFile);

    return matrix;
}

Matrix *newMatrix(int size)
{
    Matrix *matrix = (Matrix *)calloc(1, sizeof(Matrix));
    checkAlloc(matrix, "newMatrix", "matrix");

    matrix->size = size;

    matrix->data = initBiArray(size, 0);

    return matrix;
}

int **initBiArray(int size, int defaultValue)
{
    int **biArray = (int **)malloc(size * sizeof(int *));
    checkAlloc(biArray, "initbiArray", "biArray");

    for (int i = 0; i < size; i++)
    {
        biArray[i] = (int *)malloc(size * sizeof(int));
        checkAlloc(biArray, "initBiArray", "biArray[index]");

        for (int j = 0; j < size; j++)
            biArray[i][j] = defaultValue;
    }

    return biArray;
}

Matrix *readMatrixData(Matrix *matrix, FILE *inFile)
{
    checkNullPointer(inFile, "readMatrixData", "inFile");
    checkNullPointer(matrix, "readMatrixData", "matrix");

    for (int i = 0; i < matrix->size; i++)
    {
        for (int j = 0; j < matrix->size; j++)
        {
            fscanf(inFile, "%d", &matrix->data[i][j]);
        }
    }
}

void toStringMatrix(Matrix *matrix)
{
    printf("Matrix size: %d\n", matrix->size);

    for (int i = 0; i < matrix->size; i++)
    {
        for (int j = 0; j < matrix->size; j++)
        {
            printf("%d ", matrix->data[i][j]);
        }

        printf("\n");
    }
}

void printBiArray(int **biArray, int n, int m)
{
    printf("PRINT BI ARRAY:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d ", biArray[i][j]);
        }

        printf("\n");
    }
    printf("\n");
}