#include<stdio.h>
#include<stdlib.h>
#include"mpi.h"
int array[20];

int main(int argc, char **argv)
{
 int my_rank,p,tag=0,local_n,dest,source,x,j;
 int local_a,local_b,integral=0,total=0;

 MPI_Init(&argc,&argv);
 MPI_Status status;
 MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
 MPI_Comm_size(MPI_COMM_WORLD,&p);
 int i;
 for(i=0;i<16;i++)
 array[i] = i+1;
 int divisor = 2;
 int max_proc = 16;
for(j=0;j<4;j++)
{
  for(i=max_proc/2;i<max_proc;i++)
 {
   if(my_rank==i)
   {
     integral = array[i];
     MPI_Send(&integral,1,MPI_INT,(i-max_proc/2),tag,MPI_COMM_WORLD);
   }
 }

 max_proc/=2;
 
  for(i=0;i<max_proc;i++)
 {
    if(my_rank==i)
    {
      MPI_Recv(&integral,1,MPI_INT,i+max_proc,tag,MPI_COMM_WORLD,&status);
      array[i]+=integral;
    }
 }
}
if(my_rank==0)
 printf("The Sum is  :  %d\n",array[0]);
 MPI_Finalize();
 return 0;
}
