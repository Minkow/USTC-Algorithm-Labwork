#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/unistd.h> //用于RDTSC寄存器的头文件 

FILE *fp;
char filename[300];

enum NodeColor{RED,BLACK};//枚举类型RED=0 BLACK=1 

struct RBTreeNode
{
	int size,key;
	enum NodeColor color;
	RBTreeNode *left,*right,*p;//三叉链表(附带值color,size) 
};

struct RBTree
{
	RBTreeNode *root,*nil;//树的数据结构，root,nil均为RBTreeNode数据类型 
};

void LeftRotate(RBTree *T,RBTreeNode *x)
{
	RBTreeNode *y=x->right;
	x->right=y->left;
	if(y->left!=T->nil)
		y->left->p=x;
	y->p=x->p;
	if(x->p==T->nil)
		T->root=y;
	else if(x==x->p->left)
		x->p->left=y;
	else x->p->right=y;
	y->left=x;
	x->p=y;
	y->size=x->size;
	x->size=x->left->size+x->right->size+1;//旋转：仅会使两个结点的size属性失效，将其维护即可 
}	//对教材代码的实现，与右旋对称 

void RightRotate(RBTree *T,RBTreeNode *x)
{
	RBTreeNode *y=x->left;
	x->left=y->right; //y的rchild成为x的lchild
	if(y->right!=T->nil)
		y->right->p=x;
	y->p=x->p; //y成为新的根 
	if(x->p==T->nil)
		T->root=y;
	else if(x==x->p->right)
		x->p->right=y;
	else x->p->left=y;
	y->right=x;//x成为y的rchild 
	x->p=y;
	y->size=x->size;
	x->size=x->left->size+x->right->size+1;//旋转：仅会使两个结点的size属性失效，将其维护即可 
}	//对教材代码的实现，右旋把左旋中的left<->right即可 

void RBInsertFixup(RBTree *T,RBTreeNode *z)
{
	RBTreeNode *y;
	while(z->p->color==RED)
	{
		if(z->p==z->p->p->left)//z为左边的节点，下一段为z为右边节点，左右完全对称 
		{
			y=z->p->p->right;
			if(y->color==RED)//case1：叔结点为红色 
			{
				z->p->color=BLACK;
				y->color=BLACK;
				z->p->p->color=RED;
				z=z->p->p;
			}
			else 
			{
				if(z==z->p->right)//case2
				{
					z=z->p;
					LeftRotate(T,z);//左旋转化为case3 
				}
				z->p->color=BLACK;//case3
				z->p->p->color=RED;
				RightRotate(T,z->p->p);
			}
		}
		
		else
		if(z->p==z->p->p->right)
		{
			y=z->p->p->left;
			if(y->color==RED)
			{
				z->p->color=BLACK;
				y->color=BLACK;
				z->p->p->color=RED;
				z=z->p->p;
			}
			else 
			{
				if(z==z->p->left)
				{
					z=z->p;
					RightRotate(T,z);
				}
				z->p->color=BLACK;
				z->p->p->color=RED;
				LeftRotate(T,z->p->p);
			}
		}
		T->root->color=BLACK;
	}
}//对教材的实现 

void RBInsert(RBTree *T,RBTreeNode *z)//插入：查找正确的位置之后执行插入。 
{
	RBTreeNode *x,*y;
	y=T->nil;
	x=T->root;	
	while(x!=T->nil)
	{
		x->size++;// 插入：新插入结点到根向上,每个结点的size+1
		y=x;
		if(z->key<x->key)//根据key的大小确认左右 
			x=x->left;
		else 
			x=x->right;
	}	
	z->p=y;
	if(y==T->nil) 
		T->root=z;
	else 
	{
		if(z->key<y->key)
			y->left=z;
    	else
			y->right=z;
	}
	z->left=T->nil;
	z->right=T->nil;
	z->color=RED;
	z->size=1;
	z->left->size=0;
	z->right->size=0;

	RBInsertFixup(T,z);//修复红黑树颜色性质 
}//对教材上代码的实现 

void RBTransplant(RBTree *T,RBTreeNode *u,RBTreeNode *v)//子树u,v替换 
{
	if(u->p==T->nil)
		T->root=v;
	else if(u==u->p->left)
		u->p->left=v;
	else 
		u->p->right=v;
	v->p=u->p;
}

RBTreeNode *TreeMinimum(RBTree *T,RBTreeNode *x)//最小关键字，返回指针 
{
	while(x->left!=T->nil)
	{
		x=x->left;
	}
	return x;
} 

void RBDeleteFixup(RBTree *T,RBTreeNode *x)
{
	RBTreeNode *w;
	while(x!=T->root&&x->color==BLACK)//将x的黑属性向上移动 
	{
		if(x==x->p->left)//后半段是左右对称的 
		{
			w=x->p->right;
			if(w->color==RED)
			{//case1:改变w和x.p的颜色再将其旋转，转化成其他情况 
				w->color=BLACK;
				x->p->color=RED;
				LeftRotate(T,x->p);
				w=x->p->right;
			}
			if(w->left->color==BLACK&&w->right->color==BLACK)
			{//case2:x的brother是黑，而且w的两个子节点都是黑
				w->color=RED;
				x=x->p;
			}
			else
			{
				if(w->right->color==BLACK)
				{//case3：x的brother是黑色，w的lchild是红,rchild是黑。  
					w->left->color=BLACK;
					w->color=RED;
					RightRotate(T,w);
					w=x->p->right;//交换w和w.left的颜色，旋转转化为case4  
				}
			w->color=x->p->color;//case4：w为黑，w的rchild为红 
			x->p->color=BLACK;
			w->right->color=BLACK;
			LeftRotate(T,x->p);
			x=T->root;
			}
		}
			
		else if(x==x->p->right)
		{
			w=x->p->left;
			if(w->color==RED)
			{
				w->color=BLACK;
				x->p->color=RED;
				RightRotate(T,x->p);
				w=x->p->left;
			}
			if(w->right->color==BLACK&&w->left->color==BLACK)
			{
				w->color=RED;
				x=x->p;
			}
			else
			{
			if(w->left->color==BLACK)
				{
					w->right->color=BLACK;
					w->color=RED;
					LeftRotate(T,w);
					w=x->p->left;
				}
			w->color=x->p->color;
			x->p->color=BLACK;
			w->left->color=BLACK;
			RightRotate(T,x->p);
			x=T->root;
			}
		}
	}
	x->color=BLACK;
}

void RBDelete(RBTree *T,RBTreeNode *z)
{
	RBTreeNode *x,*y,*v;
	y=z;
	v=z->p;
	enum NodeColor yocolor=y->color;
	if(z->left==T->nil)//lchild为nil的情况，即除了nil只有一个或没有child，直接删之后移植子树至它自身 
	{
		while(v!=T->nil)
		{
			v->size--;
			v=v->p;
		}//删除：被删除结点之上的每个结点的size-1，在下面的几种情况都会出现。 
		x=z->right;
		RBTransplant(T,z,z->right);//右子树替换它 
	}
	else if(z->right==T->nil)//与上面对称 
	{
		while(v!=T->nil)
		{
			v->size--;
			v=v->p;
		}
		x=z->left;
		RBTransplant(T,z,z->left);
	}
	else//child不为nil，此时找到右子树最小值，替换再删除原来的最小值节点位置就可以了 
	{
		y=TreeMinimum(T,z->right);//找到右子树最小值 
		v=y->p;
		y->size=z->size-1;//后继y取代z，size-1 
		while(v!=T->nil)
		{
			v->size--;
			v=v->p;
		}
		yocolor=y->color;
		x=y->right;
		if(y->p==z)//case1:右子树最小值是它的rchild 
			x->p=y;
		else//case2:不是rchild 
		{
			RBTransplant(T,y,y->right);
			y->right=z->right;
			y->right->p=y;
		}
		RBTransplant(T,z,y);//y替换z 
		y->left=z->left;
		y->left->p=y;
		y->color=z->color;//恢复y之上的红黑树颜色性质 
	}
	if(yocolor==BLACK)
		RBDeleteFixup(T,x);
}

RBTreeNode *RBSelect(RBTreeNode *x,int i)//查找给定元素 
{
	int r;
	r=x->left->size+1;
	if(i==r)
	{
		return x;
	}
	else if(i<r)//小于去左边找，否则去右边，递归实现 
		return RBSelect(x->left,i);
	else
		return RBSelect(x->right,i-r);
}

int RBRank(RBTree *T,RBTreeNode *x)//确定元素的秩 
{
	RBTreeNode *y;
	int r;
	r=x->left->size+1;
	y=x;
	while(y!=T->root)
	{
		if(y==y->p->right)
			r=r+y->p->left->size+1;
		y=y->p;
	}
	return r;
}

void PreOrder(RBTree *T,RBTreeNode *x)//前序遍历，递归实现，下类似。 
{
	if(x!=T->nil)
	{
		fprintf(fp,"key:%d\tcolor:%d\tsize:%d\n",x->key,x->color,x->size);
		printf("key:%d\tcolor:%d\tsize:%d\n",x->key,x->color,x->size);
		PreOrder(T,x->left);
		PreOrder(T,x->right);
	}
}

void InOrder(RBTree *T,RBTreeNode *x)
{  
    if(x!=T->nil) 
    {         
        InOrder(T,x->left);  
        fprintf(fp,"key:%d\tcolor:%d\tsize:%d\n",x->key,x->color,x->size);
        printf("key:%d\tcolor:%d\tsize:%d\n",x->key,x->color,x->size);
        InOrder(T,x->right);  
    } 
}  

void PostOrder(RBTree *T,RBTreeNode *x)
{
	if(x!=T->nil)
	{
		PostOrder(T,x->left);
		PostOrder(T,x->right);
		fprintf(fp,"key:%d\tcolor:%d\tsize:%d\n",x->key,x->color,x->size);
		printf("key:%d\tcolor:%d\tsize:%d\n",x->key,x->color,x->size);
	}
}

inline unsigned long long GetNTime()//汇编调用RDTSC寄存器，里面保存为时钟周期数 
{
       __asm ("RDTSC");
}

int main()
{
    long long start,end,freq,s1,s2,total=0;
    RBTree *T=new RBTree;
    int i,j,n;
	
	T->nil=new RBTreeNode;
	T->nil->size=0;
	T->nil->key=151;//151为最大值 
	T->nil->color=BLACK;
	T->nil->left=NULL;
	T->nil->right=NULL;
	T->nil->p=NULL;
	T->root=T->nil;//红黑树的初始化 
	
	scanf("%d",&n);
	int *p=new int[n];
	long long *t=new long long[n/10];
	RBTreeNode *q=new RBTreeNode[n];//预先分配好节点的内存空间 
		
	if((fp=fopen("D:\\code\\PB14011074-project2\\ex\\input\\input.txt", "r"))==NULL)
	{
        printf("error\n");
    }
    
    for(i=0;i<n;i++)
	{
        fscanf(fp,"%d\n",&p[i]);
    }
    fclose(fp);
    
    for(i=0;i<n/10;i++)
    {
    	start=GetNTime();
    	for(j=0;j<10;j++)
    	{	
			(q[i*10+j]).key=p[i*10+j];
    		RBInsert(T,&q[i*10+j]);
    	}
    	end=GetNTime();
    	t[i]=end-start;
	}
//以上为插入节点，10个一组 
	
	sprintf(filename,"D:\\code\\PB14011074-project2\\ex\\output\\size%d\\preorder.txt",n);
	fp=fopen(filename,"a");	
    PreOrder(T,T->root);
	fclose(fp);
	
	sprintf(filename,"D:\\code\\PB14011074-project2\\ex\\output\\size%d\\inorder.txt",n);
	fp=fopen(filename,"a");	
    InOrder(T,T->root);
    fclose(fp);
	
	sprintf(filename,"D:\\code\\PB14011074-project2\\ex\\output\\size%d\\postorder.txt",n);
	fp=fopen(filename,"a");	
    PostOrder(T,T->root);
    fclose(fp);

	sprintf(filename,"D:\\code\\PB14011074-project2\\ex\\output\\size%d\\time1.txt",n);
	fp=fopen(filename,"w");
	for(i=0;i<n/10;i++)
	{
		fprintf(fp, "Insert up to Node %d0 takes %d cpu cycles\n",i+1,t[i]);
		printf("Insert up to Node %d0 takes %d cpu cycles\n",i+1,t[i]);
	}
	
	for(i=0;i<n/10;i++)
	{
		total+=t[i];
	}
	
	fprintf(fp,"Total takes %d cpu cycles",total);
	printf("Total takes %d cpu cycles",total);
	
	fclose(fp);
	 
//以下为删除 
	sprintf(filename,"D:\\code\\PB14011074-project2\\ex\\output\\size%d\\delete_data.txt",n);
	fp=fopen(filename,"a");
	
	RBTreeNode *r=new RBTreeNode;

	r=RBSelect(T->root,n/4);	
	fprintf(fp,"key:%d\tcolor:%d\tsize:%d\n",r->key,r->color,r->size);
	printf("key:%d\tcolor:%d\tsize:%d\n",r->key,r->color,r->size);
	start=GetNTime();
	RBDelete(T,r);
	end=GetNTime();
    s1=end-start;
    
    r=RBSelect(T->root,n/2-1);
    fprintf(fp,"key:%d\tcolor:%d\tsize:%d\n",r->key,r->color,r->size);
	printf("key:%d\tcolor:%d\tsize:%d\n",r->key,r->color,r->size);
	start=GetNTime();
	RBDelete(T,r);
	end=GetNTime();
    s2=end-start;
    
    fclose(fp);
    
	sprintf(filename,"D:\\code\\PB14011074-project2\\ex\\output\\size%d\\time2.txt",n);
    fp=fopen(filename,"a");
    fprintf(fp,"Delete node n/4 takes %d cpu cycles\n",s1);
	fprintf(fp,"Delete node n/2 takes %d cpu cycles\n",s2);
	printf("Delete node n/4 takes %d cpu cycles\n",s1);
	printf("Delete node n/2 takes %d cpu cycles\n",s2);
    fclose(fp);		
	sprintf(filename,"D:\\code\\PB14011074-project2\\ex\\output\\size%d\\delete_inorder.txt",n);
	fp=fopen(filename,"a");
    InOrder(T,T->root);
    fclose(fp);

	return 0;
}

