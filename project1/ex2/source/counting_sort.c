#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

int n;

void CountingSort(int A[],int B[],int k)
{
    int i,C[k+1];
    for (i=0;i<=k;i++)
	{
        C[i]=0;
    }
    for (i=0;i<n;i++)
	{
        C[A[i]]=C[A[i]]+1;
    }
    for (i=1;i<=k; i++)
	{
        C[i]=C[i]+C[i-1];
    }
    for (i=n-1;i>=0;i--)
	{
        B[C[A[i]]-1]=A[i];
        C[A[i]]=C[A[i]]-1;
    }
}
//照书上写的 

int main()
{
    //clock_t start,finish;
	LARGE_INTEGER num;
	long long start,end,freq;
	double t;
	FILE *fp;
	int b,i;
	int *p;
	int *q;
	char filename[300];
    
	printf("input base x of the length(3^x)\n");
	scanf("%d",&b);
	n=pow(3,b);
	
	p=(int *)malloc(sizeof(int)*n); 
	q=(int *)malloc(sizeof(int)*n); 
    
	if((fp=fopen("D:\\code\\PB14011074-project1\\ex2\\input\\input_strings.txt", "r"))==NULL)
	{
        printf("error\n");
        exit(0);
    }
    
    sprintf(filename,"D:\\code\\PB14011074-project1\\ex2\\output\\counting_sort\\result_%d.txt",b);//这里只是为了懒得每一次运行之前改文件代码写的路径而已。。 

    for(i=0;i<n; i++)
	{
        fscanf(fp,"%d\n",&p[i]);
    }
	fclose(fp);//读文件
    
	//start=clock();//计时，调用clock函数 
	QueryPerformanceFrequency(&num);//调用winapi中的微秒级别计时，用于较小的数据量 
    freq=num.QuadPart;
    QueryPerformanceCounter(&num);
    start=num.QuadPart;
	
	CountingSort(p,q,65535);
    
    QueryPerformanceCounter(&num);
    end=num.QuadPart;
    t=(double)(end-start)/freq;
    
	//finish=clock();//计时结束 
	//t=(double)(finish-start)/CLK_TCK;
    
    
	if((fp=fopen(filename, "w"))==NULL)//写入rusult_i.txt中 
	{
		printf("error\n");
		exit(0);
	}
    for (i=0;i<n; i++)
	{
		fprintf(fp,"%d\n",q[i]);
    }
	fclose(fp);//写output文件 
    
	if((fp=fopen("D:\\code\\PB14011074-project1\\ex2\\output\\counting_sort\\time.txt", "a"))==NULL)//写入rusult_i.txt中 
	{
		printf("error\n");
		exit(0);
	}
	fprintf(fp, "Counting Sort at base %d takes %f seconds\n",b,t);
	fclose(fp);//写time文件 
    
	printf("Counting sort : %f seconds\n",t);
	return 0;
}
