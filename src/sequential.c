#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void extractMatrixFromFile(char *path)
{
    FILE *file = fopen(path, "r");
    char ch;
    int **matrix = malloc(sizeof(int **));
    int currentLine, currentColumn, totalLines, totalColumns = 0;

    while ((ch = fgetc(file)) != EOF)
    {
        if (isdigit(ch))
        {
            currentColumn++;

            if (currentLine == 0)
            {
                totalColumns = currentColumn;
            }

            printf("%c", ch);
        }
        else if (ch == '\n')
        {
            currentLine++;
            printf("\n");
        }
    }

    totalLines = currentLine;

    printf("Total Lines: %d\n", totalLines);
    printf("Total Columns: %d\n", totalColumns);

    fclose(file);
    free(matrix);
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
