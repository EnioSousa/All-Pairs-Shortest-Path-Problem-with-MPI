#ifndef ERRORMESSAGE
#define ERRORMESSAGE

#include <stdio.h>
#include <stdlib.h>

void errorMessageAlloc(char *funcName, char *varName);
void checkAlloc(void *pointer, char *funcName, char *varName);

void errorMessagePointer(char *funcName, char *varName);
void checkNullPointer(void *pointer, char *funcName, char *varName);

void errorMessageMainArgs(char *problem);

#endif
