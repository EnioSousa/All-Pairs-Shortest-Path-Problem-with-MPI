#include "readData.h"

#define DATALOC "data/"

/*
Local Declarations
===============================================================================
*/
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
Implementation
===============================================================================
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

void closeFile(FILE *fileName)
{
    if (fileName != NULL)
        fclose(fileName);
}

Matrix *readData(FILE *file) 
{
    int size = 0;
    fscanf(file, "%d", &size);

    Matrix *matrix = newMatrix(size, size, 0);

    readMatrixData(matrix, file);

    return matrix;
}

Matrix* readDataFromFile(char *fileName)
{
    FILE *inFile = openFile(fileName, "r");

    Matrix *matrix = readData(inFile);

    closeFile(inFile);

    return matrix;
}

Matrix *readMatrixData(Matrix *matrix, FILE *inFile)
{
    checkNullPointer(inFile, "readMatrixData", "inFile");
    checkNullPointer(matrix, "readMatrixData", "matrix");

    for (int i = 0; i < matrix->nRow; i++)
    {
        for (int j = 0; j < matrix->nCol; j++)
        {
            fscanf(inFile, "%d", getMatrixPos(matrix, i, j));
        }
    }
}

