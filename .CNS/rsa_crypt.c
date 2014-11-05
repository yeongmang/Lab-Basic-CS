#include<stdio.h>

int gcd(int a, int b)
{
        int r;
        printf("gcd of %d and %d is \n");
        while(r)
        {
                r =a;
                a = b%a;
                b = r;
        }
        printf("%d\n",b);
        return b;
}
int main()
{
        int p,q,e;
        printf("Enter the prime numbers\n");
        scanf("%d%d",&p,&q);
        p--;
        q--;
        printf("p = %d q= %d\n",p,q);
        int phi = p*q;
        int mod = (p+1)*(q+1);
        printf("phi = %d\n",phi);
        printf("Different values possible for e are:\n");
        int i=1;
        for(i=1;i<phi;i++)
        {
                int c,a=i,b=phi;
                while(a!=0)
                {
                        c =a ;
                        a = b%a;
                        b = c;
                }
                if(b==1)
                        printf("%d \n",i);
        }
        int C,M;
        printf("Enter the value of M\n");
        scanf("%d",&M);
        printf("M= %d\n",M);
        int tot =1;
        e =13;
        for(i=0;i<e;i++)
        {
                tot =( tot * M)%mod;
                printf("tot = %d\n",tot);
        }
        C = tot%mod;
        if(C<0)
         C +=phi;
        printf("Cipher number = %d\n",C);
        for(i=1;i<phi;i++)
        {
                if((i*e)%phi ==1)
                {
                        printf("d = %d\n",i);
                }
        }

        return 0;
}

