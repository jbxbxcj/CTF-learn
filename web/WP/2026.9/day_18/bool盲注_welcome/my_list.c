#include <stdio.h>

int main(void)
{
    FILE *fp = fopen("single_password.txt","w");
    if (fp==NULL)
    {
        printf("打开失败！");
        return 0;
    }

    for (int i=0;i<=9;i++)
    {
        fprintf(fp,"%d\n",i);
    }
    for (char i='a';i<='z';i++)
    {
        fprintf(fp,"%c\n",i);
    }
    

    printf("process end");
    return 0;
}