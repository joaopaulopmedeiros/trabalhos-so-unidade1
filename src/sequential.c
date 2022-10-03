#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void extractMatrixFromFile(char *path)
{
    FILE *file = fopen(path, "r");
    char ch;
    int number = 0;

    while ((ch = fgetc(file)) != EOF)
    {
        if (isdigit(ch))
        {
            printf("%c", ch);
        }
    }

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
