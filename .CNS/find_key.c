#include<stdio.h>
#include<string.h>

int main()
{
        int hash[30]={0};
        char inp[400],opt[400];
        printf("Enter the Cipher text\n");
        scanf("%s",inp);
        int len = strlen(inp);
        int i;
        printf("len = %d\n",len);
        for(i=0;i<len;i++)
        {
                hash[inp[i]-65]=hash[inp[i]-65]+1;
        }
        int max=-101,max_idx=0;
        for(i=0;i<26;i++)
        {
                if(hash[i]>max)
                {
                        max=hash[i];
                        max_idx=i;
                }
        }
        int k = max_idx -4;
        printf("key = %d\n",k);
        printf("max_idx =%d\n",k);
        for(i=0;i<len;i++)
        {
                opt[i]=(inp[i]-65-k)%26;
                if(opt[i]>0)
                        opt[i]+=65;
                else
                        opt[i]+=91;
        }
        opt[len]='\0';
        printf("Deciphered code = %s\n",opt);
        return 0;
}

