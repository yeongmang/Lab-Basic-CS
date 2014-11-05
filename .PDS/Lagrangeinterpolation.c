//Lagrange interpolation

#include<stdio.h>
#include<mpi.h>
#include<string.h>
#include<stdlib.h>
//float fun(float x)
//{
//	return x*x;
//}
int main(int argc, char** argv) 
{
	MPI_Init(&argc,&argv);
	int size;
        MPI_Comm_size(MPI_COMM_WORLD, &size);
  	int rank;
  	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
	int source, tag = 0, destination;

	
	MPI_Status status;

	float X[]={0,1,3,4,7};
	float f[]={1,3,49,129,813};
	int n=5;
	int root=0;
	float sendbuf,recvbuf,x=0.3;
	int k;
	sendbuf=0.0;
	float num=1.0,den=1.0;
	if(rank!=0)
	{
		for(k=0;k<n;k++)
	{
		if(k!=(rank-1))
		{
			num*=(x-X[k]);
			den*=(X[rank-1]-X[k]);
		}
	}

		sendbuf=(num/den)*(f[rank-1]);
		printf("\nLocal sum %d =>%f",rank,sendbuf);
	}

	MPI_Reduce(&sendbuf,&recvbuf,1,MPI_FLOAT,MPI_SUM,root,MPI_COMM_WORLD);
	if(rank==0)
	{
		printf("\nAnswer: %f\n",recvbuf);

	}
	

	MPI_Finalize();
  	return 0;
}
