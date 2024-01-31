#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>

struct timeval tv1, tv2;
struct timezone tz;

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
       printf("Please, use: %s N, where N is matrix dimension", argv[0]);
       exit(EXIT_FAILURE);
    }
 
    double *A, *B, *C;
    int N,i,j,k;

    N = atoi(argv[1]);

    A = malloc(N*N*sizeof(double));
    B = malloc(N*N*sizeof(double));
    C = malloc(N*N*sizeof(double));

    for(i=0; i<N*N; i++)
    {
        A[i] = 3.;
        B[i] = 2.;
        C[i] = 0.;
    }

    gettimeofday(&tv1, &tz);
    
    for(i=0; i<N; i++){
       for(j=0; j<N; j++){
          for(k=0; k<N; k++){
              C[i*N + j] += A[i*N + k] * B[k + j*N];
          }
       }
    }

    
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
        //    printf("%f\t", C[i*N + j]);
        }
        // printf("\n");
    } 

    gettimeofday(&tv2, &tz);
    double elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    
    // Elapsed Time:
    printf("%f\n", elapsed);
    
    exit(0);
}