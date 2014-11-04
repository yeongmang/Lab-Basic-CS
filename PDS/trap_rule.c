#include <stdio.h>
#include "mpi.h"



float f(float x){ return x; }

float Trap(float a, float b, int n, float h){ 
    float integral, x;
    int i; 
    integral = (f(a) + f(b))/2.0; 
    x = a; 
    for (i = 1; i <= n-1; i++) { 
        x += h; 
        integral += f(x); } 
    return integral * h;
}

int main(int argc, char** argv)
 {
  int me, nproc, n = 10240, src, dst = 0, tag = 50;  
  float a = 1.0, b = 6.0, h, local_a, local_b, local_n;   
  float integral, total;     
  MPI_Status sts;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &me);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);

  h = (b-a)/n;  
 
  local_n = n/nproc; 
  local_a = a + me*local_n*h;
  local_b = local_a + local_n*h;
  integral = Trap(local_a, local_b, local_n, h);
 
  if(me == 0)
 {
    total = integral;
    for (src = 1; src < nproc; src++)
    {
      MPI_Recv(&integral,1,MPI_FLOAT,src,tag,MPI_COMM_WORLD,&sts);
      total += integral;
    }
  } 
  else
  {   
    MPI_Send(&integral,1,MPI_FLOAT,dst,tag,MPI_COMM_WORLD);
  }
  if(me == 0) 
 {
    printf("With n = %d trapezoids\n", n);
    printf("The integral from %f to %f is approx %f\n", 
           a, b, total); 
  }
  MPI_Finalize();
  return 0;
}
