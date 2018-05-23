#include<stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define lx 20 //x长度恒定为20 
#define ly 70 //y长度最大为70 

//由于循环操作上的方便，这个程序内嵌了随机字符串的生成 

FILE *fp;
int cnt;//保存LCS长度 

enum NodeColor{case1,case2,case3};

void LcsLength(char* X,char* Y,int c[lx+1][ly+1],int b[lx+1][ly+1],int n)
{
    int i,j;
    for(i=0;i<lx;i++)
        c[i][0]=0;
    for(j=0;j<n;j++)
        c[0][j]=0;//i=0 or j=0时c[i][j]=0; 
    for(i=1;i<=lx;i++)
        for(j=1;j<=n;j++)
        {
            if(X[i]==Y[j])  
            {
                c[i][j]=c[i-1][j-1]+1; //当x[i]=y[j]时 
                b[i][j]=case1;
            }
            else if(c[i-1][j]>=c[i][j-1]) 
            {
                c[i][j]=c[i-1][j]; //c[i][j]=max{c[i][j-1],c[i-1][j]} 
                b[i][j]=case2;
            }
            else
            {
                c[i][j]=c[i][j-1]; //c[i][j]=max{c[i][j-1],c[i-1][j]} 
                b[i][j]=case3;
            }
        }
}

void PrintLcs(int b[lx+1][ly+1],char *X,int i,int j)
{
    if(i==0||j==0)
        return;
    if(b[i][j]==case1)
    {
        PrintLcs(b,X,i-1,j-1);
        printf("%c",X[i]);
        fprintf(fp,"%c",X[i]);
        cnt++;
    }
    else if(b[i][j]==case2)
		PrintLcs(b,X,i-1,j);
    else
        PrintLcs(b,X,i,j-1);
}

inline unsigned long long GetNTime()  
{  
    __asm("RDTSC");  
}//汇编调用获得当前CPU周期数 

int main()
{
    int i,j,n,num,k;
    char *ch;
    char X[lx+1];
    char Y[ly+1];
    
    int b[lx+1][ly+1]={0};
    int c[lx+1][ly+1]={0};
    
    long long start,end;
	long long t[7];	
    
    ch=(char*)malloc(sizeof(char)*(71));
    srand((unsigned) time(NULL));//获取随机数种子 
    
    X[0]=' ';
    Y[0]=' ';
  
    for(k=0;k<7;k++)//共7组 
    {
    	cnt=0;
    	fp=fopen("D:\\code\\PB14011074-project3\\project2\\input\\inputA.txt", "a");
    	for(i=0;i<lx;i++)
    	{
    		num=rand()%26;
    		ch[i]='A'+num;
			fprintf(fp,"%c",ch[i]); 
		}
		fprintf(fp,"\n");	
		for(i=0;i<lx;i++)
		{
			X[i+1]=ch[i];
		}
		X[0]=' ';//随机生成ch[]，保存到x[]中，并且写到文件中 
    
    	for(i=0;i<10*(k+1);i++)
    	{
    		num=rand()%26;
    		ch[i]='A'+num;
			fprintf(fp,"%c",ch[i]); 
		}
		fprintf(fp,"\n");
		fclose(fp);
		 
		for(i=0;i<10*(k+1);i++)
		{
			Y[i+1]=ch[i];
		}
		Y[0]=' ';//随机生成ch[]，保存到y[]中，并且写到文件中 
    	
    	fp=fopen("D:\\code\\PB14011074-project3\\project2\\output\\ex1\\output.txt", "a");
    	fprintf(fp,"pair %d LCS is:",k+1);
    	printf("pair %d LCS is:",k+1);
    	start=GetNTime();
    	LcsLength(X,Y,c,b,10*(k+1));
    	end=GetNTime();
    	t[k]=end-start;
    	PrintLcs(b,X,lx,10*(k+1));
    	fprintf(fp,"\nLCS length is %d\n",cnt);
    	printf("\nLCS length is %d\n",cnt);
    	fclose(fp);
	}
	
	fp=fopen("D:\\code\\PB14011074-project3\\project2\\output\\ex1\\time.txt", "w");
	for(k=0;k<7;k++)
	{
		fprintf(fp,"pair %d takes %d CPU cycles\n",k+1,t[k]);
	}
	fclose(fp);//输出时间 
	
    return 0;
}


