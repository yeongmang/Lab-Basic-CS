#include<stdio.h>
#include <mpi.h>
#include<string.h> 
int main(int argc, char* argv[]) 
{
  // Initialize the MPI environment
	int rank,size,tag=0;
	char message[100];	
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
 
  // Print off a hello world message
 	sprintf(message,"Greetings for process %d",rank);
	MPI_Send(message,strlen(message)+1,MPI_CHAR,(rank+1)%size,tag,MPI_COMM_WORLD);
	MPI_Recv(message,100,MPI_CHAR,((rank-1)%size+size)%size,tag,MPI_COMM_WORLD,&status);
	printf("%s for %d\n",message,rank);

	MPI_Finalize();
	return 0;
}
