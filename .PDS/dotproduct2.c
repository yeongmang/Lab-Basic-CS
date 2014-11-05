#include<stdio.h>
#include<mpi.h>

int product=0;
int pro(int a[],int b[], int low, int high)
{
	int sum=0,i;
	for( i=low;i<high;i++)
	{
		sum+=a[i]*b[i];
	}
	return sum;
}
	

int main( int argc, char *argv[] )
{
    int rank;
    int size,source,tag=0,dest;

	int sum=0;
static int i=0;
int x[10]={4,7,2,5,1,6,4,5,5,7};
int y[10]={1,1,1,1,1,1,1,1,1,1};

    MPI_Status status;
    MPI_Init( &argc, &argv );
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	static int global;
	int local=0;	
		if(rank!=0){
		local=pro(x,y,10/(size-1)*(rank-1),rank*10/(size-1));
		printf("%d\t",local);
		MPI_Reduce(&local,&global,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
		}
	else
	{
		
		printf("SUM= %d\n",global);
	}
		

	MPI_Finalize();
    return 0;
}
