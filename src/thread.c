#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include "matrix.c"

void *runThread(void *tid)
{
    printf("Hello. I'm thread n%d\n", (int)(size_t)tid);
    sleep(((int)(size_t)tid + 1) * 2);
    pthread_exit(NULL);
}

/**
 * @brief
 * Um programa que recebe como entrada dois arquivos
 * que descrevem duas matrizes M1 e M2 e um número inteiro P, através da
 * linha de comando. O programa deve implementar a multiplicação de
 * matrizes através de threads, para cada P elementos da matriz resultado uma
 * thread deve ser criada. O programa deve inicialmente abrir, ler os números
 * e fechar o arquivo antes de criar as threads.
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char **argv)
{
    printf("Running thread parallel script\n");

    Matrix m1 = extractMatrixFromFile(argv[1]);
    Matrix m2 = extractMatrixFromFile(argv[2]);
    int itemsPerThread = atoi(argv[3]);

    int numberOfThreads = m1.totalRows * m2.totalColumns / itemsPerThread;
    pthread_t threads[numberOfThreads];
    void *threadReturn;
    int status = 0;

    for (size_t i = 0; i < numberOfThreads; i++)
    {
        printf("Main process creating thread n%d\n", i);
        status = pthread_create(&threads[i], NULL, runThread, (void *)i);
        if (status != 0)
        {
            printf("Error on attempt to create thread. Code: %d\n", status);
            cleanMatrix(m1);
            cleanMatrix(m2);
            exit(EXIT_FAILURE);
        }
    }

    for (size_t i = 0; i < numberOfThreads; i++)
    {
        printf("Waiting for thread %d finish\n", i);
        pthread_join(threads[i], &threadReturn);
        printf("Thread %d has finished\n", i);
    }

    cleanMatrix(m1);
    cleanMatrix(m2);

    printf("Thread parallel script's done\n");

    return 0;
}
