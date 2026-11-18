#include <iostream>
using namespace std;
typedef char TElemType;
typedef struct BiTNode{
	TElemType data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
/*用先序遍历创建二叉树 
先将没有左右孩子的都补上左右孩子
然后按照先序遍历得到遍历序列就可以进行输入了 
*/ 
void CreateBiTree(BiTree &T){
	char ch;
	cin>>ch;
	if(ch=='#')  T=NULL;
	else{
		T=new BiTNode;
		T->data=ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
}
void PreOrder(BiTree T){
	if(T){
	cout<<T->data;
	PreOrder(T->lchild);
	PreOrder(T->rchild);
	}
}
void InOrder(BiTree T){
	if(T){
		InOrder(T->lchild);
		cout<<T->data;
		InOrder(T->rchild);
	}
}
void PostOrder(BiTree T){
	if(T){
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		cout<<T->data;
	}
}
int NodeCount(BiTree T){
	if(T==NULL) return 0;
	return NodeCount(T->lchild)+NodeCount(T->rchild)+1;
} 
void NodeCount1(BiTree T,int &count0,int &count1,int &count2){
	if(T==NULL) return;
	else if(T->lchild&&T->rchild) count2++;
	else if(!T->lchild&&!T->rchild) count0++;
	else count1++;
	NodeCount1(T->lchild,count0,count1,count2);
	NodeCount1(T->rchild,count0,count1,count2);
}
int Height(BiTree T){
	if(T==NULL) return 0;
	else return Height(T->lchild)>Height(T->rchild)?Height(T->lchild)+1:Height(T->rchild)+1;
}
void leafCout(BiTree T){
	if(T==NULL) return;
	else if(!T->lchild&&!T->rchild) cout<<T->data<<" ";
	leafCout(T->lchild);
	leafCout(T->rchild);
}
int main(){
	int count0=0,count1=0,count2=0;
	BiTree T;
	CreateBiTree(T);
	PreOrder(T);
	cout<<endl;
	InOrder(T);
	cout<<endl;
	PostOrder(T);
	cout<<endl;
	NodeCount1(T,count0,count1,count2);
	cout<<NodeCount(T)<<endl;
	cout<<count0<<" "<<count1<<" "<<count2<<endl;
	cout<<Height(T)<<endl;
	leafCout(T);
	cout<<endl;
	return 0;
}
//abd#ef####cg###
