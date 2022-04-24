/******************************************************************************
 * FILE: mpi_MergeSort.c
 * DESCRIPTION:
 *   MPI Program - Merge Sort - C Version
 * AUTHOR: GG Lizen
 * LAST REVISED: 23/04/22
 ****************************************************************************/

#include <stdio.h>
#include "../FrMPI&OpenMP/MyMPI.h"
#include "mpi.h"
#define MASTER 0
int main(int argc, char* argv[]) {
    int numtasks, taskid, len;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);

    MPI_Finalize();
}