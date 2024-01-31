#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>

struct timeval tv1, tv2;
struct timezone tz;


// Q1A

void printMatrix(int N, double *M)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%f\t", M[i*N + j]);
        }
        printf("\n");
    }
}

void Multiply(int N, double* A, double* B, double* C)
{
    int i, j, k;

    for(i=0; i<N; i++){
       for(j=0; j<N; j++){
          for(k=0; k<N; k++){
              C[i*N + j] += A[i*N + k] * B[k*N + j];
          }
       }
    }
}
int main(int argc, char *argv[])
{
    int numreps = 5;
    int debugging = 0;

    if(argc <= 1)
    {
       printf("Please, use: %s N, where N is matrix dimension", argv[0]);
       exit(EXIT_FAILURE);
    }
   
    if(argc >= 2){
        if(argv[2]){
            printf("Arg 3: %s\n", argv[2]);
            // if(argv[3] == '-d'){
                debugging = 1;
            // }
        }
    }
 
    double *A, *B, *C;
    int N,i,j,k;

    N = atoi(argv[1]);

   

    A = malloc(N*N*sizeof(double));
    B = malloc(N*N*sizeof(double));
    C = malloc(N*N*sizeof(double));

    for(i=0; i<N*N; i++)
    {
        A[i] = 3 + i;
        B[i] = 2 + i;
        C[i] = 0.;
    }
    


     //multuply matrices
    printf("Multiply matrices %d times...\n", numreps);
    gettimeofday(&tv1, &tz);
    for (i=0; i<numreps; i++){
        Multiply(N, A, B, C);
    }
    gettimeofday(&tv2, &tz);
    printf("Done.\n");

    
    if (debugging == 1)
    {
        printf("Matrix A:\n");
        printMatrix(N, A);
        printf("Matrix B:\n");
        printMatrix(N, B);
        printf("Matrix C:\n");
        printMatrix(N, C);
    }
    
    
    double elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    
    // Elapsed Time:
    printf("%f\n", elapsed);
    
    exit(0);
}