/******************************************************************************
 * FILE: mpi_MergeSort.c
 * DESCRIPTION:
 *   MPI Program - Merge Sort - C Version
 * AUTHOR: GG Lizen
 * LAST REVISED: 23/05/7
 ****************************************************************************/

#include <stdio.h>
#include "Myutils.h"
#include "mpi.h"
#define MASTER 0
typedef int dtype;

void merge_sort(int arr[], int len);
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n);
int main(int argc, char* argv[]) {
    dtype* storage;        /* Local portion of array elements */
    dtype* storage_sample; /*Local storage of sample*/
    dtype* partitions;     /*中值*/
    int n;
    int numtasks, taskid, len;
    double elapsed_time; /* Parallel execution time */
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);

    if (argc != 2) {
        if (taskid == MASTER)
            printf("Command line: %s <m>\n", argv[0]);
        MPI_Finalize();
        exit(1);
    }

    partitions = malloc(sizeof(dtype) * (numtasks - 1));

    if (taskid == MASTER)
        storage_sample = malloc(sizeof(dtype) * numtasks * numtasks);
    else
        storage_sample = malloc(sizeof(dtype) * numtasks);
    // printf("task %d : first element:%d last element %d,block size %d\n",
    // taskid,
    //        storage[0], storage[BLOCK_SIZE(taskid, numtasks, n) - 1],
    //        BLOCK_SIZE(taskid, numtasks, n));

    // phrase 1
    read_array(argv[1], (void*)&storage, MPI_INT, &n,
               MPI_COMM_WORLD);  //分发数据

    /* Start the timer */
    MPI_Barrier(MPI_COMM_WORLD);
    elapsed_time = -MPI_Wtime();

    merge_sort(storage, BLOCK_SIZE(taskid, numtasks, n));

    for (int i = 0; i < numtasks; i++) {
        storage_sample[i] =
            storage[i * BLOCK_SIZE(taskid, numtasks, n) / numtasks];
    }
    MPI_Gather(storage_sample, numtasks, MPI_INT, storage_sample, numtasks,
               MPI_INT, MASTER, MPI_COMM_WORLD);

    // phrase 2
    if (taskid == MASTER) {
        merge_sort(storage_sample, numtasks * numtasks);
        for (int i = 1; i < numtasks; i++) {
            partitions[i - 1] = storage_sample[i * numtasks];
        }
    }
    MPI_Bcast(partitions, numtasks - 1, MPI_INT, MASTER, MPI_COMM_WORLD);
    // phrase 3
    // send_dis send_cnt
    //每段开始下标
    dtype* partStartIndex = malloc(sizeof(dtype) * numtasks);
    //每段长度
    dtype* partLen = malloc(sizeof(dtype) * numtasks);
    //元素下标
    int dIndex = 0;

    for (int i = 0; i < numtasks - 1; i++) {
        partStartIndex[i] = dIndex;
        partLen[i] = 0;
        while ((dIndex < BLOCK_SIZE(taskid, numtasks, n)) &&
               (storage[dIndex] <= partitions[i])) {
            dIndex++;
            partLen[i]++;
        }
    }
    partStartIndex[numtasks - 1] = dIndex;
    partLen[numtasks - 1] = BLOCK_SIZE(taskid, numtasks, n) - dIndex;

    dtype* recvPartLen = malloc(sizeof(dtype) * numtasks);
    //通知每个进程要准备接收多少数据
    /*
    int MPI_Alltoall(const void* buffer_send,
                 int count_send,
                 MPI_Datatype datatype_send,
                 void* buffer_recv,
                 int count_recv,
                 MPI_Datatype datatype_recv,
                 MPI_Comm communicator);
    */
    // recv_dis recv_cnt
    MPI_Alltoall(partLen, 1, MPI_INT, recvPartLen, 1, MPI_INT, MPI_COMM_WORLD);

    //接收数据相对于接受缓冲区起始位置的偏移量
    int sumPartLen = 0;
    int* newPartStart = malloc(sizeof(dtype) * numtasks);
    for (int i = 0; i < numtasks; i++) {
        newPartStart[i] = sumPartLen;
        sumPartLen += recvPartLen[i];
    }
    dtype* recvPartDate = malloc(sizeof(dtype) * sumPartLen);
    // 发送数据段和接收数据段
    /*
    int MPI_Alltoallv(const void* buffer_send,
                  const int* counts_send,
                  const int* displacements_send,
                  MPI_Datatype datatype_send,
                  void* buffer_recv,
                  const int* counts_recv,
                  const int* displacements_recv,
                  MPI_Datatype datatype_recv,
                  MPI_Comm communicator);
    */
    MPI_Alltoallv(storage, partLen, partStartIndex, MPI_INT, recvPartDate,
                  recvPartLen, newPartStart, MPI_INT, MPI_COMM_WORLD);

    // phrase 4
    merge_sort(recvPartDate, sumPartLen);

    /* Stop the timer */

    elapsed_time += MPI_Wtime();

    /* Print the results */

    if (taskid == MASTER) {
        printf("Total elapsed time: %10.6f\n", elapsed_time);
    }
    printf("task%d low:%d high:%d\n", taskid, recvPartDate[0],
           recvPartDate[sumPartLen - 1]);

    MPI_Finalize();
}
int min(int x, int y) {
    return x < y ? x : y;
}
void merge_sort(int arr[], int len) {
    int* a = arr;
    int* b = (int*)malloc(len * sizeof(int));
    int seg, start;
    for (seg = 1; seg < len; seg += seg) {
        for (start = 0; start < len; start += seg * 2) {
            int low = start, mid = min(start + seg, len),
                high = min(start + seg * 2, len);
            int k = low;
            int start1 = low, end1 = mid;
            int start2 = mid, end2 = high;
            while (start1 < end1 && start2 < end2)
                b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
            while (start1 < end1)
                b[k++] = a[start1++];
            while (start2 < end2)
                b[k++] = a[start2++];
        }
        int* temp = a;
        a = b;
        b = temp;
    }
    if (a != arr) {
        int i;
        for (i = 0; i < len; i++)
            b[i] = a[i];
        b = a;
    }
    free(b);
}
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    int p1 = 0, p2 = 0;
    int* sorted = malloc(sizeof(int) * (m + n));
    int cur;
    while (p1 < m || p2 < n) {
        if (p1 == m) {
            cur = nums2[p2++];
        } else if (p2 == n) {
            cur = nums1[p1++];
        } else if (nums1[p1] < nums2[p2]) {
            cur = nums1[p1++];
        } else {
            cur = nums2[p2++];
        }
        sorted[p1 + p2 - 1] = cur;
    }
    for (int i = 0; i != m + n; ++i) {
        nums1[i] = sorted[i];
    }
}