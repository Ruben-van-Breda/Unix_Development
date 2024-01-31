#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <mpi.h>


/* This is based on the example provided in our course work */

/*
Write a parallel MPI program computing the product of two n×n dense matrices on p processors so that
• p processors are involved in the computations.
• The 2-dimensional parallel algorithm of matrix multiplication is employed:
- the matrices are identically and equally partitioned in two dimension into p squares
- there is one-to-one mapping between the partitions and the processors
- each processor is responsible for computation of the corresponding square of the resulting
matrix

*/


int N, p;

// Function to print a matrix 
void printMatrix(double *mat) 
{ 
	for (int i = 0; i < N; i++) 
	{ 
		for (int j = 0; j < N; j++) 
			printf("%f ", mat[i*N +j]); 

		printf("\n"); 
	} 
} 

int main(int argc, char **argv)
{
    int myn, myrank;
    double *a, *b, *c, *allB, start, sum, *allC, sumdiag;

    int i, j, k;

    N = atoi(argv[1]);
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    print("Number of processors used: %d", p);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    myn = N / p;
    a = malloc(myn * N * sizeof(double));
    b = malloc(myn * N * sizeof(double));
    c = malloc(myn * N * sizeof(double));
    allB = malloc(N * N * sizeof(double));
    
    /* Initialise array values */
    // populate matrix values 
    for (i = 0; i < myn * N; i++)
    {
        a[i] = 1. + i;
        b[i] = 2. + i;
    }

    MPI_Barrier(MPI_COMM_WORLD);
    if (myrank == 0)
        start = MPI_Wtime();
    for (i = 0; i < p; i++)
        MPI_Gather(b, myn * N, MPI_DOUBLE, allB, myn * N, MPI_DOUBLE,
                   i, MPI_COMM_WORLD);
    for (i = 0; i < myn; i++)
        for (j = 0; j < N; j++)
        {
            sum = 0.;
            for (k = 0; k < N; k++)
                sum += a[i * N + k] * allB[k * N + j];
            c[i * N + j] = sum;
        }
    free(allB);
    MPI_Barrier(MPI_COMM_WORLD);
    if (myrank == 0)
        printf("It took %f seconds to multiply 2 %dx%d matrices.\n",
               MPI_Wtime() - start, N, N);
    if (myrank == 0)
        allC = malloc(N * N * sizeof(double));
    MPI_Gather(c, myn * N, MPI_DOUBLE, allC, myn * N, MPI_DOUBLE,
               0, MPI_COMM_WORLD);
    if (myrank == 0)
    {
        // for (i = 0, sumdiag = 0.; i < N; i++)
        //     sumdiag += allC[i * N + i];
        // printf("The trace of the resulting matrix is %f\n", sumdiag);
    }
    if (myrank == 0)
        free(allC);
    MPI_Finalize();

    printMatrix(c);

    free(a);
    free(b);
    free(c);
}
