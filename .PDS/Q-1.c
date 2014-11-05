#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mpi.h"

main(int argc, char *argv[])
{
int my_rank,p,source,dest,tag=0;
char message[100];
MPI_Status status;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
MPI_Comm_size(MPI_COMM_WORLD,&p);

sprintf(message,"Greeting, From Process %d!",my_rank);
dest=(my_rank+1)%p;
MPI_Send(message,strlen(message)+1,MPI_CHAR,dest,tag,MPI_COMM_WORLD);

if(my_rank!=0){
    MPI_Recv(message,100,MPI_CHAR,(my_rank-1)%p,tag,MPI_COMM_WORLD,&status);
    printf("I am processor %d and message received is %s\n",my_rank,message);
}else{
    MPI_Recv(message,100,MPI_CHAR,p-1,tag,MPI_COMM_WORLD,&status);
    printf("I am processor %d and message received is %s\n",my_rank,message);
}

MPI_Finalize();
}
