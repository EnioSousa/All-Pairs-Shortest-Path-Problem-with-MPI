#ifndef BASICFUNC
#define BASICFUNC

#include <stdlib.h>
#include <stdio.h>
#include "errorMsg.h"

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
int *newArray(int size, int defaultValue);

void printBiArray(int **biArray, int n, int m);
void printArray(int *array, int n);

#endif