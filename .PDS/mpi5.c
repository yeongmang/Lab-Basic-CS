#include<stdio.h>
#include <mpi.h>
#include<string.h>
int main(int argc, char** argv) 
{
  int rank,size,source,dest,tag=0;
  //char message[100],message2[100];
  MPI_Status status;
  
  // Initialize the MPI environment
  MPI_Init(&argc,&argv);
 
  // Get the number of processes
  //int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
 
  // Get the rank of the process
  //int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	float a=0;
	float b=1;
	
	static float sum=0;
	int n=1024;	
	if(rank!=0)
	{
	int k= n/(size-1);
	float h=(b-a)/n;
	int i;
	int j=k*(rank-1);
	printf("rank= %d k=%d h= %f j= %d\n",rank,k,h,j);
	for(i=0;i<k;i++)
	{
		float area=h*((a+(j+i)*h)*(a+(j+i)*h)+(a+(j+i+1)*h)*(a+(j+i+1)*h))/2;
		sum+=area;
	}
	MPI_Send(&sum,sizeof(sum),MPI_FLOAT,0,tag,MPI_COMM_WORLD);	
	}
 	
	else
  	{	
		float total_sum=0;
		for(source=1;source<size ;source++)
		{
			
			MPI_Recv(&sum,sizeof(float),MPI_FLOAT,source,tag,MPI_COMM_WORLD,&status);
			printf("Return %f \n",sum);
			total_sum+=sum;
		}	

		printf("Total sum = %f",total_sum);
	}
 
  	
  MPI_Finalize();
  return 0;
}

