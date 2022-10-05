#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

/**
 * @brief
 * Insere uma matriz em um arquivo
 * @param n
 * @param m
 * @param path
 */
void insertMatrixIntoFile(int n, int m, char *path)
{
  FILE *file = fopen(path, "w");

  fprintf(file, "%d %d \n", n, m);

  srand(time(NULL));

  for (size_t i = 0; i < n; i++)
  {
    for (size_t j = 0; j < m; j++)
    {
      fprintf(file, "%c ", (rand() % 10) + '0');
    }
    fprintf(file, "\n");
  }

  fclose(file);
}

/**
 * @brief
 * Um programa que receba através da linha de comando 4
 * argumentos (n1, m1, n2, m2), representando as dimensões de 2 matrizes que
 * serão multiplicadas. Usando os 4 argumentos, o programa deve gerar
 * aleatoriamente duas matrizes, M1 e M2, de dimensões n1 x m1 e n2 x m2.
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char **argv)
{
  printf("Starting program\n");

  int n1, m1, n2, m2 = 0;

  printf("Setting program from input parameters\n");

  n1 = atoi(argv[1]);
  m1 = atoi(argv[2]);
  n2 = atoi(argv[3]);
  m2 = atoi(argv[4]);

  printf("M1 is %dx%d\nM2 is %dx%d\n", n1, m1, n2, m2);

  printf("Preparing files\n");

  insertMatrixIntoFile(n1, m1, ".\\assets\\M1.txt");

  insertMatrixIntoFile(n2, m2, ".\\assets\\M2.txt");

  printf("Files ready\n");

  return 0;
}