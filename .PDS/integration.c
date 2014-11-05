#include <stdio.h>
#include <mpi.h>
#include<string.h>
#include<stdlib.h>
float integral=0.0;

float f(float a){

	return a*a;
}

int main( int argc, char *argv[] )
{
    	int rank;
   	int size,tag=0,dest=0;
	
	int source;

	float total=0.0;
	float local_a;
	float local_b;
    MPI_Status status;
    MPI_Init( &argc, &argv );
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
	int a=2,b=3;
	float h=(float)(b-a)/100;
//	printf("%f",h);
	
	  local_a=2+(rank)*h;
	 local_b=2+rank*h+h;
	printf("local_a=%f local_b=%f\n",local_a,local_b);
	

if(rank!=0){
	
	integral=h*(f(local_a)+f(local_b))/2;
	
	printf("%f\n",integral);
	MPI_Send(&integral,sizeof(float),MPI_FLOAT,0,tag,MPI_COMM_WORLD);
}

else{
	
	total=integral;
	
	for(source=1;source<size;source++){
		MPI_Recv(&integral,sizeof(float),MPI_FLOAT,source,tag,MPI_COMM_WORLD,&status);
//		printf("%f\n",integral);	
		total=integral+total;
	}
printf("%f",total);
}
 MPI_Finalize();
    return 0;

}
