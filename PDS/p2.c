#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<string.h>
int main(int argc, char *argv[])
{
	MPI_Status status;
	int rank,size,tag=0,dest,source;
	MPI_Init(&argc,&argv);
	char message[100];
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	//printf("%d ",rank);
	if(rank!=0)
	{
		sprintf(message,"Greetings for process %d\n",rank);
		//printf("rank is %d\n",rank);
		dest=0;
		MPI_Send(message,strlen(message)+1,MPI_CHAR,dest,tag,MPI_COMM_WORLD);			
	}
	else
	{
		for(source=1;source<size;source++)
		{
			MPI_Recv(message,100,MPI_CHAR,source,tag,MPI_COMM_WORLD,&status);
			printf("%s",message);		
		}
	}
	MPI_Finalize();
	return 0;
}
