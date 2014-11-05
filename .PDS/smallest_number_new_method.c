#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int findmin(int arr[],int start, int n){
	int i,min=arr[start];
	for(i=start+1;i<start+n;i++){
		if(arr[i]<min){
			min=arr[i];
		}
	}
	return min;
}	

int main(int argc,char **argv){
	int my_rank,p,source,dest,tag=0;

	int n=10,local_n,min,local_min,start,local_start;
	int num[15]={12,43,54,23,14,54,76,34,15,40};

	MPI_Init(&argc,&argv);
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&p);

	local_n=n/p;		
	local_start=my_rank*local_n;
	local_min=findmin(num,local_start,local_n);

	if(my_rank==0)
	{
		min=local_min;
		for(source=1;source<p;source++)
		{
			MPI_Recv(&local_min,1,MPI_INT,source,tag,MPI_COMM_WORLD,&status);
			if(local_min<min)
			{
				min = local_min;
			}
		}
		printf("Minimum value=%d\n",min);
	}
	else
	{
		MPI_Send(&local_min,1,MPI_INT,0,tag,MPI_COMM_WORLD);
	}

	MPI_Finalize();

	return 0;
}
