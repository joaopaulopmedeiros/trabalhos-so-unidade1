#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "matrix.h"

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

    int **matrix;

    while ((ch = fgetc(file)) != EOF)
    {
        // is file header
        if (isReadingFileHeader)
        {
            if (isdigit(ch))
            {
                // set dimensions
                if (!totalMatrixRows)
                {
                    totalMatrixRows = ch - '0';
                }

                if (!totalMatrixColumns)
                {
                    totalMatrixColumns = ch - '0';
                }
            }
            else if (ch == '\n')
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
            if (isdigit(ch))
            {
                matrix[currentMatrixRow][currentMatrixColumn] = ch - '0';
                currentMatrixColumn++;
            }
            else if (ch == '\n')
            {
                currentMatrixRow++;
                currentMatrixColumn = 0;
            }
        }
    }

    fclose(file);

    Matrix m;

    m.totalColumns = totalMatrixColumns;
    m.totalRows = totalMatrixRows;
    m.items = matrix;

    return m;
}

/**
 * @brief
 * Um programa que recebe como entrada dois arquivos que
 * descrevem duas matrizes M1 e M2, através da linha de comando. O
 * programa deve implementar a multiplicação das matrizes M1 e M2, de
 * forma convencional e salvar o resultado em um arquivo, o programa deve
 * salvar no arquivo o tempo que passou calculando o resultado.
 */
int main(int argc, char **argv)
{
    printf("Running sequential script\n");

    Matrix m1 = extractMatrixFromFile(argv[1]);

    for (size_t i = 0; i < m1.totalRows; i++)
    {
        for (size_t j = 0; j < m1.totalColumns; j++)
        {
            printf("%d ", m1.items[i][j]);
        }
        printf("\n");
    }

    printf("Cleaning up\n");

    for (int i = 0; i < m1.totalRows; i++)
    {
        free(m1.items[i]);
    }

    free(m1.items);

    printf("Sequential script's done\n");
    // int **m2 = extractMatrixFromFile(argv[2]);
    return 0;
}
