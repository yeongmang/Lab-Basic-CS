#include<stdio.h>

int main()
{
        int g,p,x,y,i;
        printf("Enter the value of g,p,x,y\n");
        scanf("%d%d%d%d",&g,&p,&x,&y);
        int gx = 1,gy =1;
        for(i=0;i<x;i++)
                gx = (gx*g)%p;
        for(i=0;i<y;i++)
                gy = (gy*g)%p;
        int r1 = gx%p;
        int r2 = gy%p;
        int k = (r1*r2)%p;
        int f =1;
        for(i=0;i<x;i++)
        {
                f = (f*r2)%p;
        }
        printf("Final message = %d\n",f);
        int gxy =1;
        for(i=0;i<x*y;i++)
                gxy =(gxy*g)%p;
        int k_diff = gxy%p;
        printf("r1 = %d\tr2 = %d\n",r1,r2);
        printf("Exchanged key = %d\n",k);
        printf("Original key = %d\n",k_diff);
        return 0;
}

