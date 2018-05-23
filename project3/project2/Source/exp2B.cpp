#include<stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define lx 105
#define ly 25

FILE *fp;
int cnt;//±£¥ÊLCS≥§∂» 

enum NodeColor{case1,case2,case3};

void LcsLength(char* X,char* Y,int c[lx+1][ly+1],int b[lx+1][ly+1],int n)
{
    int i,j;
    for(i=0;i<n;i++)
        c[i][0]=0;
    for(j=0;j<ly;j++)
        c[0][j]=0;
    for(i=1;i<=n;i++)
        for(j=1;j<=ly;j++)
        {
            if(X[i]==Y[j])
            {
                c[i][j]=c[i-1][j-1]+1;
                b[i][j]=case1;
            }
            else if(c[i-1][j]>=c[i][j-1])
            {
                c[i][j]=c[i-1][j];
                b[i][j]=case2;
            }
            else
            {
                c[i][j]=c[i][j-1];
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
}  

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
    
    ch=(char*)malloc(sizeof(char)*(106));
    srand((unsigned) time(NULL));
    
    X[0]=' ';
    Y[0]=' ';
    
    for(k=0;k<7;k++)
    {
    	cnt=0;
    	fp=fopen("D:\\code\\PB14011074-project3\\project2\\input\\inputB.txt", "a");
    	for(i=0;i<15*(k+1);i++)
    	{
    		num=rand()%26;
    		ch[i]='A'+num;
			fprintf(fp,"%c",ch[i]); 
		}
		fprintf(fp,"\n");	
		for(i=0;i<15*(k+1);i++)
		{
			X[i+1]=ch[i];
		}
		X[0]=' ';
    
    	for(i=0;i<ly;i++)
    	{
    		num=rand()%26;
    		ch[i]='A'+num;
			fprintf(fp,"%c",ch[i]); 
		}
		fprintf(fp,"\n");
		fclose(fp);
		 
		for(i=0;i<ly;i++)
		{
			Y[i+1]=ch[i];
		}
		Y[0]=' ';
    	
    	fp=fopen("D:\\code\\PB14011074-project3\\project2\\output\\ex2\\output.txt", "a");
    	fprintf(fp,"pair %d LCS is:",k+1);
    	printf("pair %d LCS is:",k+1);
    	start=GetNTime();
    	LcsLength(X,Y,c,b,15*(k+1));
    	end=GetNTime();
    	t[k]=end-start;
    	PrintLcs(b,X,15*(k+1),ly);
    	fprintf(fp,"\nLCS length is %d\n",cnt);
    	printf("\nLCS length is %d\n",cnt);
    	fclose(fp);
	}
	
	fp=fopen("D:\\code\\PB14011074-project3\\project2\\output\\ex2\\time.txt", "w");
	for(k=0;k<7;k++)
	{
		fprintf(fp,"pair %d takes %d CPU cycles\n",k+1,t[k]);
	}
	fclose(fp);
	
    return 0;
}


