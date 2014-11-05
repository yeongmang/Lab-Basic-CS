#include<stdio.h>
#include<string.h>
#include "mpi.h"
float X[] = {1.0,2.0,3.0};
float Y[] = {1.0,8.0,27.0};
float x;
float calc(int p)
{
	int i;
	float den=1.0,num=1.0;
	for(i=0;i<3;i++)
	{
		if(i!=p)
		{
			den*=(X[p]-X[i]);
			num*=(x-X[i]);
		}
	}
	return num/den;
}
	
int main(int argc,char **argv)
{
//41
//29.56
	int p,dest,source,tag=0,my_rank;
	
	int i;
	float total=0.0,val;

	x= 3.1;
	
	MPI_Init(&argc,&argv);
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&p);
	val=calc(my_rank);
	if(my_rank!=0)
	{	
		MPI_Send(&val,1,MPI_FLOAT,0,tag,MPI_COMM_WORLD);
	}
	else
	{
		total=val*Y[0];
		printf("val  0   :  %f\n",val);		
		for(source=1;source<p;source++)
		{
			MPI_Recv(&val,1,MPI_FLOAT,source,tag,MPI_COMM_WORLD,&status);
			printf("val %d  :  %f\n",source,val);
			total+=(val*Y[source]);
		}
		printf("The value of Interpolation of xcube at %f is  :   %f\n",x,total);
	}	
	MPI_Finalize();

}

