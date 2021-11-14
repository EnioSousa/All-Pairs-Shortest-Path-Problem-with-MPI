#ifndef READDATA
#define READDATA

#include <stdio.h>
#include <string.h>

#include "errorMsg.h"

typedef struct Matrix
{
    int **data; // Matrix values
    int size; // matrix size (n x n) i.e. quadratic matrix
} Matrix;

/*
    Function: Initiates a new matrix structure
    ------------------------------------------

    This function is responsible for allocation the necessary space for the 
    structure that will hold the matrix data. This data will be read from 
    the specified file

    fileName: File name of where the data is located

    Return: A new Matrix strucure contaning the data
*/
Matrix *initMatrix(char *fileName);

FILE *openFile(char *fileName, char *permissions);
FILE *closeFile(FILE *fileName);

/*
    Function: Print matrix contents
    -------------------------------
    Print matrix content on to the standard output file

    matrix: Structure of type Matrix, holding the data

    returns: void
*/
void toStringMatrix(Matrix *matrix);

#endif