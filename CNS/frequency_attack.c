#include<stdio.h>
#include<string.h>

int main()
{
        char inp[10],opt[10];
        printf("Enter the encrypted code\n");
        scanf("%s",inp);
        int i;
        for(i=0;i<strlen(inp);i++)
        {
                int alpha = inp[i]-97;
                printf("alpha = %d\n",alpha);
                int k = alpha - 4;
                if(k<0)
                        k+=26;
                printf("k = %d\n",k);

                int j ;
                for(j=0;j<strlen(inp);j++)
                {
                        opt[j]=(inp[j]-97-k)%26;
                        if(opt[j]<0)
                                opt[j]+=123;
                        else
                                opt[j]+=97;
                }
        int m;
        printf("for i = %d\n",i);
        for(m=0;m<strlen(inp);m++)
                printf("%c",opt[m]);
        printf("\n");
        }
        return 0;
}

