#include<stdio.h>
#include<string.h>

int main()
{
        char inp[20],opt[20];
        int i;
        printf("Enter the encrypted text\n");
        scanf("%s",inp);
        int inv;
        int len = strlen(inp);
        for(i=0;i<26;i++)
        {
                if((7*i)%26==1)
                {
                        inv = i;
                        break;
                }
        }
        for(i=0;i<len;i++)
        {
                opt[i]=((inp[i]-97)*inv)%26;
                opt[i]=opt[i]+97;
        }
        opt[len]='\0';
        printf("Decrypted text = %s\n",opt);

        return 0;
}

