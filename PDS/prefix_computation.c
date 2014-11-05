#include<stdio.h>
#include<stdlib.h>
#include"mpi.h"

int main(int argc,char ** argv)
{
	int my_rank,p,source,dest,tag=0;
	MPI_Status status;
	
	int n=8,local_sum,recv_sum,sum,i,j;
	int num[8]={1,2,3,4,5,6,7,8};

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&p);

	local_sum=num[my_rank];

	for(i=1;i<=3;i++)
	{
		for(j=0;j<p-i;j++)
		{
			if(my_rank==j)
			{
				dest=my_rank+(1<<(i-1));
				MPI_Send(&local_sum,1,MPI_INT,dest,tag,MPI_COMM_WORLD);
			}
		}

		for(j=i;j<p;j++)
		{
			if(my_rank==j)
			{
				MPI_Recv(&recv_sum,1,MPI_INT,(j-(1<<(i-1))),tag,MPI_COMM_WORLD,&status);
				local_sum=local_sum+recv_sum;
			}
		}

	}
	printf("prefix sum at processor %d is %d\n",my_rank,local_sum);
	MPI_Finalize();

	return 0;
}
