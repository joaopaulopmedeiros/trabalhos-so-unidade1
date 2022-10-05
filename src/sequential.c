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
 * checa se token é numererico
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

/**
 * @brief
 * Salva resultado da multiplicação de duas matrizes com abordagem sequencial.
 * Adiciona no cabeçalho as dimensões e no rodapé o tempo gasto na execução do programa
 * @param m1
 * @param m2
 * @param path
 * @param startedAt
 */
void saveMatrixMultiplicationResultIntoFile(Matrix m1, Matrix m2, char *path, clock_t startedAt)
{
    FILE *file = fopen(path, "w");

    fprintf(file, "%d %d\n", m1.totalRows, m2.totalColumns);

    for (int i = 0; i < m1.totalRows; i++)
    {
        for (int j = 0; j < m2.totalColumns; j++)
        {
            int sum = 0;

            for (int k = 0; k < m2.totalRows; k++)
            {
                sum += m1.items[i][k] * m2.items[k][j];
            }

            fprintf(file, "c%d%d %d\n", i + 1, j + 1, sum);
        }
    }

    clock_t finishedAt = clock();

    double timeSpent = (double)(finishedAt - startedAt) / CLOCKS_PER_SEC;

    fprintf(file, "%f", timeSpent);

    fclose(file);
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

    clock_t startedAt = clock();

    Matrix m1 = extractMatrixFromFile(argv[1]);
    printf("M1\n");
    printMatrix(m1);

    Matrix m2 = extractMatrixFromFile(argv[2]);
    printf("M2\n");
    printMatrix(m2);

    saveMatrixMultiplicationResultIntoFile(m1, m2, ".\\assets\\m_result_seq.txt", startedAt);

    printf("Cleaning up\n");
    cleanMatrix(m1);
    cleanMatrix(m2);

    printf("Sequential script's done\n");
    return 0;
}
