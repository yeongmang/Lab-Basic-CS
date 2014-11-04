#include<stdio.h>


int main()
{
        int p,e1,e2,d,m,r;
        int pow_e = 1,i;
        while(1)
        {
                printf("Enter a prime number primitive root and public key\n");
                scanf("%d%d%d",&p,&e1,&d);
                int chk_p=0;
                for(i=2;i*i<p;i++)
                {
                        if(p%i==0)
                        {
                                chk_p =1;
                                break;
                        }
                }
                if(chk_p ==0)
                        break;

        }

        printf("Example for 8 phi = %d\n",phi(8));
        for(i=0;i<d;i++)
                pow_e = (pow_e*e1)%p;
        e2 = pow_e%p;
        printf("e2 = %d\n",e2);
        printf("Enter the value of r and m\n");
        scanf("%d%d",&r,&m);

        pow_e=1;
        for(i=0;i<r;i++)
                pow_e = (pow_e * e1)%p;
        int c1 = pow_e%p;
        pow_e=1;
        for(i=0;i<r;i++)
                pow_e = (pow_e * e2)%p;
        int c2 = (m*pow_e)%p;
        printf("c1 = %d\nc2 = %d\n",c1,c2);

        int pow_c = 1;
        for(i=0;i<d;i++)
                pow_c = (pow_c*c1)%p;

        int c1_inv = 0;
        for(i=1;i<p;i++)
        {
                if((pow_c*i)%p == 1)
                {
                        c1_inv = i;
                        break;
                }
        }
        int final_msg = (c2*c1_inv)%p;
        printf("Final message = %d\n",final_msg);
        return 0;
}

