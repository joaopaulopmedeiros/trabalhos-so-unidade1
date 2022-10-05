#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "matrix.h"

/**
 * @brief
 * checa se token não é vazio
 * @param token
 * @return int
 */
int isNotEmpty(char *token)
{
    if (strcmp(token, " ") && strcmp(token, "\n"))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief
 * Extrai uma matriz de um arquivo dado o seu path
 * @param path
 * @return Matrix
 */
Matrix extractMatrixFromFile(char *path)
{
    FILE *file = fopen(path, "r");

    char ch;

    int isReadingFileHeader = 1;
    int isMountingMatrix = 0;

    int totalMatrixRows = 0;
    int totalMatrixColumns = 0;

    int currentMatrixRow = 0;
    int currentMatrixColumn = 0;

    char *line = malloc(sizeof(char) * 10);

    int **matrix;

    while (fgets(line, sizeof(line), file))
    {
        char *token = strtok(line, " ");

        while (token != NULL)
        {
            // is file header
            if (isReadingFileHeader)
            {
                if (isNotEmpty(token))
                {
                    // set dimensions
                    if (!totalMatrixRows)
                    {
                        totalMatrixRows = atoi(token);
                    }

                    if (!totalMatrixColumns)
                    {
                        totalMatrixColumns = atoi(token);
                    }
                }
                else if (strcmp(token, "\n") == 0)
                {
                    isReadingFileHeader = 0;
                }
            } // is file body
            else
            {
                // check wether dimensions have been specified
                if (totalMatrixColumns <= 0 || totalMatrixRows <= 0)
                {
                    printf("Matrix must have a positive number of rows and columns");
                    exit(EXIT_FAILURE);
                }

                // start mounting matrix in memory
                if (!isMountingMatrix)
                {
                    // dynamic memory allocation (heap)
                    matrix = malloc(sizeof(int *) * totalMatrixRows);

                    for (int i = 0; i < totalMatrixRows; i++)
                    {
                        matrix[i] = malloc(sizeof(int) * totalMatrixColumns);
                    }

                    isMountingMatrix = 1;

                    printf("Memory in heap is allocated\n");
                }

                // push item to matrix
                if (isNotEmpty(token))
                {
                    matrix[currentMatrixRow][currentMatrixColumn] = atoi(token);
                    currentMatrixColumn++;
                }
                else if (strcmp(token, "\n") == 0)
                {
                    currentMatrixRow++;
                    currentMatrixColumn = 0;
                }
            }

            token = strtok(NULL, " ");
        }
    }

    free(line);
    fclose(file);

    Matrix m;

    m.totalColumns = totalMatrixColumns;
    m.totalRows = totalMatrixRows;
    m.items = matrix;

    return m;
}

/**
 * @brief
 * Exibe matriz em terminal
 * @param m
 */
void printMatrix(Matrix m)
{
    for (size_t i = 0; i < m.totalRows; i++)
    {
        for (size_t j = 0; j < m.totalColumns; j++)
        {
            printf("%d ", m.items[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief
 * Limpa matriz da memória heap
 * @param m
 */
void cleanMatrix(Matrix m)
{
    for (int i = 0; i < m.totalRows; i++)
    {
        free(m.items[i]);
    }

    free(m.items);
}
