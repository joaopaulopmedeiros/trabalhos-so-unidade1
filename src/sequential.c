#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

void extractMatrixFromFile(char *path)
{
    FILE *file = fopen(path, "r");
    char ch;
    int isReadingFileHeader = 1;
    int totalMatrixRows = 0;
    int totalMatrixColumns = 0;

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
        }
    }

    printf("Total Rows: %d\n", totalMatrixRows);
    printf("Total Columns: %d\n", totalMatrixColumns);

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
    printf("Running sequential approach\n");
    extractMatrixFromFile(argv[1]);
    // int **m2 = extractMatrixFromFile(argv[2]);
    return 0;
}
