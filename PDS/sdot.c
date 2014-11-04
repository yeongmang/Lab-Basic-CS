#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<mpi.h>

int x[4]={1,2,3,4};
int y[4]={4,3,2,1};

int p;
int s_dot(int a,int b)
{
	int i,k=0;;
	for(i=a;i<=b;i++)
	{
		k+=x[i]*y[i];
	}
	return k;
}
int main(int argc, char *argv[])
{
	int rank,size,tag=0,dest=0,source,a,b,temp_sum;
	MPI_Status status;
	int sum=0;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	p = 4/(size);
	a = rank*p;
	b = a + p-1 ;
	temp_sum = s_dot(a,b);

	MPI_Reduce(&temp_sum,&sum,4,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

	if(rank==0)
		printf("Sum is %d\n",sum);
	MPI_Finalize();
	return 0;
}
