#include<stdio.h>
#include <mpi.h>
#include<string.h>
 
int main(int argc, char** argv) 
{
	int source,dest,tag=0;
	char msg[100];	
	MPI_Status status;

  // Initialize the MPI environment
  	MPI_Init(&argc,&argv);
 
  // Get the number of processes
  	int world_size;
  	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
 
  // Get the rank of the process
	  int world_rank;
  	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
 
	source=(world_rank +world_size -1)%world_size;
	dest=(world_rank +1)%world_size;

	sprintf(msg,"msg from %d ",world_rank);

	
	MPI_Send(msg,strlen(msg)+1,MPI_CHAR,dest,tag,MPI_COMM_WORLD);
		MPI_Recv(msg,100,MPI_CHAR,source,tag,MPI_COMM_WORLD,&status);
	printf("%s to rank %d\n",msg,world_rank);
		
	

	  MPI_Finalize();
	  return 0;
}
