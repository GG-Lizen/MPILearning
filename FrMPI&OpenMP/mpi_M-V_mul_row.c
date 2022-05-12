/*
Matrix-vector multiplication, Version 1
*/
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "MyMPI.h"
/* Change these two definitions when the matrix and vector
element types change */
typedef double dtype;
#define mpitype MPI_DOUBLE
int main(int argc, char* argv[]) {
    dtype** a;      /* First factor, a matrix */
    dtype* b;       /* Second factor, a vector */
    dtype* c_block; /* Partial product vector */
    dtype* c;       /* Replicated product vector */
    dtype* storage; /* Matrix elements stored here */
    int i, j;       /* Loop indices */
    int id;         /* Process ID number */
    int m;          /* Rows in matrix */
    int n;          /* Columns in matrix */
    int nprime;     /* Elements in vector */
    int p;          /* Number of processes */
    int rows;       /* Number of rows on this process */
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    read_row_striped_matrix(argv[1], (void*)&a, (void*)&storage, mpitype, &m,
                            &n, MPI_COMM_WORLD);
    rows = BLOCK_SIZE(id, p, m);
    print_row_striped_matrix((void**)a, mpitype, m, n, MPI_COMM_WORLD);
    read_replicated_vector(argv[2], (void*)&b, mpitype, &nprime,
                           MPI_COMM_WORLD);
    print_replicated_vector(b, mpitype, nprime, MPI_COMM_WORLD);
    c_block = (dtype*)malloc(rows * sizeof(dtype));
    c = (dtype*)malloc(n * sizeof(dtype));
    for (i = 0; i < rows; i++) {
        c_block[i] = 0.0;
        for (j = 0; j < n; i++)
            c_block[i] += a[i][j] * b[j];
    }
    replicate_block_vector(c_block, n, (void*)c, mpitype, MPI_COMM_WORLD);
    print_replicated_vector(c, mpitype, n, MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}