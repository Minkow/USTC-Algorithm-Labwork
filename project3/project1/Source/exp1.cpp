#include<stdio.h>
#include<stdlib.h>
#include<sys/unistd.h>

#define n 28//数据规模 
#define INF 10000000//正无穷，定义为一个大常数 

FILE *fp;

void MatrixChainOrder(int *p,int m[n+1][n+1],int s[n+1][n+1])
{
	int i,j,k,l,q;
	for(i=0;i<=n;++i)
		m[i][i] = 0;
	for(l=2;l<=n;l++)  //l是chain长度 
	{
		for(i=1;i<=n-l+1;i++)  //计算当前l的最小代价 
		{
			j=i+l-1; //从i开始，到i+l-1结束，长度为l的chain 
			m[i][j]=INF;  //最大初始化 
			for(k=i;k<=j-1;k++)  //遍历，寻找最优划分 
			{
				q=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
				if(q<m[i][j])
				{
					m[i][j]=q;
					s[i][j]=k; //记录划分的位置 
				}
			}
		}
	}
}

void PrintOptimalParens(int s[n+1][n+1],int i,int j)
{//简单的递归调用输出方案 
	if(i==j)
	{
 		printf("A%d",i);
		fprintf(fp,"A%d",i);
	}
	else
	{
		printf("(");
		fprintf(fp,"(");
		PrintOptimalParens(s,i,s[i][j]);
		PrintOptimalParens(s,s[i][j]+1,j);
		printf(")");
		fprintf(fp,")");
	}
}

inline unsigned long long GetNTime()  
{  
    __asm("RDTSC");  
}//汇编调用，记录当前cpu周期数 

int main()
{
	int p[n+1];//p保存chain的规模 
	int m[n+1][n+1]={0};
	int s[n+1][n+1]={0};
	int i,j;
	long long start,end,t;	

	if((fp=fopen("D:\\code\\PB14011074-project3\\project1\\input\\input1.txt", "r"))==NULL)
	{
		printf("error\n");
		exit(0);
	}

	for(i=0;i<=n;i++)
	{
		fscanf(fp,"%d\n",&p[i]);
	}
	fclose(fp);//读文件
	
	fp=fopen("D:\\code\\PB14011074-project3\\project1\\Output\\output.txt","a");
	fprintf(fp,"n=%d:\n",n);
	start=GetNTime();
	MatrixChainOrder(p,m,s);
	end=GetNTime();
	t=end-start;	
	PrintOptimalParens(s,1,n);
	fprintf(fp,"\n");
	printf("\n");
	fclose(fp);
	
	fp=fopen("D:\\code\\PB14011074-project3\\project1\\Output\\time.txt","a");
	fprintf(fp,"n=%d takes %d CPU cycles\n",n,t);
	return 0;
}

