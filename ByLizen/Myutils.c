#include "Myutils.h"

/*
 *   Given MPI_Datatype 't', function 'get_size' returns the
 *   size of a single datum of that data type.
 */

int get_size(MPI_Datatype t) {
    if (t == MPI_BYTE)
        return sizeof(char);
    if (t == MPI_DOUBLE)
        return sizeof(double);
    if (t == MPI_FLOAT)
        return sizeof(float);
    if (t == MPI_INT)
        return sizeof(int);
    printf("Error: Unrecognized argument to 'get_size'\n");
    fflush(stdout);
    MPI_Abort(MPI_COMM_WORLD, TYPE_ERROR);
}

/*
 *   Function 'my_malloc' is called when a process wants
 *   to allocate some space from the heap. If the memory
 *   allocation fails, the process prints an error message
 *   and then aborts execution of the program.
 */

void* my_malloc(int id,    /* IN - Process rank */
                int bytes) /* IN - Bytes to allocate */
{
    void* buffer;
    if ((buffer = malloc((size_t)bytes)) == NULL) {
        printf("Error: Malloc failed for process %d\n", id);
        fflush(stdout);
        MPI_Abort(MPI_COMM_WORLD, MALLOC_ERROR);
    }
    return buffer;
}

/*
 *   Process p-1 opens a file and inputs a two-dimensional
 *   matrix, reading and distributing blocks of rows to the
 *   other processes.
 */

void read_array(char* s,            /* IN - File name */
                void** storage,     /* OUT - Submatrix stored here */
                MPI_Datatype dtype, /* IN - Matrix element type */
                int* n,             /* OUT - Array size */
                MPI_Comm comm)      /* IN - Communicator */
{
    int datum_size; /* Size of element */
    int i;
    int id;            /* Process rank */
    FILE* infileptr;   /* Input file pointer */
    int local_size;    /* Rows on this proc */
    int p;             /* Number of processes */
    MPI_Status status; /* Result of receive */
    int x;             /* Result of read */

    MPI_Comm_size(comm, &p);
    MPI_Comm_rank(comm, &id);
    datum_size = get_size(dtype);

    /* Process p-1 opens file, reads size of matrix,
       and broadcasts matrix dimensions to other procs */

    if (id == (p - 1)) {
        infileptr = fopen(s, "r");
        if (infileptr == NULL)
            *n = 0;
        else {
            fread(n, sizeof(int), 1, infileptr);
        }
    }
    MPI_Bcast(n, 1, MPI_INT, p - 1, comm);

    if (!(*n))
        MPI_Abort(MPI_COMM_WORLD, OPEN_FILE_ERROR);

    MPI_Bcast(n, 1, MPI_INT, p - 1, comm);

    local_size = BLOCK_SIZE(id, p, *n);

    *storage = (void*)my_malloc(id, local_size * datum_size);  //申请自己的内存

    if (id == (p - 1)) {
        for (i = 0; i < p - 1; i++) {
            x = fread(*storage, datum_size, BLOCK_SIZE(i, p, *n), infileptr);
            MPI_Send(*storage, BLOCK_SIZE(i, p, *n), dtype, i, DATA_MSG, comm);
        }
        x = fread(*storage, datum_size, local_size, infileptr);
        fclose(infileptr);
    } else
        MPI_Recv(*storage, local_size, dtype, p - 1, DATA_MSG, comm, &status);
}