//trapezoidal rule
#include<stdio.h>
#include<string.h>
#include "mpi.h"

int array[201];
int dot(int local_a,int local_n)
{
 int integral=0;
 int i;
 for(i=local_a;i<=local_a+local_n-1;i++)
 {
	integral+=(array[i]*array[i+50]);
 }
 return integral;
}
int main(int argc, char **argv)
{
 int my_rank,p,tag=0,local_n,dest,source,x;
 int local_a,local_b,integral=0,total=0;

 MPI_Init(&argc,&argv);
 MPI_Status status;
 MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
 MPI_Comm_size(MPI_COMM_WORLD,&p);
 int i;
 for(i=0;i<100;i++)
 if(i<50)
 array[i] = 3;
 else
 if(i>=50)
 array[i] = 1;
 local_n=50/(p);
 local_a=my_rank*local_n;
 if(my_rank<p-1)
 integral=dot(local_a,local_n);
 else if(my_rank==p-1)
 integral=dot(local_a,50);
 if(my_rank!=0)
 {
  dest = 0;
  MPI_Send(&integral,1,MPI_INT,dest,tag,MPI_COMM_WORLD);
 }
 else
 {
  total=integral;
  for(source=1;source<p;source++)
  {
   MPI_Recv(&integral,1,MPI_INT,source,tag,MPI_COMM_WORLD,&status);
   total+=integral;
  }
  printf("\nThe DOT Product is = %d\n",total);
 }
 MPI_Finalize();
 return 0;
}
