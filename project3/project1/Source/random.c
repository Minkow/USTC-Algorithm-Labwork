#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    FILE*fp;
    int i,n,num;
    int *p;
    scanf("%d",&n);
    p=(int*)malloc(sizeof(int)*n);
    srand((unsigned) time(NULL));
    for(i=0;i<n;)
    {
    	num=1+rand()%50;
    	p[i]=num;
    	i++;
	}
		
    if((fp=fopen("input1.txt", "w"))==NULL)
	{
        exit(0);
    }
    for(i=0;i<n;i++)
	{
        fprintf(fp,"%d\n",p[i]);
    }
    fclose(fp);
    printf("success\n");
    return 0;
}
