#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

int n; 

int digit(int n,int k)
{
    int i;
    for(i=1;i<k;i++)
        n/=10;
    return n%10;
}
//获取数n第k位的值 

void Sort(int A[],int n,int d)
//计数排序作为稳定排序算法 
{
    int i;
	int B[10]={0};
	int *p=(int *)malloc(sizeof(int)*n);
    int *q=(int *)malloc(sizeof(int)*n);
    
    for(i=0;i<n;i++)
	{  
        p[i]=digit(A[i],d);  
        B[p[i]]++;  
    }  
    //数组p保存数组中各个数的第d位 
    
	for(i=1;i<10;i++)
	{  
        B[i]=B[i]+B[i-1];
	}  
  
    for(i=n-1;i>=0;i--)
	{  
        q[B[p[i]]-1]=A[i];  
        B[p[i]]--;  
    }  
  
    for(i=0;i<n;i++)
	{  
        A[i]=q[i];  
    }  
}  
//就是书上的counting sort 

void RadixSort(int A[],int n)
{
    int i;
    for(i=0;i<6;i++)
	{  
        Sort(A,n,i);
    }  
}  

int main()
{
    //clock_t start,finish;
    LARGE_INTEGER num;
    long long start,end,freq;
    double t;
    FILE *fp;
    int b,i;
    int *p;
    char filename[300];
    
    printf("input base x of the length(3^x)\n");
    scanf("%d",&b);
    n=pow(3,b);
    
    p=(int *)malloc(sizeof(int)*n); 
    
    if((fp=fopen("D:\\code\\PB14011074-project1\\ex2\\input\\input_strings.txt", "r"))==NULL)
	{
        printf("error\n");
        exit(0);
    }
    
    sprintf(filename,"D:\\code\\PB14011074-project1\\ex2\\output\\radix_sort\\result_%d.txt",b);//这里只是为了懒得每一次运行之前改文件代码写的路径而已。。 

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
    
    RadixSort(p,n);
        
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
        fprintf(fp,"%d\n",p[i]);
    }
    fclose(fp);//写output文件 
    
    if((fp=fopen("D:\\code\\PB14011074-project1\\ex2\\output\\Radix_sort\\time.txt", "a"))==NULL)//写入rusult_i.txt中 
	{
        printf("error\n");
        exit(0);
    }
    fprintf(fp, "Radix Sort at base %d takes %f seconds\n",b,t);
    fclose(fp);//写time文件 
    
    printf("Radix sort : %f seconds\n",t);
    return 0;
}
