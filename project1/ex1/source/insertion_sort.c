#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>

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
 
void InsertionSort(char A[][17])
{
    int i,j;
    char key[17];
    for (j=1; j<n; j++)
	{
        strcpy(key, A[j]);
        i=j-1;
        while(i>=0&&cmp(A[i],key)>0)
		{
            strcpy(A[i+1], A[i]);
            i--;
        }
        strcpy(A[i+1], key);
    }
}
//照着教材写的 

int main()
{
	//clock_t start,end;
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
    
    sprintf(filename,"D:\\code\\PB14011074-project1\\ex1\\output\\insertion_sort\\result_%d.txt",b);//这里只是为了懒得每一次运行之前改文件代码写的路径而已。。 
    
    for(i=0;i<n; i++)
	{
        fscanf(fp,"%s\n",p[i]);
    }
    fclose(fp);//读文件
    
    //start=clock();//计时，调用clock函数，用于较大的数据量 
    QueryPerformanceFrequency(&num);//调用winapi中的微秒级别计时，用于较小的数据量 
    freq=num.QuadPart;
    QueryPerformanceCounter(&num);
    start=num.QuadPart;
    InsertionSort(p);
    QueryPerformanceCounter(&num);
    end=num.QuadPart;
    //finish=clock();//计时结束 
    //t=(double)(finish-start)/CLK_TCK;
    t=(double)(end-start)/freq;
    
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
    
    if((fp=fopen("D:\\code\\PB14011074-project1\\ex1\\output\\insertion_sort\\time.txt", "a"))==NULL)//写入rusult_i.txt中 
	{
        printf("error\n");
        exit(0);
    }
    fprintf(fp, "Insertion Sort at base %d takes %f seconds\n",b,t);
    fclose(fp);//写time文件 
    
    printf("Insertion sort : %f seconds\n",t);
    return 0;
}
