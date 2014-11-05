#include<stdio.h>
#include<mpi.h>
#include<string.h>

int arraySumProduct(int *arr1,int *arr2,int a ,int b)
{
	int i=0,result=0,product=0;
	for(i=a;i<=b;i++)
	{
		product = arr1[i]*arr2[i];
		result+= product;
	}
	return result;
	 
}
 
int main(int argc, char** argv) 
{
	int source=1,dest,num,rank,size,tag=0;
	int arr1[]={1,2,3,4,5,6,7,8,9,10};
	int arr2[]={1,2,3,4,5,6,7,8,9,10};
	MPI_Status status;
	static int sum;
	
	static int partial_sum=0;
  	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size); 
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		int h = 10/(size);
		int a = h*(rank);
		int b = a+h-1;
		partial_sum = arraySumProduct(arr1,arr2,a,b);
		printf("rank %d\t sum %d\n",rank,partial_sum);

		MPI_Reduce(&partial_sum,&sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);             
	if(rank==0)
		printf("\nresult: %d",sum);	
	
	MPI_Finalize();
	
	return 0;
}
