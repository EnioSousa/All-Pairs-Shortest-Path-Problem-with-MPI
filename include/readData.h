#ifndef READDATA
#define READDATA

#include <stdio.h>
#include <string.h>

#include "errorMsg.h"
#include "basicFunc.h"

/*
    Function: Reads a matrix from a file and return a pointer to a Matrix obj
    -------------------------------------------------------------------------
    Function will open a file, create a Matrix object and put the contents of 
    the file in the Matrix. 

    fileName: File name to read. It should not be a full path and the file should
              be in data directory

    Returns: Pointer to a Matrix object
*/
Matrix* readData(char *fileName);

FILE *openFile(char *fileName, char *permissions);

FILE *closeFile(FILE *fileName);

#endif