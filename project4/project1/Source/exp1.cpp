#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX_NUM 3000

typedef struct node   //表结点 
{  
   int adjvex;  //邻接顶点 
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
FILE *fp,*fp1;
char filename[300];
char filename1[300];

char *color[]={"red","orange","yellow","green","cyan","blue","purple","white","maroon","tan","pink","turquoise","yellowgreen","darkgrey","darkgoldenrod","chartreuse","lightsalmon"};
//graghwiz颜色表
 
int top;//栈顶指针
int Stack[729];
bool instack[729];// Ture表示在栈中
int DFN[729];//DFS访问次序
int LOW[729];//最早抵达次序 
int Dindex;  //到达时间 

char **p=color;//颜色字符串数组指针 

AdjList *adj=(AdjList *)malloc(sizeof(AdjList));

void CreateGraph(AdjList *adj,int m,int x[9999],int y[9999])  
{  
    int n,e,i,s,d; 
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
    for(i=1;i<=e;i++)   //读取文件 
    {  
    	s=x[i-1];
    	d=y[i-1];
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
    int n=adj->VexNum;//顶点个数，后面要遍历每一个点
    EdgeNode *q=NULL;  
    int i;  
    for(i=1;i<=n;i++)  
    {  
        q=adj->vertex[i].firstedge;  
        while(q!=NULL)  
        {  
            fprintf(fp1,"%d->%d\n",adj->vertex[i].name,adj->vertex[q->adjvex].name);//grapgwiz中生成向量 
            q=q->next;  
        }  
    }  
}  

void tarjan(int u)  
{  
    int v;
	EdgeNode *q=NULL; 
    DFN[u]=LOW[u]=++Dindex; //初值赋值为到达时间 
    Stack[++top]=u;  //u入栈(栈底) 
    instack[u]=true;  //表示u在栈中 
    for(q=adj->vertex[u].firstedge;q;q=q->next)//对所有可达边的搜索  
    {  
        v=q->adjvex;  
        if (!DFN[v])		//更新LOW[u]  
        {  
            tarjan(v);  
            if(LOW[v]<LOW[u])  
				LOW[u]=LOW[v]; //取Mininum 
        }  
        else if (instack[v]&&DFN[v]<LOW[u])  
            LOW[u]=DFN[v];  
    }  
    
    if(DFN[u]==LOW[u])  //一个强连通分量被找到 
    {  
    	fprintf(fp,"("); 
        do
        {
            v=Stack[top --];  
            instack[v]=false;  //v依次出栈 
            if(u==v) fprintf(fp,"%d",v); 
			else fprintf(fp,"%d ",v);  //fprintf对时间复杂度测量影响比较大，测量时间的时候会注释掉。 
			fprintf(fp1,"%d [shape=circle, style=filled, fillcolor=%s]\n",v,*p);    //graphwiz中生成节点信息 
        }  
        while (u != v);//一直到v=u都是属于该强连通分量  
        fprintf(fp,")\n");   //同上 
        p++;
    }  
}  

void solve(int m)  
{  
    int i;  
    top=Dindex=0;  
    memset(DFN,0,sizeof(DFN)); 
    for (i=1;i<=a[m];i++)   //对所有结点执行算法 
        if (!DFN[i])  
            tarjan(i); 
}  


int main()  
{  
    int i,j;
    int x[9999],y[9999];

	for(i=0;i<5;i++)
	{	
		sprintf(filename,"D:\\code\\PB14011074-project4\\project1\\input\\size%d\\input.txt",i+1);
    	fp=fopen(filename, "r");
    	for(j=0;j<b[i];j++)
    	{
    		fscanf(fp,"%d,%d\n",&x[j],&y[j]);
		}
		CreateGraph(adj,i,x,y);
		fclose(fp);
	
	
		sprintf(filename,"D:\\code\\PB14011074-project4\\project1\\output\\size%d\\output1.txt",i+1);  
		fp=fopen(filename, "w");
		sprintf(filename1,"D:\\code\\PB14011074-project4\\project1\\output\\size%d\\outputgraph.dot",i+1);  
		fp1=fopen(filename1,"w");
		fprintf(fp1,"digraph g {\n");
		p=color;
		solve(i);  //执行算法  
		fprintf(fp1,"\n");
		DisplayGraph(adj);
		fprintf(fp1,"\noverlap=false\nfontsize=12;\n}\n");
		fclose(fp);
	}
	
	return 0;
}  
