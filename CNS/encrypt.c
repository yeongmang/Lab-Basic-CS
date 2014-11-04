#include<stdio.h>
#include<string.h>
int main()
{

        char inp[20],opt[20];
        int i,k1,k2;
        printf("Enter the plain text\n");

        scanf("%d%d",&k1,&k2);
        scanf("%s",inp);

printf("\n%s\n",inp);
printf("k1=%d, k2=%d",k1,k2);
        printf("Enter the encryption keys \n");
        printf("Plain text = %s\n",inp);

        int len= strlen(inp);
        for(i=0;i<len;i++)
        {
                if(inp[i]>=97)
                {
                        opt[i]=(k1*(inp[i]-97)+k2)%26;
                        opt[i]=opt[i]+97;
                }
                if(inp[i]<=90)
                {
                        opt[i]=(k1*(inp[i]-65)+k2)%26;
                        opt[i]=opt[i]+65;
                }
        }
        opt[i]='\0';
        printf("Encrypted Output = %s\n",opt);
        int inv;
        for(i=0;i<26;i++)
        {
                if((k1*i)%26==1)
                {
                        inv = i;
                        break;
                }
        }
        for(i=0;i<len;i++)
        {
                if(opt[i]>=97)
                {
                        opt[i]=((opt[i]-97-k2)*inv)%26;
                        if(opt[i]>0)
                                opt[i]+=97;
                        else
                                opt[i]+=123;
                }
                if(opt[i]<=90)
                {
                        opt[i]=((opt[i]-65-k2)*inv)%26;
                        if(opt[i]>0)
                                opt[i]+=65;
                        else
                                opt[i]+=91;
                }
        }
        printf("Deciphered text = %s\n",opt);
        return 0;
}

