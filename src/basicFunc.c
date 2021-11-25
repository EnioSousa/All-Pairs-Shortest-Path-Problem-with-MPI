#include "basicFunc.h"

int **newBiArray(int size, int defaultValue)
{
    int **biArray = (int **)malloc(size * sizeof(int *));
    checkAlloc(biArray, "newbiArray", "biArray");

    for (int i = 0; i < size; i++)
        biArray[i] = newArray(size, defaultValue);

    return biArray;
}

int *newArray(int size, int defaultValue)
{
    int *array = (int *)malloc(size * sizeof(int));
    checkAlloc(array, "newArray", "array");

    for (int i = 0; i < size; i++)
        array[i] = defaultValue;

    return array;
}

void printBiArray(int **biArray, int n, int m)
{
    printf("BI ARRAY SIZE: %d x %d\n", n, m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%d ", biArray[i][j]);

        printf("\n");
    }
    printf("\n");
}

void printArray(int *array, int n)
{
    printf("ARRAY SIZE: %d\n", n);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }

    printf("\n");
}

Matrix *newMatrix(int nRow, int nCol, int defaultValue)
{
    Matrix *matrix = (Matrix *)malloc(sizeof(matrix));
    checkAlloc(matrix, "newMatrix", "matrix");

    matrix->data = newArray(nRow * nCol, defaultValue);
    matrix->nRow = nRow;
    matrix->nCol = nCol;

    return matrix;
}

int *getMatrixPos(Matrix *matrix, int row, int col)
{
    checkAlloc(matrix, "getMatrixPos", "matrix");

    if (row >= matrix->nRow || col >= matrix->nCol)
    {
        fprintf(stderr, "getMatrixPos: Tried to access invalid position (%d, %d)",
                row, col);
        return NULL;
    }

    else
        return &matrix->data[row * matrix->nRow + col];
}

int *setMatrixPos(Matrix *matrix, int row, int col, int value)
{
    checkAlloc(matrix, "getMatrixPos", "matrix");

    int *pos = getMatrixPos(matrix, row, col);

    if (pos == NULL)
        return NULL;

    else
    {
        *pos = value;
        return pos;
    }
}

void printMatrix(Matrix *matrix)
{
    printf("Matrix %dx%d:\n", matrix->nRow, matrix->nCol);

    for (int i = 0; i < matrix->nRow; i++)
    {
        for (int j = 0; j < matrix->nCol; j++)
            printf("%5d ", *getMatrixPos(matrix, i, j));

        printf("\n");
    }

    printf("\n");
}


