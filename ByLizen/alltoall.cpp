#include <iostream>
#include <vector>
#include "mpi.h"

using namespace std;

int main(int argc, char* argv[]) {
    int myid, numprocs;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    int sendCounts[numprocs];
    int recvCounts[numprocs];
    int sdisp[numprocs];
    int rdisp[numprocs];

    std::vector<int> nums;  //要发送的数据是一个数组，里面装了10个int
    for (int i = 0; i < 10; ++i) {
        nums.push_back(i);
    }

    //要发送给其他节点的数据的数量,转化成byte来发送
    //发送给0号节点3个int，
    //发送给1号节点0个int，
    //发送给2号节点3个int
    sendCounts[0] = 3;
    sendCounts[1] = 0;
    sendCounts[2] = 3;
    sendCounts[3] = 4;
    sendCounts[4] = 0;

    //提前通知一下节点，各个节点要准备接收多少数据
    MPI_Alltoall(sendCounts, 1, MPI_INT, recvCounts, 1, MPI_INT,
                 MPI_COMM_WORLD);

    cout << "myid is " << myid << " receive count is " << recvCounts[myid]
         << " bytes" << endl;

    //发送数据相对于发送缓冲区起始位置的偏移量
    sdisp[0] = 0;
    for (int i = 1; i < numprocs; ++i) {
        sdisp[i] = sendCounts[i - 1] + sdisp[i - 1];
    }

    //接收的数据放在相对缓冲区中的起始位置的偏移量
    rdisp[0] = 0;
    for (int i = 1; i < numprocs; ++i) {
        rdisp[i] = recvCounts[i - 1] + rdisp[i - 1];
    }

    int ssize = 0;
    int rsize = 0;
    //初始化发送的数量和接收的数量
    for (int i = 0; i < numprocs; ++i) {
        ssize = ssize + sendCounts[i];
        rsize = rsize + recvCounts[i];
    }

    std::vector<int> recvvector;
    recvvector.resize(
        rsize);  //接收缓冲区的大小,因为每个节点要接收所有其他节点发过来的，所以要用发过来的总数量除以int的byte数
    MPI_Alltoallv(nums.data(), sendCounts, sdisp, MPI_INT, recvvector.data(),
                  recvCounts, rdisp, MPI_INT, MPI_COMM_WORLD);

    cout << "myid is " << myid << " receive element size is "
         << recvvector.size() << endl;

    for (int i = 0; i < recvvector.size(); ++i) {
        cout << "myid is " << myid << "  recvvector index i  is  " << i
             << " element is " << recvvector.at(i) << endl;
    }

    MPI_Finalize();
}
