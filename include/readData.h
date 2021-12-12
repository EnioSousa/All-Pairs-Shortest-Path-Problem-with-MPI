#ifndef READDATA
#define READDATA

#include <stdio.h>
#include <string.h>

#include "errorMsg.h"
#include "basicFunc.h"

/**
 * @brief Function reads data from an open file
 * 
 * @param file File to read
 * @return Matrix object that contains the read values of the file
 */
Matrix* readData(FILE *file);

/**
 * @brief Function will open a file, create a Matrix object and put 
 * the contents of the file in the Matrix. 
 * 
 * @param fileName The file name to read. File need to be in data directory
 * @return The Matrix object that contains the read values of the file
 */
Matrix* readDataFromFile(char *fileName);

/**
 * @brief Open a file with certain permissions
 * 
 * @param fileName The file name to read. Need to be in data directory
 * @param permissions The permissions for the file reader
 * @return FILE* 
 */
FILE *openFile(char *fileName, char *permissions);

/**
 * @brief Close an open file
 * 
 * @param fileName The opened file
 */
void closeFile(FILE *fileName);

#endif