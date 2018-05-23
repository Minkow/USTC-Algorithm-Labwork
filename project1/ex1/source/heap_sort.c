#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

int n;//全局变量，用做记录长度

int heapsize;

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
 

void MaxHeapify(char A[][17],int i)
{
    int l=2*i+1;//=LEFT(i)
    int r=2*(i+1);//=RIGHT(i)
    int largest;
    char ex[17];
    if(l<=heapsize&&cmp(A[l], A[i])>0)
        largest=l;
    else
        largest=i;
    if(r<=heapsize&&cmp(A[r], A[largest])>0)
        largest=r;
    if(largest!=i)
	{
        strcpy(ex,A[i]);
        strcpy(A[i],A[largest]);
        strcpy(A[largest],ex);
        MaxHeapify(A,largest);
    }
}

void BuildMaxHeap(char A[][17])
{
    int i;
    for(i=(n-1)/2;i>=0;i--)
        MaxHeapify(A,i);
}

void HeapSort(char A[][17])
{
	int i;
    BuildMaxHeap(A);
    char ex[17];
    for (i=n-1;i>0;i--)
	{
        strcpy(ex, A[i]);
        strcpy(A[i], A[0]);
        strcpy(A[0], ex);//exchange(A[1] with A[i]
        heapsize--;
        MaxHeapify(A, 0);
    }
}
//以上，全是照着书写的 

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
    
    heapsize=n-1;
    
    p=(char (*)[17])malloc(sizeof(char)*17*n);//二维数组，按线性分配内存空间 
    
    if((fp=fopen("D:\\code\\PB14011074-project1\\ex1\\input\\input_strings.txt", "r"))==NULL)
	{
        printf("error\n");
        exit(0);
    }
    
    sprintf(filename,"D:\\code\\PB14011074-project1\\ex1\\output\\heap_sort\\result_%d.txt",b);//这里只是为了懒得每一次运行之前改文件代码写的路径而已。。 
    
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
    
    HeapSort(p);
    
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
    
    if((fp=fopen("D:\\code\\PB14011074-project1\\ex1\\output\\heap_sort\\time.txt", "a"))==NULL)//写入rusult_i.txt中 
	{
        printf("error\n");
        exit(0);
    }
    fprintf(fp, "Heap Sort at base %d takes %f seconds\n",b,t);
    fclose(fp);//写time文件 
    
    printf("Heap sort : %f seconds\n",t);
    return 0;
}
