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

#include "mpi.h"

Matrix *newMatrix(int nRow, int nCol, int defaultValue)
{  
    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    checkAlloc(matrix, "newMatrix", "matrix");

    matrix->data = newArray(nRow * nCol, defaultValue);
    matrix->nRow = nRow;
    matrix->nCol = nCol;
    matrix->fullSize = nRow * nCol;

    return matrix;
}

Matrix *newMatrixNoDefault(int nRow, int nCol) {
    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));

    matrix->nRow = nRow;
    matrix->nCol = nCol;
    matrix->fullSize = nRow * nCol;
    matrix->data = (int *)malloc(matrix->fullSize * sizeof(int));

    return matrix;
}

int *getMatrixPos(Matrix *matrix, int row, int col)
{
    checkAlloc(matrix, "getMatrixPos", "matrix");

    if (row >= matrix->nRow || col >= matrix->nCol)
    {
        fprintf(stderr, "getMatrixPos: Tried to access invalid position (%d, %d)\n",
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

Matrix *resetMatrix(Matrix *C, int value)
{

    int size = C->nRow;

    for (int i = 0; i < size; i++)
    {
        for (int x = 0; x < size; x++)
        {
            setMatrixPos(C, i, x, value);
        }
    }

    return C;
}

Matrix *replaceMatrixValue(Matrix *matrix, int toReplace, int newValue)
{
    int size = matrix->nRow;

    for (int i = 0; i < size; i++)
    {
        for (int x = 0; x < size; x++)
        {   
            int *pos = getMatrixPos(matrix, i, x);

            if ( *pos == toReplace) 
                *pos = newValue;
        }
    }

    return matrix;
}

int equalsMatrix(Matrix *matrix0, Matrix *matrix1)
{
    if (matrix0->nCol != matrix1->nCol || matrix0->nRow != matrix1->nRow)
    {
        return 0;
    }

    return memcmp(matrix0->data, matrix1->data,
                  matrix0->fullSize * sizeof(int)) == 0
               ? 1
               : 0;
}

void printMatrix(Matrix *matrix)
{
    if (matrix == NULL || matrix->data == NULL)
    {
        printf("Matrix is NULL\n");
        return;
    }

    printf("Matrix %dx%d:\n", matrix->nRow, matrix->nCol);

    for (int i = 0; i < matrix->nRow; i++)
    {
        for (int j = 0; j < matrix->nCol; j++)
        {
            int temp = *getMatrixPos(matrix, i, j);

            temp == INT_MAX ? printf("%5s ", "inf") : printf("%5d ", temp);
        }

        printf("\n");
    }

    printf("\n");
}

void freeBiArray(int **array, int size)
{
    if (array != NULL)
    {
        for (int i = 0; i < size; i++)
            free(array[i]);
    }

    free(array);
}

void freeArray(int *array)
{
    if (array != NULL)
    {
        free(array);
    }
}

void freeMatrix(Matrix *matrix)
{
    if (matrix != NULL)
    {
        free(matrix->data);
        free(matrix);
    }
}

void copyMatrix(Matrix *matrix_A, Matrix *matrix_B)
{
    checkNullPointer(matrix_A, "copyMatrix", "matrix_a");
    checkNullPointer(matrix_B, "copyMatrix", "matrix_B");

    if (matrix_A->fullSize != matrix_B->fullSize)
        return;

    memcpy(matrix_B->data, matrix_A->data, matrix_B->fullSize * sizeof(int));
}
