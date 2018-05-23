#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

int n;//全局变量，用做记录长度

int cmp(char *a,char *b)
{
    if(strlen(a)!=strlen(b)) 
    {
    	return strlen(a)-strlen(b);
	}
    else
	{
        return strcmp(a,b);
    }
}
//长度排序，调用了strcmp，考虑到编译器优化问题可能strcmp运行时间较短，但是影响不大
//此处返回值并不是1或者0而是正数或者负数 
 

void Merge(char A[][17],int p, int q, int r)
{
    int i,j,k;
    int n1=q-p+1;
    int n2=r-q;
    char L[n1+1][17],R[n2+1][17];
    for(i=0;i<n1; i++)
	{
        strcpy(L[i],A[p+i]);
    }
    for(j=0;j<n2;j++)
	{
        strcpy(R[j], A[q+j+1]);
    }
    strcpy(L[n1],"zzzzzzzzzzzzzzzz");//zzzzzzzzzzzzzzzz即为正无穷 
    strcpy(R[n2],"zzzzzzzzzzzzzzzz");
    i=0;
    j=0;
    for(k=p; k<r+1; k++)
	{
        if(cmp(L[i],R[j])<=0) 
		{
            strcpy(A[k],L[i]);
            i++;
        }
        else
		{
            strcpy(A[k],R[j]);
            j++;
        }
    }
}

void MergeSort(char A[][17], int p, int r)
{
    int q;
    if(p<r)
	{
        q=(p+r)/2;
        MergeSort(A,p,q);
        MergeSort(A,q+1,r);
        Merge(A,p,q,r);
    }
}
//以上，全是照教材写的 

int main()
{
    //clock_t start,finish;
    LARGE_INTEGER num;
    long long start,end,freq;
    double t;
    FILE*fp;
    int b,i;
    char (*p)[17];
    char filename[300];
    
    printf("input base x of the length(3^x)\n");
    scanf("%d",&b);
    n=pow(3,b);
    
    p=(char (*)[17])malloc(sizeof(char)*17*n);//二维数组，按线性分配内存空间 
    
    if((fp=fopen("D:\\code\\PB14011074-project1\\ex1\\input\\input_strings.txt", "r"))==NULL)
	{
        printf("error\n");
        exit(0);
    }
    
    
    sprintf(filename,"D:\\code\\PB14011074-project1\\ex1\\output\\merge_sort\\result_%d.txt",b);//这里只是为了懒得每一次运行之前改文件代码写的路径而已。。 
    
    for(i=0;i<n; i++)
	{
        fscanf(fp,"%s\n",p[i]);
    }
    
    //start=clock();//计时，调用clock函数
	
	QueryPerformanceFrequency(&num);//调用winapi中的微秒级别计时，用于较小的数据量 
    freq=num.QuadPart;
    QueryPerformanceCounter(&num);
    start=num.QuadPart;
	 
    MergeSort(p,0,n-1);
    
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
        fprintf(fp, "%s\n",p[i]);
    }
    fclose(fp);//写output文件 
    
    if((fp=fopen("D:\\code\\PB14011074-project1\\ex1\\output\\merge_sort\\time.txt", "a"))==NULL)//写入rusult_i.txt中 
	{
        printf("error\n");
        exit(0);
    }
    fprintf(fp, "Merge Sort at base %d takes %f seconds\n",b,t);
    fclose(fp);//写time文件 
    
    printf("Merge sort : %f seconds\n",t);
    return 0;
}
