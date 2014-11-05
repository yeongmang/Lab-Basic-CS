# include<stdio.h>
# include<stdlib.h>
# include"mpi.h"


float fun(float x)
{
    return x*x;
}

int main(int argc,char **argv)
{
    int my_rank,p,source,dest,tag=0,i;
    int a,b;
   // printf("Enter the value of a and b(a<b)\n");
 //   scanf("%d %d",&a,&b);
    a=0;
    b=2;
    float h,integral=0.0;
       
    MPI_Init(&argc,&argv);
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    MPI_Comm_size(MPI_COMM_WORLD,&p);
    h=(float)(b-a)/(float)p;
    float f;
    f=fun(a+((float)my_rank*h));
    
    if(my_rank==0)
    {
        printf("a=%d  b=%d\n h=%f\n",a,b,h);
        integral=f+fun(b);
        for(i=1;i<p;i++)
        {
            source=i;
            MPI_Recv(&f,1,MPI_FLOAT,source,tag,MPI_COMM_WORLD,&status);
            integral+=f;
        }
        integral*=h/3;
        printf("The value of integration in %f\n",integral);
        
    }
    else
    {
        dest=0;
        if(my_rank % 2==0)
           f=f*2;
        else
           f=f*4;
        MPI_Send(&f,1,MPI_FLOAT,dest,tag,MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
    return 0;
}
    
    
    
    
