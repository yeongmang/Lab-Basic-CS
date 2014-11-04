#include<stdio.h>
#include<string.h>
int main()
{
        char inp[20],opt[20];
        char k[7]={'p','a','s','c','a','l'};
        printf("Enter the plain text\n");
        scanf("%s",inp);
        int i,j;
        for(i=0;i<strlen(inp);i++)
        {
                opt[i]=((inp[i]-97)+(k[i%6]-97))%26;
                opt[i]+=97;
        }
        for(j=0;j<strlen(inp);j++)
                printf("%c",opt[j]);

        for(i=0;i<strlen(inp);i++)
        {
                inp[i]=((opt[i]-97)-(k[i%6]-97))%26;
                if(inp[i]<0)
                        inp[i]+=123;
                else
                        inp[i]+=97;
        }
        printf("\n");
        for(j=0;j<strlen(inp);j++)
                printf("%c",inp[j]);
        printf("\n");
        return 0;
}

