#include<stdio.h>
#include<mpi.h>
#include<string.h>
 
int main(int argc, char** argv) 
{
	int source=1,dest,num,rank,size,tag=0;
	int arr[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	MPI_Status status;
	static int sum,i;
	
	static int partial_sum=0;
  	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size); 
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if(rank!=0)
	{
		partial_sum =0;
		for(i=0;i<5;i++)
		{
			partial_sum =partial_sum + arr[5*(rank -1) +i];
		}
		dest =0;
		MPI_Send(&partial_sum,sizeof(int),MPI_INT,dest,tag,MPI_COMM_WORLD);  
		printf("\n%d",partial_sum);             
			
	}
	else
	{
		int temp=0;
		for(source=1;source<size;source++)
		{
			
			MPI_Recv(&partial_sum,sizeof(int),MPI_INT,source,tag,MPI_COMM_WORLD,&status);
			temp=temp+ partial_sum;
		
		}
		printf("\nresult: %d",temp);	
	}
	
	MPI_Finalize();
	
	return 0;
}
