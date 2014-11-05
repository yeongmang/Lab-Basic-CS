#include<stdio.h>
#include<mpi.h>

int product=0;


int main( int argc, char *argv[] )
{
    int rank;
    int size,source,tag=0,dest;

	int sum=0;
static int i=0;
int x[6]={2,3,4,5,6,2};
int y[6]={4,3,2,5,2,13};

    MPI_Status status;
    MPI_Init( &argc, &argv );
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	

	if(rank!=0)
	{
		product= x[rank-1]*y[rank-1];
       		
	MPI_Send(&product,sizeof(int),MPI_INT,0,tag,MPI_COMM_WORLD);
	
	}
	else
	{
		for(source=size-1;source>0;source--)
		{
                MPI_Recv(&product,sizeof(int),MPI_INT,source,tag,MPI_COMM_WORLD,&status); 
		
		sum+=product;
		}
		printf("SUM= %d\n",sum);
	}
                


    MPI_Finalize();
    return 0;
}
