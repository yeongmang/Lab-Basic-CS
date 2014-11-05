#include<stdio.h>
#include<stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[]){
    int my_rank,p,source,dest,tag = 0, val, small;
    int i, arr[4] = {3, 2, 1, 4};
    MPI_Init(&argc,&argv);
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    MPI_Comm_size(MPI_COMM_WORLD,&p);
    if(my_rank == 3){
        dest = my_rank - 1;
        MPI_Send(&arr[my_rank], 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
    }
    if(my_rank != 3 && my_rank != 0){
        source = my_rank + 1;
        dest = my_rank - 1;
        MPI_Recv(&val, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
        small = val<arr[my_rank]?val:my_rank;
        MPI_Send(&small, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
    }
    if(my_rank == 0){
        source = my_rank + 1;
        MPI_Recv(&val, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
        small = val<arr[my_rank]?val:my_rank;
        printf("Smallest value is %d", small);
    }
    MPI_Finalize();
}
