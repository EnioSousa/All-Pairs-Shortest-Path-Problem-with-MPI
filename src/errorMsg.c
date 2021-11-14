#include "errorMsg.h"

void errorMessageAlloc(char *funcName, char *varName)
{
    fprintf(stderr, "%s: Memory allocation failed. Var %s\n", funcName, varName);
    exit(EXIT_FAILURE);
}

void checkAlloc(void *pointer, char *funcName, char *varName)
{
    if (pointer == NULL)
        errorMessageAlloc(funcName, varName);
}

void errorMessagePointer(char *funcName, char *varName)
{
    fprintf(stderr, "%s: Pointer (%s) is null\n", funcName, varName);
    exit(EXIT_FAILURE);
}

void checkNullPointer(void *pointer, char *funcName, char *varName)
{
    if (pointer == NULL)
        errorMessagePointer(funcName, varName);
}

void errorMessageMainArgs(char *problem)
{
    fprintf(stderr, "%s\n", problem);
    exit(EXIT_FAILURE);
}