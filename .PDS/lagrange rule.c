#include<stdio.h>
#include<mpi.h>
#include<string.h>
//int sum_dot(int*,int*,int,int);

float x[3]={4,2,3};//3,4,4,8,3,2,2,1,6,5,3,1,2};
float y[3]={4,2,3};//8,9,2,3,4,5,2,3,9,9,9,7,6};

float X=2.5,Y;

float fun(int i)
{
   float p=1;int j;
for(j=0;j<3;j++)
{
   if(i!=j)
   p*=((X-x[j])/(x[i]-x[j]));
}
   //printf("%f\n",p);
   return p;
}

float sum_dot(int a,int b)
{
	int i;float sum=0;
	for(i=a;i<b;i++)
	
		sum+=(fun(i)*y[i]);
       // printf("%f\n",sum);
	return sum;
}

int main(int argc,char** argv)
{
	int tag=0,dest=0,source,size,rank;
        float sum=0,total=0;
	int a,b,h,i;float temp_sum;
	
	
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	h=3/size;
	a=(rank)*h;
	b=a+h;
	temp_sum=sum_dot(a,b);
        printf("%f\n",temp_sum);
	MPI_Reduce(&temp_sum,&total,1,MPI_FLOAT,MPI_SUM,0.0,MPI_COMM_WORLD);
	if(rank==0)
	{
		printf("total sum=%f\n",total);
	}	
	MPI_Finalize();
	return 0;
	
}

