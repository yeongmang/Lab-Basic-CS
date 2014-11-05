#include<stdio.h>
#include<mpi.h>
#include<string.h>

int arraySum(int *arr,int a ,int b)
{
	int i=0,result=0;
	for(i=a;i<=b;i++)
		result+= arr[i];

	return result;
	 
}
 
int main(int argc, char** argv) 
{
	int source=1,dest,num,rank,size,tag=0;
	int arr[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	MPI_Status status;
	static int sum;
	
	static int partial_sum=0;
  	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size); 
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		int h = 20/(size);
		int a = h*(rank);
		int b = a+h-1;
		partial_sum = arraySum(arr,a,b);
		printf("rank %d\t sum %d\n",rank,partial_sum);
		dest =0;
		MPI_Reduce(&partial_sum,&sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);             
	if(rank==0)
		printf("\nresult: %d",sum);	
	
	MPI_Finalize();
	
	return 0;
}
