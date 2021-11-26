#ifndef ERRORMESSAGE
#define ERRORMESSAGE

#include <stdio.h>
#include <stdlib.h>

/*
    Function: Checks if malloc/calloc worked correctly
    ---------------------------------------------------------------------------
    Checks if the memory allocation was successfull, if not stop execution
    and shows where the error was

    pointer: Variable to check
    funcName: Function where the allocation took place
    varName: Name of the variable
*/
void checkAlloc(void *pointer, char *funcName, char *varName);

/*
    Function: Checks if a given pointer is NULL
    ---------------------------------------------------------------------------
    Function will check if a pointer is null, and stops the program execution
    if true by priting in STDERR where the NULL was detected.

    pointer: Variable to check
    funcName: Function name where the variable was checked
    varName: Name of the variable

*/
void checkNullPointer(void *pointer, char *funcName, char *varName);

void errorMessageMainArgs(char *problem);

#endif
