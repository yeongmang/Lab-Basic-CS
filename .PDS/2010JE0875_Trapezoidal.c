//trapezoidal rule
#include<stdio.h>
#include<string.h>
#include "mpi.h"
float f(float x)
{
	return x*x;
}
float trap(float local_a,float local_b,int local_n,float h)
{
 float integral,x;
 int i;
 integral=(f(local_a)+f(local_b))/2.0;
 for(i=1;i<=local_n-1;i++)
 {
	x+=h;
	integral+=f(x);
 }
 integral=integral*h;
 return integral;
 
}
int main(int argc, char **argv)
{
 int my_rank,p, source, dest, tag=0,n=10,local_n;
 float a=0.0,b=1.0,h,local_a,local_b,integral,total;
 MPI_Status status;
 MPI_Init(&argc,&argv);
 MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
 MPI_Comm_size(MPI_COMM_WORLD,&p);
 h=(b-a)/n;
 local_n=n/p;
 local_a=a+my_rank*local_n*h;
 local_b=local_a+local_n*h;
 integral=trap(local_a,local_b,local_n,h);
printf("n=%d\na=%f\nb=%f\n\nintegral=%f",local_n,local_a,local_b,integral);
 if(my_rank!=0)
 {
  MPI_Send(&integral,1,MPI_FLOAT,dest,tag,MPI_COMM_WORLD);
 }
 else
 {
  total=integral;
  for(source=1;source<p;source++)
  {
   MPI_Recv(&integral,1,MPI_FLOAT,source,tag,MPI_COMM_WORLD,&status);
   total+=integral;
  }
 }
 if(my_rank==0)
 {
 	printf("\nWith n=%d trapezoids,our estimate of integral from %f to %f",n,a,b,total);
 }

 MPI_Finalize();
}
