#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>

struct timeval tv1, tv2;
struct timezone tz;

void printMatrix(int N, double *M)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%f\t", M[i * N + j]);
        }
        printf("\n");
    }
}

void Multiply(int N, double *A, double *B, double *C)
{
    int i = 0;
    int j = 0;
    int k = 0;
   // printf("\n");
    for (k = 0; k < N; k++)
    {
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                C[i * N + j] += A[i * N + k] * B[k + j * N];
            }
      //      printf("\n");
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("Please, use: %s N, where N is matrix dimension", argv[0]);
        exit(EXIT_FAILURE);
    }

    double *A, *B, *C;
    int N, i, j, k;
    int numreps = 5;
    int verbose = 0;

    N = atoi(argv[1]);
    if (argc > 2)
    {
        verbose = 1;
    }

    A = malloc(N * N * sizeof(double));
    B = malloc(N * N * sizeof(double));
    C = malloc(N * N * sizeof(double));

    for (i = 0; i < N * N; i++)
    {
        A[i] = 2.;
        B[i] = 3.;
        C[i] = 0.;
    }

    gettimeofday(&tv1, &tz);
    //multuply matrices
    printf("Multiply matrices %d times...\n", numreps);
    gettimeofday(&tv1, &tz);
    for (i=0; i<numreps; i++){
        Multiply(N, A, B, C);
    }
    gettimeofday(&tv2, &tz);
    printf("Done.\n");

    if (verbose == 1)
    {
        printf("Matrix A:\n");
        printMatrix(N, A);
        printf("Matrix B:\n");
        printMatrix(N, B);
        printf("Matrix C:\n");
        printMatrix(N, C);
    }

    gettimeofday(&tv2, &tz);
    double elapsed = (double)(tv2.tv_sec - tv1.tv_sec) + (double)(tv2.tv_usec - tv1.tv_usec) * 1.e-6;

    // Elapsed Time:
    printf("%f\n", elapsed);

    exit(0);
}