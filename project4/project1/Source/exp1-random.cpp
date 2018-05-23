#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_VERTEX_NUM 729

typedef char VertexType; 

typedef struct node   //表结点 
{  
   int adjvex;  //邻接顶点
   int weight;  //权值 
   node* next;  
}EdgeNode;  
  
typedef struct     //头结点 
{  
   int name;  	//顶点序号 
   EdgeNode* firstedge;  //头指针 
}VertexNode;  
  
typedef struct   
{   
    int VexNum,ArcNum;  //点个数和边的条数 
	VertexNode vertex[MAX_VERTEX_NUM];  //头结点数组 
}AdjList;  //

int a[5]={9,27,81,243,729};  //头结点个数 
int b[5]={18,81,324,1215,4374};  //边个数
FILE *fp;
char filename[300];

AdjList *adj=(AdjList *)malloc(sizeof(AdjList));

void CreateGraph(AdjList *adj,int m)  
{  
    int n,e,i,s,d,w; 
	n=a[m];
	e=b[m];   
    adj->VexNum=n;
    adj->ArcNum=e; 
    EdgeNode *q=NULL;  
    //初始化表头结点    
    for(i=1;i<=n;i++)  
    {  
        adj->vertex[i].name=i;  
        adj->vertex[i].firstedge=NULL;  
    }
    srand((unsigned) time(NULL));
    for(i=1;i<=e;i++)   //随机生成边 
    {  
    	s=rand()%n+1;
    	d=rand()%n+1;  //可以生成：环、重边 
        q=(EdgeNode *)malloc(sizeof(EdgeNode)); //创建一个表结点  
        if(q==NULL)  
            return;  
        q->adjvex=d;   
        q->next=adj->vertex[s].firstedge;//节点依次后移  
        adj->vertex[s].firstedge=q;  
    } 
}

void DisplayGraph(AdjList *adj)  
{  
    int n=adj->VexNum;//顶点个数，后面要遍历每一个点点  
    EdgeNode *q=NULL;  
    int i;  
    for(i=1;i<=n;i++)  
    {  
        q=adj->vertex[i].firstedge;  
        while(q!=NULL)  
        {  
            //printf("%d,%d\n",adj->vertex[i].name,adj->vertex[q->adjvex].name);
            fprintf(fp,"%d,%d\n",adj->vertex[i].name,adj->vertex[q->adjvex].name);
            q=q->next; 
        }  
    }  
  
}  

int main()  
{  
    int i,j;      
    for(i=1;i<=5;i++)
    {
    sprintf(filename,"D:\\code\\PB14011074-project4\\project1\\input\\size%d\\input.txt",i);  //生成的图写入文件 
    fp=fopen(filename, "w");
    CreateGraph(adj,i-1);  
    DisplayGraph(adj);
    fclose(fp);
	}
	return 0;
}  
