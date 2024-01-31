#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

struct timeval tv1, tv2;
struct timezone tz;

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void printMatrix(int N, double *M)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%f\t", M[i*N +j]);
        }
        printf("\n");
    }
}

/*
Number of memory accesses: 2 * N^3 * n/N * n/N (read each block of A and B N^3 times) + 2 * N^2 * n/N *n/N (read and write each block of C once in the second nested loop N^2 times). This transformation is called loop tiling.
The improvement = n^3/N*n^2 = n/N = b. In general, increasing b sounds like a good idea, but only until all three arrays can fit in the cache. Thus if the cache-size is M, then the maximum block-size we can have is sqrt(M/3) (which is also the maximum speedup we can have).
*/

/// @brief  Matrix multiplication with blocking
/// @param N dimenstion
/// @param blockSize 
/// @param A 
/// @param B 
/// @param C 
void Multiply(int N, int blockSize, double *A, double *B, double *C)
{   
    int i, j, k;
    int bi, bj, bk;

    int sum = 0.0;

    for (bi = 0; bi < N; bi += blockSize)
    {
        for (bj = 0; bj < N; bj += blockSize)
        {
            for (i = 0; i < N; i++)
            {
                for (j = bi; j < bi + blockSize; j++)
                {
                    for (k = bj; k < bj + blockSize; k++)
                    {
                        /* code */
                        C[i*N + j] += A[i*N + k] * B[k*N + j];
                    }
                    
                }
                
            }
            
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        printf("Please, use: %s N, where N is matrix dimension", argv[0]);
        exit(EXIT_FAILURE);
    }

    // double **A, **B, **C;
    double *A, *B, *C;
    int N, i, j, k;
    int numreps = 5;
    int debugging = 0;
    N = atoi(argv[1]);
    int blockSize = 1;

    blockSize = atoi(argv[2]);
    // NOTE: the block size must be a factor of the matrix size!
    if (N % blockSize != 0)
    {
        printf("the block size must be a factor of %d the matrix size!", N);
        exit(1);
    }

    if (argc >= 3)
    {
        if (argv[3])
        {
            printf("Arg 3: %s", argv[3]);
            // if(argv[3] == '-d'){
            debugging = 1;
            // }
        }
    }

    // allocate memory for the matrices

    // note that for each matrix there
    // are only two memory allocations

    A = malloc(N*N*sizeof(double));
    B = malloc(N*N*sizeof(double));
    C = malloc(N*N*sizeof(double));

    for(i=0; i<N*N; i++)
    {
        A[i] = 3.;
        B[i] = 2.;
        C[i] = 0.;
    }

    //multuply matrices
    printf("Multiply matrices %d times...\n", numreps);
    gettimeofday(&tv1, &tz);
    for (i=0; i<numreps; i++){
        Multiply(N, blockSize, A, B, C);
    }
    gettimeofday(&tv2, &tz);
    printf("Done.\n");

    if(debugging == 1){
        printMatrix(N, C);
    }

    double elapsed = (double)(tv2.tv_sec - tv1.tv_sec) + (double)(tv2.tv_usec - tv1.tv_usec) * 1.e-6;
    // Print Elapsed Time
    printf("%f\n", elapsed);
    
    // deallocate memory
    // free(A[0]);
    // free(A);
    // free(B[0]);
    // free(B);
    // free(C[0]);
    // free(C);

    return 0;

    exit(0);
}