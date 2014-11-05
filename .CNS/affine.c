#include<stdio.h>
#include<string.h>

int main()
{
        char inp[20],opt[20];
        int i =0,a=0;
        for(i=0;i<26;i++)
        {
                if((i*21)%26==1)
                {
                        a = i;
                        printf("%d\n",a);
                }
        }
        printf("ä = %d\n",a);

        return 0;
}

