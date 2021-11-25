#ifndef READDATA
#define READDATA

#include <stdio.h>
#include <string.h>

#include "errorMsg.h"
#include "basicFunc.h"

Matrix* readData(char *fileName);

FILE *openFile(char *fileName, char *permissions);

FILE *closeFile(FILE *fileName);

#endif