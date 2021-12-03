#ifndef BASICFUNC
#define BASICFUNC

#include <stdlib.h>
#include <stdio.h>
#include "errorMsg.h"
#include <limits.h>

typedef struct Matrix
{
    int *data;
    int nCol;
    int nRow;

    int fullSize;
}Matrix;

/**
 * @brief Allocates space for a Matrix object and returns the pointer
 * 
 * @param nRow Number of rows in the matrix.
 * @param nCol Number of columns in the matrix.
 * @param defaultValue Value to intialize the matrix with
 * @return Matrix structure, initialized with "defaultValue"
 */
Matrix *newMatrix(int nRow, int nCol, int defaultValue);

/**
 * @brief Return the pointer that holds (row,col) possition. If possition dosen't exist return NULL
 * 
 * @param matrix Matrix object
 * @param row row index
 * @param col col index
 * @return Pointer to the memory space that holds (row,col) or NULL
 */
int *getMatrixPos(Matrix *matrix, int row, int col);

/*
    Function: Set matrix possition with a value
    -------------------------------------------
    Set a given possition with a value

    matrix: Matrix object
    row: row
    col: col
    value: Value to set

    Return: Pointer to the memory that was changed or NULL if possition dosen't
            exit
*/
int *setMatrixPos(Matrix *matrix, int row, int col, int value);

/**
 * @brief Resent the contents of a matrix object with a new value
 * 
 * @param C Matrix to change
 * @param value Value to change the matrix to
 * @return The matrix object, now with a new value
 */
Matrix* resetMatrix(Matrix* C, int value);

int equalsMatrix(Matrix *matrix0, Matrix* matrix1);

Matrix* replaceMatrixValue(Matrix *matrix, int toReplace, int newValue);
/*
    Function: Alocates space for a bidimensional array
    --------------------------------------------------
    Will dynamically allocate space for a bi array and initiate it with a 
    default value

    size: size of the bi array (size x size)
    defaultValue: default value for the array

    Returns: pointer to a bi array
*/
int **newBiArray(int size, int defaultValue);

/*
    Function: Alocates space for an array
    --------------------------------------------------
    Will dynamically allocate space for an array and initiate it with a 
    default value

    size: size of the bi array
    defaultValue: default value for the array

    Returns: pointer to an array
*/
int *newArray(int size, int defaultValue);

void printMatrix(Matrix *matrix);
void printBiArray(int **biArray, int n, int m);
void printArray(int *array, int n);

void freeBiArray(int **array, int size);
void freeArray(int *array);
void freeMatrix(Matrix *matrix);

void copyMatrix(Matrix *matrix_A, Matrix *matrix_B);

#endif
