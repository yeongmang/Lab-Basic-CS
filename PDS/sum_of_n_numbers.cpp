#include<stdio.h>
#include<stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[]){
    int my_rank,p,source,dest,tag=0;
    int i, arr[100];
    MPI_Init(&argc,&argv);
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    MPI_Comm_size(MPI_COMM_WORLD,&p);
    for(i=0;i<100;i++)
        arr[i] = i+1;
    if(my_rank != 0){
        dest = 0;
        MPI_Send(&arr[my_rank], 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
    }else{
        sum = arr[my_rank];
        for(i=0;i<100;i++){
            MPI_Recv(&val, 1, MPI_INT, i, tag, MPI_COMM_WORLD, &status);
            sum = sum + val;
        }
        printf("SUM OF ALL NUMBERS IS %d", sum);
    }
    MPI_Finalize();
}
