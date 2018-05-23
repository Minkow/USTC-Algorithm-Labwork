#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h> 

int n,m,match,phash,thash,y;
char t[150000];
char p[100];
char next[100];
char qsbc[122];
int d=62;


void kmpnext()  
{  
	int i;
    int j=0;  
    for(i=1;i<=m;i++)
	{  
		next[i]=j;
		while(j>0&&(p[i]!=p[j]))
		{
			j=next[j];
			j++;
		}
	}
}

void kmp()
{
	int i,j=1;
	match=-1;
	for(i=1;i<=n;i++)
	{
		while(j>0&&t[i]!=p[j])
			{j=next[j];}
		if(j==m)
			{match=(i-m+1);} 
		j++;				
	}
}
//以上为kmp算法，分为求next[]以及计算，预处理为kmpnext(),计算为kmp() 

void prebc()
{
	int i;
	for(i=30;i<=122;i++)
		qsbc[i]=m+1;
	for(i=1;i<=m;i++)
		qsbc[p[i]]=m+1-i;		
}

void qs()
{
	int j=1;
	match=-1;
	while(j<=n-m+1)
	{
		if(memcmp(p,t+j-1,m)==0)
			match=j;
		j+=qsbc[t[j+m]];
	}
}
//以上为qs算法，prebc()为预处理，qs()为计算 

int ord(char a)
{
	if('0'<=a<='9')
		return (a-'0');
	else if('a'<=a<='z')
		return (a-'a'+10);
	else if('A'<=a<='Z')
		return (a-'A'+36);
}

void krpre()
{
	int i;
	for(i=1;i<m;i++)
	y*=d;
	for(i=1;i<=m;i++)
	{
		phash=((phash*d)+ord(p[i]));
		thash=((thash*d)+ord(t[i]));
	}
}

void kr()
{
	int j=1;
	match=-1;
	while(j<=n-m+1)
	{
		if(phash==thash&&memcmp(p,t+j-1,m)==0)
			match=j;
		thash=(thash-ord(t[j])*y)*d+ord(t[j+m]);
		j++;
	}
}
//以上为kr算法，krpre()为分离出来的预处理，kr()为执行，ord()为求字符a对应的62进制数的函数 


inline unsigned long long GetNTime()  
{  
    __asm("RDTSC");  
}//汇编调用，记录当前cpu周期数 


int main()
{
    FILE *fp;
    int i,j,k,num,r,cnt;
	char c;
	long long start,end,t1,t2; 
	char filename[300];
	
    srand((unsigned) time(NULL));
    t[0]='0';
    p[0]='0';
    for(i=0;i<5;i++)
	{
		fp=fopen("D:\\code\\PB14011074-project5\\input\\input.txt", "a");
		k=5+3*i;
		n=pow(2,k);
		m=pow(2,i+2);
		fprintf(fp,"%d,%d,",n,m);
		for(j=0;j<n;j++)
		{
			cnt=1;
			r=rand()%62;
			if(r<10)
			{
				num=rand()%10;
				c='0'+num;
      		  	fprintf(fp,"%c",c);
      		  	t[cnt]=c;
      		  	cnt++;
			}
			else if(r<36)
			{
				num=rand()%26;
				c='a'+num;
				fprintf(fp,"%c",c);
				t[cnt]=c;
      		  	cnt++;
			}
    	    else 
    	    {
    	    	num=rand()%26;
				c='A'+num;
				fprintf(fp,"%c",c);
				t[cnt]=c;
      		  	cnt++;
			}//随机字符串生成，所有字符等概率 
		}
		fprintf(fp,",");
		for(j=0;j<m;j++)
		{
			cnt=1;
			r=rand()%62;
			if(r<10)
			{
				num=rand()%10;
				c='0'+num;
      		  	fprintf(fp,"%c",c);
      		  	p[cnt]=c;
      		  	cnt++;
			}
			else if(r<36)
			{
				num=rand()%26;
				c='a'+num;
				fprintf(fp,"%c",c);
				p[cnt]=c;
      		  	cnt++;
			}
    	    else 
    	    {
    	    	num=rand()%26;
				c='A'+num;
				fprintf(fp,"%c",c);
				p[cnt]=c;
      		  	cnt++;
			}//随机字符串生成，所有字符等概率 
		}
		fprintf(fp,"\n");
		fclose(fp);
		
		
		sprintf(filename,"D:\\code\\PB14011074-project5\\output\\output_%d.txt",i+1);
		fp=fopen(filename,"w");
		
		start=GetNTime();
		kmpnext();
		end=GetNTime();
		t1=end-start;
		
		start=GetNTime();
		kmp();
		end=GetNTime();
		t2=end-start;
		fprintf(fp,"KMP:%d,%d,%d,%d,%d\n",n,m,match,t1,t2);
		printf("KMP:%d,%d,%d,%d,%d\n",n,m,match,t1,t2);
		
		start=GetNTime();
		prebc();
		end=GetNTime();
		t1=end-start;
		
		start=GetNTime();
		qs();
		end=GetNTime();
		t2=end-start;
		fprintf(fp,"QS:%d,%d,%d,%d,%d\n",n,m,match,t1,t2);
		printf("QS:%d,%d,%d,%d,%d\n",n,m,match,t1,t2);
		
		start=GetNTime();
		krpre();
		end=GetNTime();
		t1=end-start;
		
		start=GetNTime();
		kr();
		end=GetNTime();
		t2=end-start;
		fprintf(fp,"KR:%d,%d,%d,%d,%d\n",n,m,match,t1,t2);
		printf("KR:%d,%d,%d,%d,%d\n",n,m,match,t1,t2);
		fclose(fp);
    }
    return 0;
}
