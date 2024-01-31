#include <stdio.h>
#include <stdlib.h>

// #ifndef MATRIX_MANAGER
// #define MATRIX_MANAGER
// #include "matrix.h"
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

#define MAX_ROW 10
#define MAX_COL = 10

typedef double matrix_data_type;


typedef struct {
    int row_size;
    int col_size;
    int size;
    matrix_data_type *data; 
} SomeMatrix;



SomeMatrix allocateMemory(int rowCount, int colCount){
    SomeMatrix *res = (SomeMatrix *)malloc(sizeof(SomeMatrix));
    res->size = rowCount;
    res->row_size = rowCount;
    res->col_size = colCount;
    res->data = malloc(rowCount * colCount * sizeof(matrix_data_type *));
    return *res;
}

SomeMatrix createMatrix(int N){
    SomeMatrix *res = (SomeMatrix *)malloc(sizeof(SomeMatrix));
    res->size = N;
    res->row_size = res->col_size = N;
    res->data = malloc(N * N * sizeof(matrix_data_type *));


    /* Populate matrix values*/
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++){
            res->data[r * res->col_size + c] = 1 + c;
        }

    }

    return *res;


}

matrix_data_type* create2DArray(int m, int n)
{
    // matrix_data_type *values = calloc(m * n, sizeof(matrix_data_type));
    matrix_data_type *rows = malloc(n * m * sizeof(matrix_data_type));

    for (int i = 0; i < n*m; ++i)
    {
        rows[i] = ( i * m);
    }

    return &rows;
}

void DisplayMatrix(SomeMatrix matrix)
{
    for (int r = 0; r < matrix.row_size; r++)
    {
        for (int c = 0; c < matrix.col_size; c++)
        {
            printf("%.0f ", matrix.data[r * matrix.col_size + c]);
        }
        printf("\n");
    }
    printf("\n");
}


void free_matrix(SomeMatrix *mat)
{
        free(mat->data);
        free(mat);
}


// #endif