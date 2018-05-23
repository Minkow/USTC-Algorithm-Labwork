#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

int in(int *a,int n,int t)
{
    int i;
    for(i=0;i<t;++i)
        if(a[i]==n)
            return 1;
 
    return 0;
}

int main()
{
    FILE*fp;
    int i,n,num;
    int *p;
    scanf("%d",&n);
    p=(int*)malloc(sizeof(int)*n);
    for(i=0;i<n;)
    {
    	num=1+rand()%150;
    	if(in(p,num,n))
    		continue;
    	p[i]=num;
    	i++;
	}
	
	
    if ((fp=fopen("input.txt", "w"))==NULL)
	{
        exit(0);
    }
    srand((unsigned) time(NULL));
    for(i=0;i<n;i++)
	{
        fprintf(fp,"%d\n",p[i]);
    }
    fclose(fp);
    printf("success\n");
    return 0;
}
