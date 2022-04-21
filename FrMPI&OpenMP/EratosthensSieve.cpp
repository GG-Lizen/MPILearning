#include <math.h>
#include <stdio.h>
#include "MyMPI.h"
#include "mpi.h"
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main(int argc, char* argv[]) {
    int count;           /* Local prime count */
    double elapsed_time; /* Parallel execution time */
    int first;           /* Index of first multiple */
    int global_count;    /* Global prime count */
    int high_value;      /* Highest value on this proc */
    int i;
    int id;         /* Process ID number */
    int index;      /* Index of current prime */
    int low_value;  /* Lowest value on this proc */
    char* marked;   /* Portion of 2,...,'n' */
    int n;          /* Sieving from 2, ..., 'n' */
    int p;          /* Number of processes */
    int proc0_size; /* Size of proc 0's subarray */
    int prime;      /* Current prime */
    int size;       /* Elements in 'marked' */

    MPI_Init(&argc, &argv);

    /* Start the timer */
    MPI_Barrier(MPI_COMM_WORLD);
    elapsed_time = -MPI_Wtime();
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    // must specified upper bound
    // !id => master
    if (argc != 2) {
        if (!id)
            printf("Command line: %s <m>\n", argv[0]);
        MPI_Finalize();
        exit(1);
    }

    n = atoi(argv[1]);

    /* Figure out this process's share of the array, as
       well as the integers represented by the first and
       last array elements */

    low_value = 2 + BLOCK_LOW(id, p, n - 1);  //进程的第一个数 2开始，n是上界
    high_value = 2 + BLOCK_HIGH(id, p, n - 1);  //进程的最后一个数
    size = BLOCK_SIZE(id, p, n - 1);            //进程处理的数组大小

    /* Bail out if all the primes used for sieving are
       not all held by process 0 */

    proc0_size = (n - 1) / p;

    if ((2 + proc0_size) <
        (int)sqrt((double)n)) {  // ? 2开始  2 + proc0_size 0所拥有的最大数
        if (!id)
            printf("Too many processes\n");
        MPI_Finalize();
        exit(1);
    }

    /* Allocate this process's share of the array. */

    marked = (char*)malloc(size);

    if (marked == NULL) {
        printf("Cannot allocate enough memory\n");
        MPI_Finalize();
        exit(1);
    }

    for (i = 0; i < size; i++)
        marked[i] = 0;
    if (!id)
        index = 0;
    prime = 2;  //从素数2开始
    do {
        //确定素数的第一个倍数的下标（局部下标）
        if (prime * prime > low_value)
            first = prime * prime - low_value;
        else {
            if (!(low_value % prime))
                first = 0;
            else
                first = prime -
                        (low_value % prime);  // (p)--(r)--(lv)--(p-r)--(p+p)
        }

        for (i = first; i < size; i += prime)
            marked[i] = 1;
        if (!id) {
            while (marked[++index])
                ;
            prime = index + 2;  //  下标从0开始 但数从2开始
        }
        MPI_Bcast(&prime, 1, MPI_INT, 0, MPI_COMM_WORLD);
    } while (prime * prime <= n);

    count = 0;
    for (i = 0; i < size; i++)
        if (!marked[i])
            count++;
    MPI_Reduce(&count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    /* Stop the timer */

    elapsed_time += MPI_Wtime();

    /* Print the results */

    if (!id) {
        printf("There are %d primes less than or equal to %d\n", global_count,
               n);
        printf("Total elapsed time: %10.6f\n", elapsed_time);
    }
    MPI_Finalize();
    return 0;
}