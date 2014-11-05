#include<stdio.h>
#include <mpi.h>
#include<string.h>
int y[10] = {0,1,4,9,16,25,36,49,64,81};
int x[10] = {0,1,2,3,4,5,6,7,8,9};

float function(float x1,int n)
{
	int xi = x[n];
	float result = 1.0;int i;
	for(i=0;i<10;i++)
	{
		if((xi-x[i])!=0)
		result = result*((float)x1-(float)x[i])/((float)xi-(float)x[i]);
	}
	return result;
}

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

	float x1 = 3.5;
	static float sum=0;	
	if(rank!=0)
	{
		int k= 10/(size-1);
		int i;
		int j=k*(rank-1);
		//printf("rank= %d k=%d h= %f j= %d\n",rank,k,h,j);
		for(i=j;i<j+k;i++)
		{
			float l = function(x1,i);
			float f = (float)l*(float)y[i];
			sum+=f;
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

