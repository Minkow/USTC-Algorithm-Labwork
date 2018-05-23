#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

#define INF 65535 

int a[5]={9,27,81,243,729};
int b[5]={18,81,324,1215,4374};
int graph[729][729];//以邻接矩阵形式表示图 
int d[729][729];   
int path[729][729]; //用以保存最短路径 
int cnt;//长度计数 
FILE *fp;

void FloydWarshall(int n)
{
    int i,j,k;
    for(k=0;k<a[n];k++)
        for(i=0;i<a[n];i++)
            for(j=0;j<a[n];j++)
                if(d[i][k]!=INF&&d[k][j]!=INF&&d[i][j]>d[i][k]+d[k][j])
                {
                    d[i][j]=d[i][k]+d[k][j];
                    path[i][j]=k;        //i到j要经过K节点，前驱矩阵 
                }
}

void Inf()
{//初始化为正无穷 
	int i,j;
	for(i=0;i<729;i++)
		for(j=0;j<729;j++)
		{
            graph[i][j]=INF;  
        }
}

void Init()
{//根据graph初始化d，同时置前驱矩阵为空 
	int i,j;
	for(i=0;i<729;i++)
		for(j=0;j<729;j++)
		{
            d[i][j]=graph[i][j];
            path[i][j]=0;     
        }
}

void ShortestPath(int i,int j,int k)//利用前驱矩阵，递归实现输出最短路径 
{
    if(path[i][j]==0)
    {
    	if(j==k) fprintf(fp,"%d",j);
		else fprintf(fp,"%d->", j);
        return;
    }
    else
    {
    	cnt++;
        ShortestPath(i, path[i][j],k);
        ShortestPath(path[i][j],j,k);
    }
}

int main()
{
	char filename[300];
	int weight,x,y,i,j,k;
	LARGE_INTEGER num;
    long long start,end,freq;
    double t;
	
	for(i=0;i<5;i++)
	{
		sprintf(filename,"D:\\code\\PB14011074-project4\\project2\\input\\size%d\\input.txt",i+1);
		fp=fopen(filename, "r");
		  //读文件 
		Inf();
		for(j=0;j<b[i];j++)
		{
			fscanf(fp,"%d,%d %d\n",&x,&y,&weight);
			graph[x][y]=weight;
		}
		fclose(fp);
		QueryPerformanceFrequency(&num);//调用winapi中的微秒级别计时，用于较小的数据量 
		freq=num.QuadPart;
		QueryPerformanceCounter(&num);
		start=num.QuadPart;
		Init();
		FloydWarshall(i);
		QueryPerformanceCounter(&num);
    	end=num.QuadPart;
    	t=(double)(1000.0*(end-start)/freq);
		sprintf(filename,"D:\\code\\PB14011074-project4\\project2\\output\\size%d\\output2.txt",i+1);
		fp=fopen(filename, "w");
		for(j=0;j<a[i];j++)
		{
			for(k=0;k<a[i];k++)
			{
				if(j!=k)
				{
					fprintf(fp,"(");
					fprintf(fp,"%d->",j);
					cnt=1;
					ShortestPath(j,k,k);
					fprintf(fp,")");
					fprintf(fp,"   Path Length is %d",cnt);
					fprintf(fp,"\n");
				}
			}
		}
		fclose(fp);
		sprintf(filename,"D:\\code\\PB14011074-project4\\project2\\output\\size%d\\time2.txt",i+1);
		fp=fopen(filename, "w");
		fprintf(fp,"Exp%d takes %f ms",i+1,t);
		fclose(fp);
	}
	
	
	
}
