#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<mpi.h>

int p,counter;
int main(int argc, char *argv[])
{
	int rank,size,tag=0,dest=0,source;
	MPI_Status status;
	int sum;
	
	int arr[8]={1,2,3,4,5,6,7,8};
	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	p = 8/(size-1);

	if(rank!=0)
	{
		//for(counter=1;counter<size;counter++)
		//{
			int i;
				sum=0;
			for(i=(rank-1)*p;i<(rank*p);i++)
				sum +=arr[i];
			printf("sum of processor %d = %d\n",rank,sum);
			MPI_Send(&sum,1,MPI_INT,0,tag,MPI_COMM_WORLD);	
		//}
	}
	else
	{
		int final =0;
		for(source=1;source<size;source++)
		{
			MPI_Recv(&sum,1,MPI_INT,source,tag,MPI_COMM_WORLD,&status);
			final +=sum;
		}
		printf("Sum =  %d\n",final);
	}
	
	MPI_Finalize();
	return 0;
}
