#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "matrix.c"

/**
 * @brief
 * Salva resultado da multiplicação de duas matrizes com abordagem sequencial.
 * Adiciona no cabeçalho as dimensões e no rodapé o tempo gasto na execução do programa
 * @param m1
 * @param m2
 * @param path
 * @param startedAt
 */
void saveMatrixMultiplicationResultIntoFile(Matrix m1, Matrix m2, char *path)
{
    clock_t startedAt = clock();

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

    Matrix m1 = extractMatrixFromFile(argv[1]);
    Matrix m2 = extractMatrixFromFile(argv[2]);

    saveMatrixMultiplicationResultIntoFile(m1, m2, ".\\assets\\m_result_seq.txt");

    cleanMatrix(m1);
    cleanMatrix(m2);

    printf("Sequential script's done\n");

    return 0;
}
