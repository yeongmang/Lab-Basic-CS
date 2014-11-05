#include<stdio.h>
#include <mpi.h>
#include<string.h>
 
int main(int argc, char** argv) 
{
	int tag=0,dest=0,source,size,rank,sum=0,total=0;
    int x[3]={2,4,8};
    int y[3]={8,4,2};
	
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 
    if(rank!=0)  
	{
	    sum=x[rank]*y[rank];
        //printf("sum is %d\n",sum);
	    dest=0;
	    MPI_Send(&sum,1,MPI_INT,dest,tag,MPI_COMM_WORLD);
    }
    else 
    {
        total=x[rank]*y[rank];
 	    for(source=1;source<size;source++) 
        {
		    MPI_Recv(&sum,1,MPI_INT,source,tag,MPI_COMM_WORLD,&status);
            total+=sum;
 		    //printf("%d to %d\n",message,rank);
 		}
    printf("Total sum is %d\n",total);
	}
    MPI_Finalize();
    return 0;
}
