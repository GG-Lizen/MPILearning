# MPI Turtorrials (LLNL)



site https://hpc-tutorials.llnl.gov/mpi/



## What is MPI



**M P I** = **M**essage **P**assing **I**nterface



data is moved from the address space of one process to that of another process through cooperative operations on each process.



### Reasons for Using MPI



- **Standardization**
- **Portability**
- **Performance Opportunities**
- **Functionality**
- **Availability**



![img](https://s2.loli.net/2022/02/07/kgu35I16DCVGl7z.png)



## Implementations and Compilers



### Open MPI



#### General Information



Open MPI is a thread-safe, open source MPI implementation developed and supported by a consortium of academic, research, and industry partners.



Available on all LC Linux clusters. However, you’ll need to load the desired [module](https://hpc.llnl.gov/training/tutorials/livermore-computing-resources-and-environment#modules) first. For example:



```plain
module avail                 (list available modules)
module load openmpi/3.0.1    (use the module of interest)
```



This ensures that LC’s MPI wrapper scripts point to the desired version of Open MPI.



#### Compiling



See the MPI Build Scripts table below.



#### Running



Be sure to load the same Open MPI module that you used to build your executable. If you are running a batch job, you will need to load the module in your batch script.



Launching an Open MPI job can be done using the following commands. For example, to run a 48 process MPI job:



```plain
mpirun -np 48 a.out
mpiexec -np 48 a.out
srun -n 48 a.out
```



#### Documentation



Open MPI home page: http://www.open-mpi.org/



## Getting started



#### Program Structure:



![img](https://hpc-tutorials.llnl.gov/mpi/images/prog_structure.gif)



#### Format of MPI Calls:



C names are case sensitive;



Programs must not declare variables or functions with names beginning with the prefix `MPI_` or `PMPI_` (profiling interface).

| C Binding      |                                               |
| -------------- | --------------------------------------------- |
| Format:        | rc = MPI_Xxxxx(parameter, ... )               |
| Example:       | rc = MPI_Bsend(&buf,count,type,dest,tag,comm) |
| ???Error code: | Returned as "rc". MPI_SUCCESS if successful   |



#### Communicators and Groups:



simply use `MPI_COMM_WORLD` whenever a communicator is required - **it is the predefined communicator that includes all of your MPI processes.**



#### Rank:



Within a communicator, every process has its own unique, integer identifier assigned by the system when the process initializes. A rank is sometimes **also called a “task ID”.** Ranks are contiguous and begin at zero.



## Environment Management Routines



Most of the commonly used ones are described below.



[**MPI_Init**](https://hpc-tutorials.llnl.gov/mpi/MPI_INIT.txt)



Initializes the MPI execution environment. This function must be **called in every MPI program**, must be called before any other MPI functions and must be **called only once** in an MPI program. For C programs, MPI_Init may be used to pass the command line arguments to all processes, although this is not required by the standard and is implementation dependent.



```plain
MPI_Init (&argc,&argv)
```



[**MPI_Comm_size**](https://hpc-tutorials.llnl.gov/mpi/MPI_COMM_SIZE.txt)



Returns the total number of MPI processes in the **specified communicator**, such as MPI_COMM_WORLD. If the communicator is MPI_COMM_WORLD, then it represents the number of MPI tasks available to your application.



```plain
MPI_Comm_size (comm,&size)
```



[**MPI_Comm_rank**](https://hpc-tutorials.llnl.gov/mpi/MPI_COMM_RANK.txt)



Returns the rank of the calling MPI process within the specified communicator. Initially, each process will be assigned a unique integer rank between 0 and number of tasks - 1 within the communicator MPI_COMM_WORLD. This rank is often referred to as a task ID. `If a process becomes associated with other communicators, it will have a unique rank within each of these as well.`



```plain
MPI_Comm_rank (comm,&rank)
```



[**MPI_Abort**](https://hpc-tutorials.llnl.gov/mpi/MPI_ABORT.txt)



Terminates all MPI processes associated with the communicator. **In most MPI implementations it terminates ALL processes regardless of the communicator specified.**



```plain
MPI_Abort (comm,errorcode)
```



[**MPI_Get_processor_name**](https://hpc-tutorials.llnl.gov/mpi/MPI_GET_PROCESSOR_NAME.txt)



Returns the processor name. Also returns the length of the name. The buffer for “name” must be at least MPI_MAX_PROCESSOR_NAME characters in size. What is returned into “name” is implementation dependent - **may not be the same as** the output of the “hostname” or “host” shell commands.



```plain
MPI_Get_processor_name (&name,&resultlength)
```



[**MPI_Get_version**](https://hpc-tutorials.llnl.gov/mpi/MPI_GET_VERSION.txt)



Returns the version and subversion of the MPI standard that’s implemented by the library.



```plain
MPI_Get_version (&version,&subversion)
```



[**MPI_Initialized**](https://hpc-tutorials.llnl.gov/mpi/MPI_INITIALIZED.txt)



Indicates whether MPI_Init has been called (指示MPI_Init 是否被调用)- returns flag as either logical true (1) or false(0). MPI requires that MPI_Init be called once and only once by each process.



```plain
MPI_Initialized (&flag)
```



[**MPI_Wtime**](https://hpc-tutorials.llnl.gov/mpi/MPI_WTIME.txt)



Returns an elapsed（过去） wall clock time in seconds (double precision) on the calling processor.



```plain
Wall time, also called real-world time or wall-clock time, refers to elapsed time as determined by a chronometer such as a wristwatch or wall clock. ... In practical computing, wall time is the actual time, usually measured in seconds, that a program takes to run or to execute its assigned tasks.
```



```plain
MPI_Wtime ()
```



[**MPI_Wtick**](https://hpc-tutorials.llnl.gov/mpi/MPI_WTICK.txt)



Returns the resolution in seconds (double precision) of MPI_Wtime.



```plain
MPI_Wtick ()
```



[**MPI_Finalize**](https://hpc-tutorials.llnl.gov/mpi/MPI_FINALIZE.txt)



Terminates the MPI execution environment. This function **should be the last MPI routine called in every MPI program** - no other MPI routines may be called after it.



```plain
MPI_Finalize ()
```



## Point to Point Communication Routines

| Blocking sends       | MPI_Send(buffer,count,type,dest,tag,comm)            |
| -------------------- | ---------------------------------------------------- |
| Non-blocking sends   | MPI_Isend(buffer,count,type,dest,tag,comm,request)   |
| Blocking receive     | MPI_Recv(buffer,count,type,source,tag,comm,status)   |
| Non-blocking receive | MPI_Irecv(buffer,count,type,source,tag,comm,request) |

**Buffer**

Program (application) address space that references the data that is to be sent or received. In most cases, this is simply the variable name that is be sent/received. For C programs, this argument is passed by reference and usually must be prepended with an ampersand: `&var1`

**Data Count**

Indicates the number of data elements of a particular type to be sent.

**Data Type**

For reasons of portability, MPI predefines its elementary data types. The table below lists those required by the standard.

**Destination**

An argument to send routines that indicates the process where a message should be delivered. Specified as the rank of the receiving process.

**Source**

An argument to receive routines that indicates the originating process of the message. Specified as the rank of the sending process. This may be set to the wild card MPI_ANY_SOURCE to receive a message from any task.

**Tag**

Arbitrary non-negative integer assigned by the programmer to uniquely identify a message. Send and receive operations should match message tags. For a receive operation, the wild card MPI_ANY_TAG can be used to receive any message regardless of its tag. The MPI standard guarantees that integers 0-32767 can be used as tags, but most implementations allow a much larger range than this.

**Communicator**

Indicates the communication context, or set of processes for which the source or destination fields are valid. Unless the programmer is explicitly creating new communicators, the predefined communicator MPI_COMM_WORLD is usually used.

**Status**

For a receive operation, indicates the source of the message and the tag of the message. In C, this argument is a pointer to a predefined structure MPI_Status (ex. stat.MPI_SOURCE stat.MPI_TAG). In Fortran, it is an integer array of size MPI_STATUS_SIZE (ex. stat(MPI_SOURCE) stat(MPI_TAG)). Additionally, the actual number of bytes received is obtainable from Status via the MPI_Get_count routine. The constants MPI_STATUS_IGNORE and MPI_STATUSES_IGNORE can be substituted if a message’s source, tag or size will be be queried later.

**Request**

Used by non-blocking send and receive operations. Since non-blocking operations may return before the requested system buffer space is obtained, the system issues a unique “request number”. The programmer uses this system assigned “handle” later (in a WAIT type routine) to determine completion of the non-blocking operation. In C, this argument is a pointer to a predefined structure MPI_Request. In Fortran, it is an integer.







### Collective Communication Routines

[**MPI_Barrier**](https://hpc-tutorials.llnl.gov/mpi/collective_comms/MPI_Barrier.txt)

Synchronization operation. Creates a barrier synchronization in a group. Each task, when reaching the MPI_Barrier call, blocks until all tasks in the group reach the same MPI_Barrier call. Then all tasks are free to proceed.

```
MPI_Barrier (comm)
```

[**MPI_Bcast**](https://hpc-tutorials.llnl.gov/mpi/collective_comms/MPI_Bcast.txt)

Data movement operation. Broadcasts (sends) a message from the process with rank “root” to all other processes in the group. [Diagram here](https://hpc-tutorials.llnl.gov/mpi/collective_comms/images/MPI_Bcast.gif)

```
MPI_Bcast (&buffer,count,datatype,root,comm)
```

[**MPI_Scatter**](https://hpc-tutorials.llnl.gov/mpi/collective_comms/MPI_Scatter.txt)

Data movement operation. Distributes distinct messages from a single source task to each task in the group. [Diagram here](https://hpc-tutorials.llnl.gov/mpi/collective_comms/images/MPI_Scatter.gif)

```
MPI_Scatter (&sendbuf,sendcnt,sendtype,&recvbuf,recvcnt,recvtype,root,comm)
```

[**MPI_Gather**](https://hpc-tutorials.llnl.gov/mpi/collective_comms/MPI_Gather.txt)

Data movement operation. Gathers distinct messages from each task in the group to a single destination task. This routine is the reverse operation of MPI_Scatter. [Diagram here](https://hpc-tutorials.llnl.gov/mpi/collective_comms/images/MPI_Gather.gif)

```
MPI_Gather (&sendbuf,sendcnt,sendtype,&recvbuf,recvcount,recvtype,root,comm)
```

[**MPI_Allgather**](https://hpc-tutorials.llnl.gov/mpi/collective_comms/MPI_Allgather.txt)

Data movement operation. Concatenation of data to all tasks in a group. Each task in the group, in effect, performs a one-to-all broadcasting operation within the group. [Diagram here](https://hpc-tutorials.llnl.gov/mpi/collective_comms/images/MPI_Allgather.gif)

```
MPI_Allgather (&sendbuf,sendcount,sendtype,&recvbuf,recvcount,recvtype,comm)
```

[**MPI_Reduce**](https://hpc-tutorials.llnl.gov/mpi/collective_comms/MPI_Reduce.txt)

Collective computation operation. Applies a reduction operation on all tasks in the group and places the result in one task. [Diagram here](https://hpc-tutorials.llnl.gov/mpi/collective_comms/images/MPI_Reduce.gif)

```
MPI_Reduce (&sendbuf,&recvbuf,count,datatype,op,root,comm)
```













## Parallel Computer Memory Architectures



### Shared Memory



#### Uniform Memory Access (UMA)



- Most commonly represented today by ***Symmetric Multiprocessor (SMP)*** machines



![img](https://hpc.llnl.gov/sites/default/files/shared_mem.gif)



#### Non-Uniform Memory Access (NUMA)



- Often made by physically linking two or more SMPs



![img](https://hpc.llnl.gov/sites/default/files/numa.gif)



### Distributed Memory



![img](https://hpc.llnl.gov/sites/default/files/distributed_mem.gif)



### Hybrid Distributed-Shared Memory



![img](https://hpc.llnl.gov/sites/default/files/styles/large/public/hybrid_mem.gif?itok=Y_P9O-9C)



![img](https://hpc.llnl.gov/sites/default/files/styles/large/public/hybrid_mem2.gif?itok=SkSmq0l1)