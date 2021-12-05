#ifndef BASICFUNC
#define BASICFUNC

#include <stdlib.h>
#include <stdio.h>
#include "errorMsg.h"
#include <limits.h>
#include <string.h>

/**
 * @brief Matrix object that holds a (nRow x nCol) Matrix
 */
typedef struct Matrix
{
    /**
     * @brief Holds the values of the matrix
     */
    int *data;
    /**
     * @brief Number of columns
     */
    int nCol;
    /**
     * @brief Number of rows
     */
    int nRow;
    /**
     * @brief Full size of the matrix, i.e. number of positions
     */
    int fullSize;
} Matrix;

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

/**
 * @brief Set matrix position with a value
 * 
 * @param matrix  Matrix object 
 * @param row Row index to change
 * @param col Col index to change
 * @param value Value to change to
 * @return The updated Matrix object if position exists, otherwise null
 */
int *setMatrixPos(Matrix *matrix, int row, int col, int value);

/**
 * @brief Resent the contents of a matrix object with a new value
 * 
 * @param C Matrix to change
 * @param value Value to change the matrix to
 * @return The matrix object, now with a new value
 */
Matrix *resetMatrix(Matrix *C, int value);

/**
 * @brief Checks if tow Matrix are equals 
 * 
 * @param matrix0 First matrix
 * @param matrix1 Second Matrix
 * @return 1 if the matrix values are the same, otherwise 0
 */
int equalsMatrix(Matrix *matrix0, Matrix *matrix1);

/**
 * @brief Replace Matrix values with another
 * 
 * @param matrix The matrix object
 * @param toReplace the value to replace
 * @param newValue The new value
 * @return The Matrix with the replaced values
 */
Matrix *replaceMatrixValue(Matrix *matrix, int toReplace, int newValue);

/**
 * @brief Allocates space for a bidimensional array
 * 
 * @param size Size of the bi array (size x size)
 * @param defaultValue Default value for the new array
 * @return Pointer to the bi array
 */
int **newBiArray(int size, int defaultValue);

/**
 * @brief Allocates space for an array
 * 
 * @param size Size of the array
 * @param defaultValue Default value for the new array
 * @return Pointer to an array
 */
int *newArray(int size, int defaultValue);

/**
 * @brief Print the contents of a Matrix
 * 
 * @param matrix The matrix object
 */
void printMatrix(Matrix *matrix);

/**
 * @brief Print the contents of a bi array
 * 
 * @param biArray The bi array to print
 * @param n Number of rows
 * @param m Number of cols
 */
void printBiArray(int **biArray, int n, int m);

/**
 * @brief Print the contetns of an array
 * 
 * @param array Array to print
 * @param n number of rows
 */
void printArray(int *array, int n);

/**
 * @brief Free the memory ynamically allocated for a bi array
 * 
 * @param array the starting pointer for the array
 * @param size Number of rows in the bi array
 */
void freeBiArray(int **array, int size);

/**
 * @brief Free the memory dinamically allocated for an array
 * 
 * @param array The starting pointer for the array
 */
void freeArray(int *array);

/**
 * @brief Free the memory dinamically allocated for a matrix object
 * 
 * @param matrix The matrix pointer 
 */
void freeMatrix(Matrix *matrix);

/**
 * @brief Copy the contents of one matrix to another
 * 
 * @param matrix_A first matrix, source
 * @param matrix_B second matrix, destination
 */
void copyMatrix(Matrix *matrix_A, Matrix *matrix_B);

#endif
