#include<stdio.h>

int chk_fun(int a)
{
        return (2*a);
}
int main()
{
        int a=5,count =1;
        while(1)
        {
                if(a%11==1)
                {
                        printf("a = %d\n",a);
                        printf("count = %d\n",count);
                        printf("a/11 = %d\n",a/11);
                        break;
                }
                else
                {
                        a = a*5;
                        count++;
                }
        }
        return 0;
}

