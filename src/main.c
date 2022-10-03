#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

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

  printf("M1 is %dx%d\nM2 is %dx%d", n1, m1, n2, m2);

  return 0;
}