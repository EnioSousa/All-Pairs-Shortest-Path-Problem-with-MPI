#include "basicFunc.h"

int **newBiArray(int size, int defaultValue)
{
    int **biArray = (int **)malloc(size * sizeof(int *));
    checkAlloc(biArray, "newbiArray", "biArray");

    for (int i = 0; i < size; i++)
        biArray[i] = newArray(size, defaultValue);

    return biArray;
}

int *newArray(int size, int defaultValue)
{
    int *array = (int *)malloc(size * sizeof(int));
    checkAlloc(array, "newArray", "array");

    for (int i = 0; i < size; i++)
        array[i] = defaultValue;

    return array;
}

void printBiArray(int **biArray, int n, int m)
{
    printf("BI ARRAY SIZE: %d x %d\n", n, m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%d ", biArray[i][j]);

        printf("\n");
    }
    printf("\n");
}

void printArray(int *array, int n)
{
    printf("ARRAY SIZE: %d\n", n);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }

    printf("\n");
}