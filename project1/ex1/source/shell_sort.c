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

void ShellSort(char A[][17],int n)
{
    int inc[5]={21,15,7,3,1},i,j,k=0;
    char t[17];
    while(inc[k]>n)
    	k++;//找到合适增量 
    	
    for(;k<5;k++)//对对应increment作排序 
    {
        for(i=inc[k];i<n;i++)//一趟排序，将d后元素插入有序区 
        {
        	if(cmp(A[i],A[i-inc[k]])<0)
        	{
        		strcpy(t,A[i]);
        		j=i-inc[k];
        		while(j>=0&&cmp(t,A[j])<0)//查找R[i]插入位置 
        		{
        			strcpy(A[j+inc[k]],A[j]);//后移记录 
        			j-=inc[k];//查找前一记录 
				}
				strcpy(A[j+inc[k]],t);//A[i]插入对应位置 
			}
		}
    }
}

                                 
int main()
{
	int inc[5]={21,15,7,3,1};
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
    
    sprintf(filename,"D:\\code\\PB14011074-project1\\ex1\\output\\shell_sort\\result_%d.txt",b);//这里只是为了懒得每一次运行之前改文件代码写的路径而已。。 
    
    for(i=0;i<n; i++)
	{
        fscanf(fp,"%s\n",p[i]);
    }
    fclose(fp);//读文件
    
    //start=clock();//计时，调用clock函数 
    QueryPerformanceFrequency(&num);//调用winapi中的微秒级别计时，用于较小的数据量 
    freq=num.QuadPart;
    QueryPerformanceCounter(&num);
    start=num.QuadPart;
    
    ShellSort(p,n);

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
    
    if((fp=fopen("D:\\code\\PB14011074-project1\\ex1\\output\\shell_sort\\time.txt", "a"))==NULL)//写入rusult_i.txt中 
	{
        printf("error\n");
        exit(0);
    }
    fprintf(fp, "Shell Sort at base %d takes %f seconds\n",b,t);
    fclose(fp);//写time文件 
    
    printf("Shell sort : %f seconds\n",t);
    return 0;
}
