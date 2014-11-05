#include<stdio.h>
#include<stdlib.h>
#include"mpi.h"
int a[8] = {1,1,1,1,1,1,1,1};
int b[8] = {0,0,0,0,0,0,0,0};
int mask[8]={0,1,0,1,0,1,0,1};
int shuffle(int a)
{
	int temp=a&(1<<2);
	a=((a<<1)%8) | (temp?1:0);
	return a;	
}

int unshuffle(int a)
{
	int temp = a&1;
	a= (a>>1)|(temp<<2);
	return a;
}
int exchange(int a)
{
	if(a&1)
	{
		return a-1;
	}
	return a+1;
}

int main(int argc,char **argv)
{
	int my_rank,p,source,dest,tag=0;

	
	int local_sum,recv_sum,sum,i,j;


	MPI_Init(&argc,&argv);
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&p);
	int x;
        int t;
	int y=2;
	for(i=0;i<3;i++)
	{
		for(j=0;j<8;j++)
		{
			if(my_rank==j && my_rank!=0 && my_rank!=7)
			{
				if(mask[my_rank])
				a[my_rank]*=y;
				dest=shuffle(my_rank);
                              
				t=mask[my_rank];
				MPI_Send(&t,1,MPI_INT,dest,tag,MPI_COMM_WORLD);
			}
			else if(my_rank==7)
			{
				a[my_rank]=128;
			}
		}
		
		for(j=0;j<8;j++)
		{
			if(my_rank==j && my_rank!=0 && my_rank!=7)
			{
				source = unshuffle(my_rank);
				MPI_Recv(&x,1,MPI_INT,source,tag,MPI_COMM_WORLD,&status);
				mask[my_rank]=x;
			}
		}
		y*=y;
	}
	printf("value in proc %d  :  %d\n", my_rank, a[my_rank]);
	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 8; j++)
		{
			if(my_rank==j && my_rank != 0 && my_rank != 7)
			{
				dest=shuffle(my_rank);
                              
				t=a[my_rank];
				MPI_Send(&t,1,MPI_INT,dest,tag,MPI_COMM_WORLD);
			}
		}
		
		for(j=0;j<8;j++)
		{
			if(my_rank==j && my_rank!=0 && my_rank!=7)
			{
				source = unshuffle(my_rank);
				MPI_Recv(&x,1,MPI_INT,source,tag,MPI_COMM_WORLD,&status);
				b[my_rank]=x;
			}
		}
                if(my_rank==0 || my_rank==7)
		{
                        b[my_rank]=a[my_rank];
		}

		for(j=0;j<8;j++)
		{
			if(my_rank==j)
			{
				a[my_rank]=b[my_rank];
				dest=exchange(my_rank);
				MPI_Send(&b[my_rank],1,MPI_INT,dest,tag,MPI_COMM_WORLD);
			}
		}
      		
		for(j=0;j<8;j++)
		{
			if(my_rank==j)
			{
				source=exchange(my_rank);
				MPI_Recv(&x,1,MPI_INT,source,tag,MPI_COMM_WORLD,&status);
				b[my_rank]=x;
				a[my_rank]+=b[my_rank];
			}		
		}
	}

	MPI_Finalize();

	printf("Sum in proc %d   :   %d\n",my_rank,a[my_rank]);
	return 0;
}
