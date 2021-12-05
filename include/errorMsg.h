#ifndef ERRORMESSAGE
#define ERRORMESSAGE

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Checks if the memory allocation was successfull, if not stop 
 * execution and shows where the error was
 * 
 * @param pointer Pointer to check if its null
 * @param funcName Function name that the alloc took place
 * @param varName Name of the variable
 */
void checkAlloc(void *pointer, char *funcName, char *varName);

/**
 * @brief Function will check if a pointer is null, and stops the program execution
 * if true by priting in STDERR where the NULL was detected.
 * 
 * @param pointer Pointer to check if its null
 * @param funcName Function name that called this function
 * @param varName Var name
 */
void checkNullPointer(void *pointer, char *funcName, char *varName);

void errorMessageMainArgs(char *problem);

#endif
