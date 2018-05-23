#include<stdio.h>
#include <stdlib.h>
#include<time.h> 

int main()
{
	int a[5]={9,27,81,243,729};
	int b[5]={18,81,324,1215,4374}; 
	FILE *fp;
	char filename[300];
	int graph[729][729];
	int weight,x,y,i,j;
	srand((unsigned)time(NULL));
	
	for(i=0;i<729;i++)
		for(j=0;j<729;j++)
			graph[i][j]=65535;
	
	for(i=0;i<5;i++)
	{
		sprintf(filename,"D:\\code\\PB14011074-project4\\project2\\input\\size%d\\input.txt",i+1);
		fp=fopen(filename, "w");
		  //生成的图写入文件 
		for(j=0;j<b[i];j++)
		{
			weight=rand()%31-10;
			x=rand()%a[i];
			y=rand()%a[i];
			while((x==y)||(graph[x][y]!=65535))
			{	
				y=rand()%a[i];
			}
			graph[x][y]=weight;
			fprintf(fp,"%d,%d %d\n",x,y,weight);
		}
		fclose(fp);
	}
	
}
