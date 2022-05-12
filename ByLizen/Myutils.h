#ifndef MYMPI_H_
#define MYMPI_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mpi.h"
#define DATA_MSG 0
#define PROMPT_MSG 1
#define RESPONSE_MSG 2

#define OPEN_FILE_ERROR -1
#define MALLOC_ERROR -2
#define TYPE_ERROR -3

#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define BLOCK_LOW(id, p, n) ((id) * (n) / (p))
#define BLOCK_HIGH(id, p, n) (BLOCK_LOW((id) + 1, p, n) - 1)
#define BLOCK_SIZE(id, p, n) (BLOCK_HIGH(id, p, n) - BLOCK_LOW(id, p, n) + 1)
#define BLOCK_OWNER(j, p, n) (((p) * ((j) + 1) - 1) / (n))
#define PTR_SIZE (sizeof(void*))
#define CEILING(i, j) (((i) + (j)-1) / (j))

void read_array(char* s,            /* IN - File name */
                void** storage,     /* OUT - Submatrix stored here */
                MPI_Datatype dtype, /* IN - Matrix element type */
                int* n,             /* OUT - Array size */
                MPI_Comm comm);

int fwrite_MB_INT(const char* fileName, int size);
#endif